void UARTConsoleInit(void) {
}

void IntRegister(unsigned int intrNum, void (*fnHandler)(void)) {
}

void IntPrioritySet(unsigned int intrNum, unsigned int priority,
                    unsigned int hostIntRoute) {
}

void IntSystemEnable(unsigned int intrNum) {
}

void LogCString(unsigned char level, const char *message) {
}

signed char UARTCharGetNonBlocking(unsigned int baseAdd) {
}

unsigned int UARTCharPutNonBlocking(unsigned int baseAdd,
                                    unsigned char byteWrite) {
}

void UARTIntDisable(unsigned int baseAdd, unsigned int intFlag) {
}

void UARTIntEnable(unsigned int baseAdd, unsigned int intFlag) {
}

int main(int argc, char **argv) {
}
