#include "kernel/drivers/uart_irda_cir.h"
#include "utils/uartConsole.h"
#include "communication.h"

static signed char uart_in_buff[COMMUNICATION_UART_IN_BUFF_SIZE];
static unsigned int uart_in_buff_used;

void CommunicationCheck(void) {
    signed char in_char = UARTCharGetNonBlocking(UART_CONSOLE_BASE);

    // Check if we got a char
    if(in_char == -1) {
        // No more chars to read
        return;
    }

    uart_in_buff[uart_in_buff_used++] = in_char;
}
