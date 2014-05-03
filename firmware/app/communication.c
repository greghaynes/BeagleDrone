#include "app/afproto.h"
#include "app/crc16.h"
#include "app/log.h"
#include "app/command.h"
#include "app/communication.h"
#include "glue/communication.h"

#include <string.h>

static CommunicationState *_communicationState;

// Try and decode a frame from com state
void CommunicationHandleFrame(CommunicationState *com) {
    int keep_decoding = 1;

    while(keep_decoding && !RingBufferIsEmpty(&com->uart_in_ringbuffer)) {
        BufferClear(&com->deframed_buffer);
        keep_decoding = afproto_ringbuffer_pop_frame(&com->uart_in_ringbuffer,
                                                     &com->deframed_buffer);

        if(com->deframed_buffer.used > 0)
            CommandHandleRaw(com->deframed_buffer.data,
                             com->deframed_buffer.used);
    }
}

void CommunicationCheckWrite(CommunicationState *com) {
    char ch;
    while(RingBufferPeek(&com->uart_out_ringbuffer, &ch)) {
        if(CommunicationTrySendChar(ch))
            RingBufferPop(&com->uart_out_ringbuffer, 0);
    }

    if(RingBufferSize(&com->uart_out_ringbuffer) > 0)
        CommunicationIntDisableWrite();
}

void CommunicationCheckRead(CommunicationState *com) {
    unsigned char in_char;
    while(CommunicationTryGetChar(&in_char)) {
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
static void CommunicationISR(void) {
    CommunicationCheck(_communicationState);
}

void CommunicationSend(CommunicationState *com, const char *data,
                       unsigned int data_size) {
    if(data_size > COMMUNICATION_UART_OUT_BUFF_SIZE) {
        LogCString(LOG_LEVEL_ERROR, "Attempting to send message larger than"
                   " output buffer size, dropping message");
        return;
    }

    afproto_ringbuffer_push_frame(&com->uart_out_ringbuffer, data, data_size);

    CommunicationIntEnableWrite();
}

void CommunicationGotChar(CommunicationState *com, char ch) {
    RingBufferPush(&com->uart_in_ringbuffer, ch);

    // We might have hit the end of a frame
    if(ch == AFPROTO_END_BYTE)
        CommunicationHandleFrame(com);
}

void CommunicationInit(CommunicationState *com) {
    RingBufferInit(&com->uart_in_ringbuffer, com->uart_in_data,
            COMMUNICATION_UART_IN_BUFF_SIZE);
    BufferInit(&com->deframed_buffer, com->deframed_data,
            COMMUNICATION_UART_IN_BUFF_SIZE);
    RingBufferInit(&com->uart_out_ringbuffer, com->uart_out_data,
            COMMUNICATION_UART_OUT_BUFF_SIZE);

    _communicationState = com;
    CommunicationIntRegisterHandler(CommunicationISR);

    LogCString(LOG_LEVEL_DEBUG, "Initializing communication");

    // Initialize UART peripheral
    CommunicationHwInit();

    // Enable UART read interrupts
    CommunicationIntEnableRead();

    LogCString(LOG_LEVEL_DEBUG, "Communication initialized");
}

CommunicationState *CommunicationStateGet(void) {
    return _communicationState;
}
