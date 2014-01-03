#include "kernel/drivers/uart_irda_cir.h"
#include "tests/mock/uart_driver.h"

#include "assert.h"

static UartMockDriverState *mock_state;

void checkedCallWriteInterrupt(UartMockDriverState *ms) {
    if(ms->int_flags & UART_INT_THR)
        ms->int_handler();
}

/* Call interrupt if read flag is set and there is data in buffer */
void checkedCallReadInterrupt(UartMockDriverState *ms) {
    if(ms->int_flags & UART_INT_RHR_CTI &&
            RingBufferPeek(&ms->comm_state.uart_in_ringbuffer, 0))
        ms->int_handler();
}

void UartBaudRateSet(unsigned int baseAdd, unsigned int baudRate) {
}

void UartFIFOConfigure(unsigned int baseAdd,
                       unsigned int txTrigLevel,
                       unsigned int rxTrigLevel) {
}

void UartInit(unsigned int baseAdd, unsigned int baudRate) {
}

void UartModuleClkConfig(unsigned int baseAdd) {
}

void UartPinMuxSetup(unsigned int baseAdd) {
}

void UartInitExpClk(unsigned int baseAdd,
                         unsigned int baudRate,
                         unsigned int rxTrigLevel,
                         unsigned int txTrigLevel) {
}

void UartSetInterruptHandler(unsigned int baseAdd, void (*fnHandler)(void)) {
    assert(mock_state);
    mock_state->int_handler = fnHandler;
}

/* Returns 0 if no char available, 1 otherwise */
int UartGetCharNonBlocking(unsigned int baseAdd, unsigned char *data) {
    assert(mock_state);
    return RingBufferPop(&mock_state->comm_state.uart_in_ringbuffer,
                         (char*)data);
}

unsigned int UARTCharPutNonBlocking(unsigned int baseAdd,
                                    unsigned char byteWrite) {
    RingBufferPush(&mock_state->comm_state.uart_out_ringbuffer, byteWrite);
    return 1;
}

void UARTIntDisable(unsigned int baseAdd, unsigned int intFlag) {
    mock_state->int_flags &= ~intFlag;
}

void UARTIntEnable(unsigned int baseAdd, unsigned int intFlag) {
    mock_state->int_flags |= intFlag;
    checkedCallReadInterrupt(mock_state);
}

void UartMockDriverStateInit(UartMockDriverState *ms) {
    mock_state = ms;
    RingBufferInit(&ms->comm_state.uart_in_ringbuffer,
                   ms->comm_state.uart_in_data,
                   UART_MOCK_DRIVER_BUFFER_SIZE);
    RingBufferInit(&ms->comm_state.uart_out_ringbuffer,
                   ms->comm_state.uart_out_data,
                   UART_MOCK_DRIVER_BUFFER_SIZE);
    ms->int_handler = 0;
    ms->int_flags = 0;
}

void UartMockDriverInBufferPush(UartMockDriverState *ms, char ch) {
    RingBufferPush(&ms->comm_state.uart_in_ringbuffer, ch);
    checkedCallReadInterrupt(ms);
}
