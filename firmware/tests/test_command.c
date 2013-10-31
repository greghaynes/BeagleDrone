#include "tests/test_help.h"
#include "app/command.h"

#include <assert.h>
#include <stdio.h>

static int commands_nav_init_called;
void CommandsNavInit() {
    commands_nav_init_called = 1;
}

void CommunicationSend(const char *data, unsigned int size) {
}

void LogCString(unsigned int level, const char *str) {
    printf("Log: %s\n", str);
}

void test_command_init(void) {
    commands_nav_init_called = 0;

    CommandInit();
    assert(commands_nav_init_called == 1);
}

void test_command_handle_raw(void) {
    
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Command Init", test_command_init },
        { "Command Handle Raw", test_command_handle_raw },
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}
