#ifndef UART_MOCK_DRIVER_H
#define UART_MOCK_DRIVER_H

#include "app/buffer.h"
#include "app/communication.h"

#define UART_MOCK_DRIVER_BUFFER_SIZE 256

typedef struct UartMockDriverState {
    CommunicationState comm_state;

    void (*int_handler)(void);
    unsigned int int_flags;
} UartMockDriverState;

void UartMockDriverStateInit(UartMockDriverState *ms);

void UartMockDriverInBufferPush(UartMockDriverState *ms, char ch);

#endif

