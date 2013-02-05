#include "kernel/drivers/uart_irda_cir.h"
#include "kernel/interrupt.h"
#include "utils/uartConsole.h"
#include "app/afproto.h"
#include "app/log.h"
#include "communication.h"

static signed char uart_in_buff[COMMUNICATION_UART_IN_BUFF_SIZE];
static unsigned int uart_in_buff_used;

static unsigned char uart_out_buff[COMMUNICATION_UART_OUT_BUFF_SIZE];
static unsigned int uart_out_buff_end;
static unsigned int uart_out_buff_start;

void UARTIsr(void);

void CommunicationCheckForFrame(void) {
}

void CommunicationsInit(void) {
    // Initialize UART peripheral
    UARTConsoleInit();

    // Register the UART ISR
    IntRegister(SYS_INT_UART0INT, UARTIsr);

    // Set interrupt priority
    IntPrioritySet(SYS_INT_UART0INT, 2, AINTC_HOSTINT_ROUTE_IRQ);

    // Enable system interrupt
    IntSystemEnable(SYS_INT_UART0INT);

    // Enable UART read interrupts
    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_RHR_CTI);
}

void CommunicationCheckWrite(void) {
    while(uart_out_buff_start != uart_out_buff_end) {
        // Try to put byte in transmit buffer
        if(UARTCharPutNonBlocking(UART_CONSOLE_BASE,
                                  uart_out_buff[uart_out_buff_start]))
            uart_out_buff_start++;
        else
            return;

        // Handle buffer wrapping
        if(uart_out_buff_start >= COMMUNICATION_UART_OUT_BUFF_SIZE)
            uart_out_buff_start = 0;
    }
    UARTIntDisable(UART_CONSOLE_BASE, UART_INT_THR);
}

void CommunicationCheckRead(void) {
    while(1) {
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
}

void CommunicationCheck(void) {
    CommunicationCheckRead();
    CommunicationCheckWrite();
}

void CommunicationSend(const char *data, unsigned int data_size) {
    if(data_size > COMMUNICATION_UART_OUT_BUFF_SIZE) {
        LogCString(LOG_LEVEL_ERROR, "Attempting to send message larger than"
                   " output buffer size, dropping message");
        return;
    }

    unsigned int i;
    for(i = 0;i < data_size;++i) {
        uart_out_buff[uart_out_buff_end++] = data[i];
        
        // Handle buffer wrap
        if(uart_out_buff_end >= COMMUNICATION_UART_OUT_BUFF_SIZE)
            uart_out_buff_end = 0;
    }

    UARTIntEnable(UART_CONSOLE_BASE, UART_INT_THR);
}

void UARTIsr(void) {
    CommunicationCheck();
}
