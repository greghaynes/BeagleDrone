#include "app/afproto.h"
#include "app/communication.h"
#include "app/state.h"
#include "tests/test_help.h"
#include "tests/mock/uart_driver.h"

#include <string.h>

void test_boot_communication(void) {
    UartMockDriverState uart;
    CommunicationState com;

    UartMockDriverStateInit(&uart);
    CommunicationInit(&com);

    // TODO:GAH Decoding and testing using app/afproto seems tautological
}

int main() {
    TestInfo tests[] = {
        { "Test Boot Communication", test_boot_communication },
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}
