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
    assert(NearEqual(q.a, 0, .0001));
    assert(NearEqual(q.b, 1, .0001));
    assert(NearEqual(q.c, 0, .0001));
    assert(NearEqual(q.d, 0, .0001));

    eulers.a = PI_DIV_2;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    assert(NearEqual(q.a, 0.70, 0.01));
    assert(NearEqual(q.b, 0.70, 0.01));
    assert(q.c == 0);
    assert(q.d == 0);

    eulers.a = 0;
    eulers.b = PI_DIV_2;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    assert(NearEqual(q.a, 0.70, 0.01));
    assert(q.b == 0);
    assert(NearEqual(q.c, 0.70, 0.01));
    assert(q.d == 0);

    eulers.b = 0;
    eulers.c = PI_DIV_2;
    QuaternionFromEulers(&eulers, &q);
    QuaternionPrint(&q);
    assert(NearEqual(q.a, 0.70, 0.01));
    assert(q.b == 0);
    assert(q.c == 0);
    assert(NearEqual(q.d, 0.70, 0.01));
}

void test_basic_quaternion_to_eulers(void) {
    Vector3F eulers;
    Quaternion q = { 1, 0, 0, 0 };

    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);
    assert(eulers.a == 0);
    assert(eulers.b == 0);
    assert(eulers.c == 0);

    q.a = -0.0;
    q.b = 1.0;
    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);
    assert(NearEqual(eulers.a, PI, 0.001));
    assert(eulers.b == 0);
    assert(eulers.c == 0);

    q.a = 0.707141;
    q.b = 0.7073;
    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);
    assert(NearEqual(eulers.a, PI_DIV_2, 0.001));
    assert(eulers.b == 0);
    assert(eulers.c == 0);

    q.c = q.b;
    q.b = 0;
    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);
    assert(eulers.a == 0);
    assert(NearEqual(eulers.b, PI_DIV_2, 0.001));
    assert(eulers.c == 0);

    q.d = q.c;
    q.c = 0;
    QuaternionToEulers(&q, &eulers);
    Vector3fPrint(&eulers);
    assert(eulers.a == 0);
    assert(eulers.b == 0);
    assert(NearEqual(eulers.c, PI_DIV_2, 0.001));
}

void test_basic_quaternion_multiply(void) {
    Quaternion q = { 1, 0, 0, 0 };
    Quaternion r = { 1, 0, 0, 0 };
    Quaternion t;
    Vector3F eulers;

    QuaternionMultiply(&q, &r, &t);
    QuaternionPrint(&t);
    assert(t.a == 1);
    assert(t.b == 0);
    assert(t.c == 0);
    assert(t.d == 0);

    q.a = 0.707107;
    q.b = 0.707107;
    QuaternionMultiply(&q, &r, &t);
    QuaternionPrint(&t);
    QuaternionToEulers(&t, &eulers);
    assert(NearEqual(eulers.a, PI_DIV_2, 0.001));
    assert(eulers.b == 0);
    assert(eulers.c == 0);

    QuaternionMultiply(&q, &q, &t);
    QuaternionPrint(&t);
    QuaternionToEulers(&t, &eulers);
    assert(NearEqual(eulers.a, PI, 0.001));
    assert(eulers.b == 0);
    assert(eulers.c == 0);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Basic quaternion from eulers", test_basic_quaternion_from_eulers },
        { "Basic quaternion to eulers", test_basic_quaternion_to_eulers },
        { "Basic quaternion multiplication", test_basic_quaternion_multiply },
        { 0, 0 }
    };

    run_tests(tests);
}

