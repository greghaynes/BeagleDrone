#ifndef COMMAND_H
#define COMMAND_H

typedef struct CommandTypeHeader {
    unsigned char type_id;
} CommandTypeHeader;

#define COMMAND_TYPE_LOG_MSG 0

typedef struct CommandLogMsgHeader {
    CommandTypeHeader type_header;
    unsigned char log_level;
} CommandLogMsgHeader;

void CommandSend(const CommandTypeHeader *header, unsigned int header_size,
                  const char *data, unsigned int data_size);

#endif
