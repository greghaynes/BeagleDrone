#include "tests/test_help.h"
#include "app/ahrs.h"

#include <stdio.h>
#include <assert.h>

void QuaternionPrint(const Quaternion *q, const char *label) {
    Vector3F eulers;
    QuaternionToEulers(q, &eulers);
    printf("%s: x: %f\ty: %f\tz: %f\n", label, eulers.a, eulers.b,
           eulers.c);
}

void AhrsErrorPrint(const AhrsState *state) {
    QuaternionPrint(&state->error_p, "Error (P)");
    QuaternionPrint(&state->error_i, "Error (I)");
    QuaternionPrint(&state->error_d, "Error (D)");
}

void AhrsPrint(const AhrsState *state) {
    const Quaternion *q = &state->r_b_to_i;
    printf("state:\t");
    printf("a: %f\tb: %f\tc: %f\td: %f\n",
           q->a, q->b, q->c, q->d);
    Vector3F eulers;
    QuaternionToEulers(q, &eulers);
    printf("x: %f\ty: %f\tz: %f\n",
            eulers.a, eulers.b, eulers.c);
}

void test_single_axis_basic_rot_angvel_update(void) {
    AhrsState s;
    AhrsInit(&s);
    AhrsPrint(&s);

    int i;
    AhrsRotationalFloat ang_vel = { 1, 0, 0 };
    for(i = 0;i < 100;i++) {
        AhrsUpdateRotFromAngVel(&s, &ang_vel, .001);
    }

    AhrsPrint(&s);
    Vector3F eulers;
    QuaternionToEulers(&s.r_b_to_i, &eulers);
    assert(NearEqual(eulers.a, 0.1, 0.001));
    assert(eulers.b == 0);
    assert(eulers.c == 0);
}

void test_single_axis_large_rot_angvel_update(void) {
    AhrsState s;
    AhrsInit(&s);
    AhrsPrint(&s);

    int i;
    AhrsRotationalFloat ang_vel = { 1, 0, 0 };
    for(i = 0;i < 3160;i++) {
        AhrsUpdateRotFromAngVel(&s, &ang_vel, .001);
    }

    AhrsPrint(&s);
    Vector3F eulers;
    QuaternionToEulers(&s.r_b_to_i, &eulers);
    assert(NearEqual(eulers.a, -3.12, 0.1));
    assert(eulers.b == 0);
    assert(eulers.c == 0);
}

void test_multi_axis_basic_rot_angvel_update(void) {
    AhrsState s;
    AhrsInit(&s);
    AhrsPrint(&s);

    int i;
    AhrsRotationalFloat ang_vel = { 1, 1, 0 };
    for(i = 0;i < 3160;i++) {
        AhrsUpdateRotFromAngVel(&s, &ang_vel, .001);
    }

    AhrsPrint(&s);
    //TODO:GAH what vals do we expect?
}

void test_error_update(void) {
    AhrsState s;
    Quaternion error;
    Vector3F eulers = {.001, 0, 0};
    AhrsInit(&s);
    QuaternionFromEulers(&eulers, &error);

    AhrsUpdateError(&s, &error, .001);
    AhrsErrorPrint(&s);
    QuaternionToEulers(&s.error_p, &eulers);
    assert(NearEqual(eulers.a, 0.001, .0001));
    QuaternionToEulers(&s.error_i, &eulers);
    assert(NearEqual(eulers.a, 0.001, .0001));
    QuaternionToEulers(&s.error_d, &eulers);
    assert(NearEqual(eulers.a, 1, 0.1));

    AhrsUpdateError(&s, &error, .001);
    QuaternionToEulers(&s.error_p, &eulers);
    assert(NearEqual(eulers.a, 0.001, .0001));
    QuaternionToEulers(&s.error_i, &eulers);
    assert(NearEqual(eulers.a, 0.002, .0001));
    QuaternionToEulers(&s.error_d, &eulers);
    assert(NearEqual(eulers.a, 0, 0.001));
    AhrsErrorPrint(&s);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Basic rotation updating",
            test_single_axis_basic_rot_angvel_update },
        { "Single axis large rotation",
            test_single_axis_large_rot_angvel_update },
        { "Basic multi axis rotation updating",
            test_multi_axis_basic_rot_angvel_update},
        { "Error updating",
            test_error_update},
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}

