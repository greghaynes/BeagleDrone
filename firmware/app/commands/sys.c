#include "app/commands/sys.h"
#include "app/command.h"

typedef struct CommandsSysHeader {
    CommandTypeHeader type_header;
    unsigned char sys_cmd;
} CommandsSysHeder;

void CommandsSysInit(void) {
    CommandSetHandler(COMMAND_TYPE_SYS, CommandsSysHandler);
}

void CommandsSysHandler(unsigned char type_id, const char *data) {
    CommandsSysHeader *hdr = (CommandsSysHeader*)data;
    data += 1;
    switch(hdr->nav_cmd) {
        case COMMANDS_SYS_TURN_ON:
            CommandsSysTurnOn(hdr, data);
    }
}

void CommandsSysTurnOn(CommandsSysHeader *hdr, const char *data) {
}

