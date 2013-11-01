#include "app/motorstate.h"
#include "tests/test_help.h"

void test_motor_rescale(void) {
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Motor Rescale", test_motor_rescale }
    };

    run_tests(tests);
    return 0;
}

