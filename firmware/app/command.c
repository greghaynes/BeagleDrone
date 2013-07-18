#include "command.h"
#include "app/communication.h"
#include "app/log.h"

#include <string.h>

static char command_buffer[COMMUNICATION_UART_OUT_BUFF_SIZE];

static command_handler_t command_handlers[COMMAND_CNT];

void CommandInit(void) {
    int i;
    for(i = 0;i < COMMAND_CNT;++i)
        command_handlers[i] = 0;
}

void CommandSetHandler(unsigned char type_id, command_handler_t handler) {
    command_handlers[type_id] = handler;
}

void CommandHandleRaw(const char *data) {
    CommandTypeHeader *type_hdr = (CommandTypeHeader*)data;
    switch(type_hdr->type_id) {
        case COMMAND_TYPE_NAV:
            break;
        default:
            LogCString(LOG_LEVEL_ERROR, "Received invalid command id");
    }
}

void CommandSend(const CommandTypeHeader *header, unsigned int header_size,
                  const char *data, unsigned int data_size) {

    memcpy(command_buffer, header, header_size);
    memcpy(command_buffer + header_size, data, data_size);
    CommunicationSend(command_buffer, header_size + data_size);
}
