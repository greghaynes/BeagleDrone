#include "app/communication.h"
#include "app/state.h"
#include "tests/test_help.h"

void test_commands_tun_on(void) {
    State s;
    CommunicationState com;
    StateInit(&s);
    CommunicationInit(&com);
}

int main() {
    TestInfo tests[] = {
        { "Turn On", test_commands_tun_on },
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}
