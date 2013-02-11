#include "kernel/drivers/uart_irda_cir.h"
#include "kernel/interrupt.h"
#include "utils/uartConsole.h"
#include "utils/uartStdio.h"
#include "app/afproto.h"
#include "app/log.h"
#include "communication.h"

#include <string.h>

static char uart_in_buff[COMMUNICATION_UART_IN_BUFF_SIZE];
static unsigned int uart_in_buff_used;
static char deframed_buff[COMMUNICATION_UART_IN_BUFF_SIZE];
static unsigned int deframed_buff_size;

static char uart_out_buff[COMMUNICATION_UART_OUT_BUFF_SIZE];
static unsigned int uart_out_buff_end;
static unsigned int uart_out_buff_start;

void CommunicationCheckForFrame(void) {
    unsigned int ret_size;
    unsigned int ret;

    if((ret = afproto_get_data(uart_in_buff, uart_in_buff_used,
                     deframed_buff, &ret_size)) >= 0) {
        uart_in_buff_used -= ret;
        memcpy(uart_in_buff, uart_in_buff + ret, uart_in_buff_used);
        deframed_buff_size = ret;
    } else if (ret_size != 0) {
        uart_in_buff_used -= ret_size;
        memcpy(uart_in_buff, uart_in_buff + ret_size, uart_in_buff_used);
        deframed_buff_size = 0;
    }
}

void CommunicationCheckWrite(void) {
#ifdef DEBUG_UART
    UARTprintf("Write called, start: %u, end: %u\n", uart_out_buff_start, uart_out_buff_end);
#endif

    while(uart_out_buff_start != uart_out_buff_end) {
#ifdef DEBUG_UART
        UARTPuts("Write loop, Out buff: ", 22);
        int i;
        for(i = uart_out_buff_start;i < uart_out_buff_end;++i)
            UARTprintf("%x", uart_out_buff[i]);
        UARTPuts("\n", 1);
#endif

        // Try to put byte in transmit buffer
        if(UARTCharPutNonBlocking(UART_CONSOLE_BASE,
                                  uart_out_buff[uart_out_buff_start])) {
#ifdef DEBUG_UART
            UARTprintf("Char written, start at %u\n", uart_out_buff_start);
#endif
            uart_out_buff_start++;
        } else {
#ifdef DEBUG_UART
            UARTPuts("THR full, returning write\n\n", 26);
            return;
#endif
        }

        // Handle buffer wrapping
        if(uart_out_buff_start >= COMMUNICATION_UART_OUT_BUFF_SIZE)
            uart_out_buff_start = 0;
    }

#ifdef DEBUG_UART
    UARTPuts("Write completed\n\n", 17);
#endif
    UARTIntDisable(UART_CONSOLE_BASE, UART_INT_THR);
}

void CommunicationCheckRead(void) {
    while(1) {
        signed char in_char = UARTCharGetNonBlocking(UART_CONSOLE_BASE);

        // Check if we got a char
        if(in_char == -1) {
            // No more chars to read
            return;
        }

        uart_in_buff[uart_in_buff_used++] = in_char;
        // We might have hit the end of a frame
        if(in_char == AFPROTO_END_BYTE) {
            CommunicationCheckForFrame();
        }
    }
}

void CommunicationCheck(void) {
    //CommunicationCheckRead();
    CommunicationCheckWrite();
}

void CommunicationSend(const char *data, unsigned int data_size) {
    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_THR);

    if(data_size > COMMUNICATION_UART_OUT_BUFF_SIZE) {
        LogCString(LOG_LEVEL_ERROR, "Attempting to send message larger than"
                   " output buffer size, dropping message");
        return;
    }

    unsigned int i;
    for(i = 0;i < data_size;++i) {
        uart_out_buff[uart_out_buff_end++] = data[i];
        
        // Handle buffer wrap
        if(uart_out_buff_end >= COMMUNICATION_UART_OUT_BUFF_SIZE)
            uart_out_buff_end = 0;
    }

    //CommunicationCheckWrite();
}

static void UARTIsr(void) {
    CommunicationCheck();
}

void CommunicationsInit(void) {
    uart_in_buff_used = 0;
    uart_out_buff_start = 0;
    uart_out_buff_end = 0;

    // Initialize UART peripheral
    UARTConsoleInit();

    // Register the UART ISR
    IntRegister(SYS_INT_UART0INT, UARTIsr);

    // Set interrupt priority
    IntPrioritySet(SYS_INT_UART0INT, 2, AINTC_HOSTINT_ROUTE_IRQ);

    // Enable system interrupt
    IntSystemEnable(SYS_INT_UART0INT);

    // Enable UART read interrupts
    // UARTIntEnable(UART_CONSOLE_BASE, UART_INT_RHR_CTI);
}

