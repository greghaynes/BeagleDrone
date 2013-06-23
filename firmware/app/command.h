#ifndef COMMAND_H
#define COMMAND_H

#include "app/state.h"

typedef struct CommandTypeHeader {
    unsigned char type_id;
} CommandTypeHeader;

typedef enum {
    COMMAND_TYPE_LOG_MSG = 0,
    COMMAND_TYPE_SET_ROT_SETPOINT = 1,
} command_type_t;

typedef struct CommandLogMsgHeader {
    CommandTypeHeader type_header;
    unsigned char log_level;
} CommandLogMsgHeader;

typedef struct CommandSetRotSetpoint {
    CommandTypeHeader type_header;
    StateRotationalFloat rot_setpoint;
} CommandSetRotSetpoint;

void CommandHandleRaw(const char *data);

void CommandSend(const CommandTypeHeader *header, unsigned int header_size,
                  const char *data, unsigned int data_size);

#endif
