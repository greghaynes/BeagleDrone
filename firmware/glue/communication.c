#include "glue/communication.h"
#include "kernel/hw/soc_AM335x.h"
#include "kernel/drivers/uart_irda_cir.h"
#include "kernel/drivers/uart.h"
#include "kernel/interrupt.h"

#define UART_CONSOLE_BASE                    (SOC_UART_0_REGS)
#define BAUD_RATE_115200                     (115200)

void (*_comm_isr)(void);

static void UARTIsr(void) {
    if(_comm_isr)
        _comm_isr();
}

void CommunicationHwInit(void) {
    UartInit(UART_CONSOLE_BASE, BAUD_RATE_115200);
    UartSetInterruptHandler(UART_CONSOLE_BASE, UARTIsr);
}

int CommunicationTrySendChar(unsigned char ch) {
    return UARTCharPutNonBlocking(UART_CONSOLE_BASE, ch);
}

int CommunicationTryGetChar(unsigned char *dest) {
    return UartGetCharNonBlocking(UART_CONSOLE_BASE, dest);
}

void CommunicationIntEnableRead(void) {
    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_RHR_CTI);
}

void CommunicationIntDisableWrite(void) {
    UARTIntDisable(UART_CONSOLE_BASE, UART_INT_THR);
}

void CommunicationIntEnableWrite(void) {
    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_THR);
}

void CommunicationIntRegisterHandler(void (*isr)(void)) {
    _comm_isr = isr;
}
