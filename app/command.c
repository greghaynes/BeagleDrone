#include "app/communication.h"
#include "command.h"

void CommandSend(const CommandTypeHeader *header, unsigned int header_size,
                  const char *data, unsigned int data_size) {
    CommunicationSend((const char *)header, header_size);
    CommunicationSend(data, data_size);
}
