#include "kernel/hw/soc_AM335x.h"
#include "kernel/drivers/uart_irda_cir.h"
#include "kernel/drivers/uart.h"
#include "kernel/interrupt.h"
#include "app/afproto.h"
#include "app/crc16.h"
#include "app/log.h"
#include "app/command.h"
#include "app/communication.h"

#include <string.h>

#define UART_CONSOLE_BASE                    (SOC_UART_0_REGS)
#define BAUD_RATE_115200                     (115200)

static CommunicationState *_communicationState;

void CommunicationCheckForFrame(CommunicationState *com) {
    char ch;
    unsigned short crc_check = 0;
    int prev_escape = 0;
    int i;
    while(RingBufferPop(&com->uart_in_ringbuffer, &ch) &&
            ch != AFPROTO_START_BYTE);
    // We never saw a start byte
    if(ch != AFPROTO_START_BYTE)
        return;

    BufferClear(&com->deframed_buffer);
    while(RingBufferPop(&com->uart_in_ringbuffer, &ch)) {
        if(prev_escape) {
            ch ^= 0x20;
            prev_escape = 0;
        }

        if(ch == AFPROTO_ESC_BYTE) {
            prev_escape = 1;
        } else {
            if(!BufferAppend(&com->deframed_buffer, ch)) {
                // We ran out of space!
                BufferClear(&com->deframed_buffer);

                // The previous data must be invalid, but there could still
                // be a valid frame in the input buffer
                if(ch == AFPROTO_START_BYTE)
                    RingBufferPush(&com->uart_in_ringbuffer, ch);

                CommunicationCheckForFrame(com);
            }

            if(com->deframed_buffer.used >= 2 && ch != AFPROTO_END_BYTE)
                crc_check = crc16_floating(
                        com->deframed_data[com->deframed_buffer.used-2],
                        crc_check);

            if(ch == AFPROTO_END_BYTE)
                break;
        }
    }

    if(com->deframed_buffer.used < 2)
        return;

    // We never saw an end byte
    // If our callers logic is correct, we should never hit this branch
    if(ch != AFPROTO_END_BYTE) {
        LogCString(LOG_LEVEL_ERROR,
                "Check for frame called but no afproto end byte found");
        for(i = 0;i < com->deframed_buffer.used;++i)
            RingBufferPush(&com->uart_in_ringbuffer, com->deframed_data[i]);
        BufferClear(&com->deframed_buffer);
        return;
    }

    unsigned short sent_crc = *(unsigned short*)&com->deframed_data[
        com->deframed_buffer.used-2];

    if(sent_crc != crc_check) {
        LogCString(LOG_LEVEL_NOTICE,
                "Received afproto frame with invalid CRC");
        return;
    }

    CommandHandleRaw(com->deframed_data);
}

void CommunicationCheckWrite(CommunicationState *com) {
#ifdef DEBUG_UART
    UARTprintf("Write called, start: %u, end: %u\n",
               uart_out_buff_start,
               uart_out_buff_end);
#endif

    char ch;
    while(RingBufferPeek(&com->uart_out_ringbuffer, &ch)) {
#ifdef DEBUG_UART
        UARTPuts("Write loop, Out buff: ", 22);
        int i;
        for(i = uart_out_buff_start;i < uart_out_buff_end;++i)
            UARTprintf("%x", com->uart_out_buff[i]);
        UARTPuts("\n", 1);
#endif

        // Try to put byte in transmit buffer
        if(UARTCharPutNonBlocking(UART_CONSOLE_BASE, ch)) {
            RingBufferPop(&com->uart_out_ringbuffer, 0);
#ifdef DEBUG_UART
            UARTprintf("Char written, start at %u\n",
                       com->uart_out_buff_start);
#endif
        } else {
#ifdef DEBUG_UART
            UARTPuts("THR full, returning write\n\n", 26);
            return;
#endif
        }
    }

#ifdef DEBUG_UART
    UARTPuts("Write completed\n\n", 17);
#endif
    UARTIntDisable(UART_CONSOLE_BASE, UART_INT_THR);
}

void CommunicationCheckRead(CommunicationState *com) {
    unsigned char in_char;
    while(UartGetCharNonBlocking(UART_CONSOLE_BASE, &in_char)) {
        CommunicationGotChar(com, in_char);
    }
}

void CommunicationCheck(CommunicationState *com) {
    CommunicationCheckRead(com);
    CommunicationCheckWrite(com);
}

/* TODO:GAH
 * This is an ugly hack. We really should be able to pass state into our ISR
 * register routine and retrieve this state. Unfortunately, this would require
 * a rewrite of the UART driver to be OO. For now, were storing the state
 * globally.
 */
// Extra wrapper for ISR so we can mock out the interrupt call in testing.
static void CommunicationISR(void *data) {
    CommunicationState *com = (CommunicationState*)data;
    CommunicationCheck(com);
}

static void UARTIsr(void) {
    CommunicationISR(_communicationState);
}

static void CommunicationSendChar(CommunicationState *com, char ch) {
    RingBufferPush(&com->uart_out_ringbuffer, ch);
}

void CommunicationSend(CommunicationState *com, const char *data,
                       unsigned int data_size) {
    if(data_size > COMMUNICATION_UART_OUT_BUFF_SIZE) {
        LogCString(LOG_LEVEL_ERROR, "Attempting to send message larger than"
                   " output buffer size, dropping message");
        return;
    }

    CommunicationSendChar(com, AFPROTO_START_BYTE);

    unsigned int i;
    short crc = 0;

    int prev_escape = 0;
    for(i = 0;i < data_size;++i) {
        if(prev_escape) {
            prev_escape = 0;
            crc = crc16_floating(data[i], crc);
            CommunicationSendChar(com, data[i] ^ 0x20);
        } else if (data[i] == AFPROTO_START_BYTE ||
                data[i] == AFPROTO_ESC_BYTE) {
            prev_escape = 1;
            CommunicationSendChar(com, AFPROTO_ESC_BYTE);
            --i;
        } else {
            crc = crc16_floating(data[i], crc);
            CommunicationSendChar(com, data[i]);
        }
    }

    char *crc_ch = (char*)&crc;
    CommunicationSendChar(com, crc_ch[1]);
    CommunicationSendChar(com, crc_ch[0]);
    CommunicationSendChar(com, AFPROTO_END_BYTE);

    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_THR);
}

void CommunicationGotChar(CommunicationState *com, char ch) {
    RingBufferPush(&com->uart_in_ringbuffer, ch);

    // We might have hit the end of a frame
    if(ch == AFPROTO_END_BYTE)
        CommunicationCheckForFrame(com);
}

void CommunicationInit(CommunicationState *com) {
    RingBufferInit(&com->uart_in_ringbuffer, com->uart_in_data,
            COMMUNICATION_UART_IN_BUFF_SIZE);
    BufferInit(&com->deframed_buffer, com->deframed_data,
            COMMUNICATION_UART_IN_BUFF_SIZE);
    RingBufferInit(&com->uart_out_ringbuffer, com->uart_out_data,
            COMMUNICATION_UART_OUT_BUFF_SIZE);
    _communicationState = com;

    LogCString(LOG_LEVEL_DEBUG, "Initializing communication");

    // Initialize UART peripheral
    UartInit(UART_CONSOLE_BASE, BAUD_RATE_115200);

    UartSetInterruptHandler(UART_CONSOLE_BASE, UARTIsr);

    // Enable UART read interrupts
    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_RHR_CTI);
    LogCString(LOG_LEVEL_DEBUG, "Communication initialized");
}

CommunicationState *CommunicationStateGet(void) {
    return _communicationState;
}
