#include "app/ahrs.h"
#include "app/communication.h"
#include "tests/test_help.h"
#include "tests/mock/uart_driver.h"

void test_commands_tun_on(void) {
    UartMockDriverState uart;
    AhrsState s;
    CommunicationState com;

    UartMockDriverStateInit(&uart);
    AhrsInit(&s);
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
