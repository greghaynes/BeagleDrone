#include "tests/test_help.h"
#include "app/quaternion.h"

#include <stdio.h>
#include <assert.h>

void QuaternionPrint(const Quaternion *q) {
    printf("Quaternion: %f\t%f\t%f\t%f\n",
           q->a, q->b, q->c, q->d);
}

void test_basic_quaternion_from_eulers(void) {
    Quaternion q = { 0, 0, 0, 0 };

    Vector3F eulers = { 0, 0, 0 };
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    Vector4F res = { 1, 0, 0, 0 };
    assert(Vector4FEqual(&res, &q));

    eulers.a = 3.14159265;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    assert(q.a < .0001 && q.a > -.0001);
    assert(q.b < 1.0001 && q.b > .9999);
    assert(q.c < .0001 && q.c > -.0001);
    assert(q.c < .0001 && q.c > -.0001);

    eulers.a = 1.5707;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    assert(q.a < 0.71 && q.a > 0.7);
    assert(q.b < 0.71 && q.a > 0.7);
    assert(q.c == 0);
    assert(q.d == 0);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Basic quaternion from eulers", test_basic_quaternion_from_eulers },
        { 0, 0 }
    };

    run_tests(tests);
}

