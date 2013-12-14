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
}

/* Returns 0 if no char available, 1 otherwise */
int UartGetCharNonBlocking(unsigned int baseAdd, unsigned char *data) {
    return 0;
}

unsigned int UARTCharPutNonBlocking(unsigned int baseAdd,
                                    unsigned char byteWrite) {
    return 0;
}

void UARTIntDisable(unsigned int baseAdd, unsigned int intFlag) {
}

void UARTIntEnable(unsigned int baseAdd, unsigned int intFlag) {
}
