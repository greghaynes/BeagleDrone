#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/* There are two buffers of this size to allow for frame decoding. */
#define COMMUNICATION_UART_IN_BUFF_SIZE     1024
#define COMMUNICATION_UART_OUT_BUFF_SIZE    1024

#define COMMUNICATION_CHECK_MAX_TIME 100

typedef struct CommunicationState
{
    char uart_in_data[COMMUNICATION_UART_IN_BUFF_SIZE];
    RingBuffer uart_in_ringbuffer;
    char deframed_data[COMMUNICATION_UART_IN_BUFF_SIZE];
    Buffer deframed_buffer;

    char uart_out_data[COMMUNICATION_UART_OUT_BUFF_SIZE];
    RingBuffer uart_out_ringbuffer;
} CommunicationState;

// Send data in afproto frame
void CommunicationSend(CommunicationState *com, const char *data,
                       unsigned int data_size);

// Received a char of input, handle it
void CommunicationGotChar(CommunicationState *com, char ch);

void CommunicationInit(CommunicationState *com);

#endif
