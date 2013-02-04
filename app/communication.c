#include "kernel/drivers/uart_irda_cir.h"
#include "kernel/sysdelay.h"
#include "kernel/interrupt.h"
#include "utils/uartConsole.h"
#include "app/afproto.h"
#include "app/log.h"
#include "communication.h"

static signed char uart_in_buff[COMMUNICATION_UART_IN_BUFF_SIZE];
static unsigned int uart_in_buff_used;

void UARTIsr(void);

void CommunicationCheckForFrame(void) {
}

void CommunicationsInit(void) {
    UARTConsoleInit();

    IntRegister(SYS_INT_UART0INT, UARTIsr);
    IntPrioritySet(SYS_INT_UART0INT, 2, AINTC_HOSTINT_ROUTE_IRQ);
    IntSystemEnable(SYS_INT_UART0INT);

    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_THR);
    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_RHR_CTI);
}

void CommunicationCheckWrite(void) {
}

void CommunicationCheckRead(void) {
    SysStartTimer(COMMUNICATION_CHECK_MAX_TIME);

    while(!SysIsTimerElapsed()) {
        signed char in_char = UARTCharGetNonBlocking(UART_CONSOLE_BASE);

        // Check if we got a char
        if(in_char == -1) {
            // No more chars to read
            return;
        }

        uart_in_buff[uart_in_buff_used++] = in_char;
        // We might have hit the end of a frame
        if(in_char == AFPROTO_END_BYTE) {
            CommunicationCheckForFrame();
        }
    }

    // We ran out of time
    LogCString(LOG_LEVEL_WARNING, "Ran out of time while reading communication "
               "input buffer");
}

void CommunicationCheck(void) {
    CommunicationCheckRead();
    CommunicationCheckWrite();
}

void CommunicationSend(const char *data, unsigned int data_size) {
}

void UARTIsr(void) {
    CommunicationCheck();
}
