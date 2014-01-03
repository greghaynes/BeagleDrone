#ifndef COMMAND_H
#define COMMAND_H

typedef struct CommandTypeHeader {
    unsigned char type_id;
} CommandTypeHeader;

typedef enum {
    COMMAND_TYPE_LOG = 0,
    COMMAND_TYPE_SYS = 1,
    COMMAND_TYPE_NAV = 2,
    COMMAND_CNT = 3
} CommandType_t;

typedef void (*CommandHandler_t)(unsigned char type_id,
                                 const char *data,
                                 unsigned int size);

void CommandInit(void);

void CommandSetHandler(unsigned char type_id, CommandHandler_t handler);

void CommandHandleRaw(const char *data, unsigned int size);

void CommandSend(const CommandTypeHeader *header, unsigned int header_size,
                  const char *data, unsigned int data_size);

#endif
