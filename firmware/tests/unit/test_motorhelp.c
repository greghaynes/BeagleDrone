#include "app/motorhelp.h"
#include "tests/test_help.h"

#include <assert.h>

void test_motor_rescale(void) {
    MotorState s;
    s.a = .5;
    s.b = .5;
    s.c = .5;
    s.d = .5;

    MotorRescale(&s);
    assert(s.a == .5);
    assert(s.b == .5);
    assert(s.c == .5);
    assert(s.d == .5);

    s.a = 1.1;
    s.b = 0.5;
    s.c = 0.5;
    s.d = 0.5;
    MotorRescale(&s);
    assert(s.a <= 1.0 && s.a > 0.9);
    assert(s.b > 0.4 && s.b < 0.5);
    assert(s.c > 0.4 && s.c < 0.5);
    assert(s.d > 0.4 && s.d < 0.5);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Motor Rescale", test_motor_rescale }
    };

    run_tests(tests);
    return 0;
}

