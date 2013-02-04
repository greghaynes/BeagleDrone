#include "app/command.h"

void LogMessage(unsigned char level, const char *message, unsigned int size) {
    CommandLogMsgHeader hdr;
    hdr.type_header.type_id = COMMAND_TYPE_LOG_MSG;
    hdr.log_level = level;
    CommandSend((CommandTypeHeader*)&hdr, sizeof(CommandLogMsgHeader), message, size);
}

void LogCString(unsigned char level, const char *message) {
    unsigned int size = 0;
    while(message[size++]);
    LogMessage(level, message, size-1);
}
