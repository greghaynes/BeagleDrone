#ifndef UART_CONSOLE_H
#define UART_CONSOLE_H

#include "kernel/hw/soc_AM335x.h"

#define UART_CONSOLE_BASE                    (SOC_UART_0_REGS)
#define BAUD_RATE_115200                     (115200)
#define UART_MODULE_INPUT_CLK                (48000000)

void UARTConsolePutc(unsigned char data);
unsigned char UARTConsoleGetc(void);
void UARTConsoleInit(void);

#endif
