#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/* There are two buffers of this size to allow for frame decoding. */
#define COMMUNICATION_UART_IN_BUFF_SIZE     1024
#define COMMUNICATION_UART_OUT_BUFF_SIZE    1024

#define COMMUNICATION_CHECK_MAX_TIME 100

void CommunicationsInit(void);

// Send raw data
void CommunicationSend(const char *data, unsigned int data_size);

#endif
