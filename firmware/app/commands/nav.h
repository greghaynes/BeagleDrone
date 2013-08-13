#ifndef COMMANDS_NAV_H
#define COMMANDS_NAV_H

typedef enum CommandsNavType {
    COMMANDS_NAV_SET_ROT = 0
} CommandsNavType_t;

void CommandsNavInit(void);

void CommandsNavHandler(unsigned char type_id, const char *data);

#endif

