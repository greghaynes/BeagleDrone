#ifndef COMMANDS_SYS_H
#define COMMANDS_SYS_H

typedef enum CommandsSysType {
    COMMANDS_SYS_TURN_ON = 0
} CommandsSysType_t;

void CommandsSysInit(void);

void CommandsSysHandler(unsigned char type_id, const char *data);

#endif

