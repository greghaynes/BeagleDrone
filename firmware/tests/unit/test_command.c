#include "tests/test_help.h"
#include "app/command.h"
#include "app/communication.h"

#include <assert.h>
#include <stdio.h>

static int commands_nav_init_called;
void CommandsNavInit() {
    commands_nav_init_called = 1;
}

static unsigned char nav_handler_type_id;
static const char *nav_handler_data;
void CommandsNavHandler(unsigned char type_id, const char *data) {
    nav_handler_type_id = type_id;
    nav_handler_data = data;
}

CommunicationState *CommunicationStateGet(void) {
    return 0;
}

void CommunicationSend(CommunicationState *com, const char *data, unsigned int size) {
}

static int last_log_level;

void LogCString(unsigned int level, const char *str) {
    last_log_level = level;
    printf("Log: %s\n", str);
}

void test_command_init(void) {
    commands_nav_init_called = 0;

    CommandInit();
    assert(commands_nav_init_called == 1);
}

void test_command_handle_raw(void) {
    // Set to non-sane value for debugging
    last_log_level = 0xFF;
    nav_handler_type_id = 0xFF;
    nav_handler_data = 0;

    const char *data = "\x02\x04\x03";
    CommandHandleRaw(data, 3);
    assert(last_log_level == 0xFF);
    assert(nav_handler_type_id == 0x02);
    assert(nav_handler_data == data);
}

void test_command_handle_raw_invalid(void) {
    // Set to non-sane value for debugging
    last_log_level = 0xFF;
    nav_handler_type_id = 0xFF;
    nav_handler_data = 0;

    const char *data = "\x05\xFF\x00";
    CommandHandleRaw(data, 3);
    assert(last_log_level == 0x03);
    assert(nav_handler_type_id == 0xFF);
    assert(nav_handler_data == 0);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Command Init", test_command_init },
        { "Command Handle Raw", test_command_handle_raw },
        { "Command Handle Raw (invalid)", test_command_handle_raw_invalid },
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}
