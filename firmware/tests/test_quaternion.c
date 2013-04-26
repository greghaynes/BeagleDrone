#include "tests/test_help.h"
#include "app/quaternion.h"

#include <stdio.h>

void QuaternionPrint(const Quaternion *q) {
    printf("Quaternion: %f\t%f\t%f\t%f\n",
           q->a, q->b, q->c, q->d);
}

void test_basic_quaternion_from_eulers(void) {
    Quaternion q = { 0, 0, 0, 0 };
    Vector3F eulers = { 0, 0, 0 };
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Basic quaternion from eulers", test_basic_quaternion_from_eulers },
        { 0, 0 }
    };

    run_tests(tests);
}

