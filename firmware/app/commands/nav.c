#include "app/commands/nav.h"
#include "app/command.h"

typedef struct CommandsNavHeader {
    CommandTypeHeader type_header;
    unsigned char nav_cmd;
} CommandsNavHeader;

void CommandsNavInit(void) {
    CommandSetHandler(COMMAND_TYPE_NAV, CommandsNavHandler);
}

void CommandsNavSetRot(CommandsNavHeader *hdr, const char *data) {
}

void CommandsNavHandler(unsigned char type_id, const char *data) {
    CommandsNavHeader *hdr = (CommandsNavHeader*)data;
    data += 1;
    switch(hdr->nav_cmd) {
        case COMMANDS_NAV_SET_ROT:
            CommandsNavSetRot(hdr, data);
    }
}
