#ifndef COMMAND_H
#define COMMAND_H

typedef struct CommandTypeHeader {
    unsigned char type_id;
} CommandTypeHeader;

typedef enum {
    COMMAND_TYPE_LOG = 0,
    COMMAND_TYPE_NAV = 1,
    COMMAND_CNT = 2
} command_type_t;

typedef void (*command_handler_t)(unsigned char type_id, const char *data);

void CommandInit(void);

void CommandSetHandler(unsigned char type_id, command_handler_t handler);

void CommandHandleRaw(const char *data);

void CommandSend(const CommandTypeHeader *header, unsigned int header_size,
                  const char *data, unsigned int data_size);

#endif
