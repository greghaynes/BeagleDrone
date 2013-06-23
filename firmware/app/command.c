#include "app/communication.h"
#include "app/log.h"
#include "command.h"

#include <string.h>

char command_buffer[COMMUNICATION_UART_OUT_BUFF_SIZE];

void CommandHandleRaw(const char *data) {
    CommandTypeHeader *type_hdr = (CommandTypeHeader*)data;
    switch(type_hdr->type_id) {
        case COMMAND_TYPE_SET_ROT_SETPOINT:
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
