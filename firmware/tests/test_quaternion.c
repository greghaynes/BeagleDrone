#include "tests/test_help.h"
#include "app/quaternion.h"

#include <stdio.h>
#include <assert.h>

void QuaternionPrint(const Quaternion *q) {
    printf("Quaternion: %f\t%f\t%f\t%f\n",
           q->a, q->b, q->c, q->d);
}

void Vector3fPrint(const Vector3F *v) {
    printf("Vector3F: %f\t%f\t%f\n",
            v->a, v->b, v->c);
}

void test_basic_quaternion_from_eulers(void) {
    Quaternion q = { 0, 0, 0, 0 };

    Vector3F eulers = { 0, 0, 0 };
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    Vector4F res = { 1, 0, 0, 0 };
    assert(Vector4FEqual(&res, &q));

    eulers.a = PI;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    assert(q.a < .0001 && q.a > -.0001);
    assert(q.b < 1.0001 && q.b > .9999);
    assert(q.c < .0001 && q.c > -.0001);
    assert(q.c < .0001 && q.c > -.0001);

    eulers.a = PI_DIV_2;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    assert(q.a < 0.71 && q.a > 0.7);
    assert(q.b < 0.71 && q.a > 0.7);
    assert(q.c == 0);
    assert(q.d == 0);

    eulers.a = 0;
    eulers.b = PI_DIV_2;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);

    eulers.b = 0;
    eulers.c = PI_DIV_2;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
}

void test_basic_quaternion_to_eulers(void) {
    Vector3F eulers;
    Quaternion q = { 1, 0, 0, 0 };

    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);

    q.a = -0.0;
    q.b = 1.0;
    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);

    q.a = 0.707141;
    q.b = 0.7073;
    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);

    q.c = q.b;
    q.b = 0;
    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);

    q.d = q.c;
    q.c = 0;
    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Basic quaternion from eulers", test_basic_quaternion_from_eulers },
        { "Basic quaternion to eulers", test_basic_quaternion_to_eulers },
        { 0, 0 }
    };

    run_tests(tests);
}

