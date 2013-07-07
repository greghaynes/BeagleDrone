#ifndef DRIVERS_UART_H
#define DRIVERS_UART_H

void UartBaudRateSet(unsigned int baseAdd, unsigned int baudRate);
void UartFIFOConfigure(unsigned int baseAdd,
                       unsigned int txTrigLevel,
                       unsigned int rxTrigLevel);
void UartInit(unsigned int baseAdd, unsigned int baudRate);
void UartModuleClkConfig(unsigned int baseAdd);
void UartPinMuxSetup(unsigned int baseAdd);
void UartInitExpClk(unsigned int baseAdd,
                         unsigned int baudRate,
                         unsigned int rxTrigLevel,
                         unsigned int txTrigLevel);

void UartInterruptEnable(unsigned int baseAdd, void (*fnHandler)(void));

#endif

