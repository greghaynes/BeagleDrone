#include "tests/test_help.h"
#include "app/state.h"

#include <stdio.h>
#include <assert.h>

void QuaternionPrint(const Quaternion *q, const char *label) {
    Vector3F eulers;
    QuaternionToEulers(q, &eulers);
    printf("%s: x: %f\ty: %f\tz: %f\n", label, eulers.a, eulers.b,
           eulers.c);
}

void StateErrorPrint(const State *state) {
    QuaternionPrint(&state->error_p, "Error (P)");
    QuaternionPrint(&state->error_i, "Error (I)");
    QuaternionPrint(&state->error_d, "Error (D)");
}

void StatePrint(const State *state) {
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
    State s;
    StateInit(&s);
    StatePrint(&s);

    int i;
    StateRotationalFloat ang_vel = { 1, 0, 0 };
    for(i = 0;i < 100;i++) {
        StateUpdateRotFromAngVel(&s, &ang_vel, .001);
    }

    StatePrint(&s);
    Vector3F eulers;
    QuaternionToEulers(&s.r_b_to_i, &eulers);
    assert(NearEqual(eulers.a, 0.1, 0.001));
    assert(eulers.b == 0);
    assert(eulers.c == 0);
}

void test_single_axis_large_rot_angvel_update(void) {
    State s;
    StateInit(&s);
    StatePrint(&s);

    int i;
    StateRotationalFloat ang_vel = { 1, 0, 0 };
    for(i = 0;i < 3160;i++) {
        StateUpdateRotFromAngVel(&s, &ang_vel, .001);
    }

    StatePrint(&s);
    Vector3F eulers;
    QuaternionToEulers(&s.r_b_to_i, &eulers);
    assert(NearEqual(eulers.a, -3.12, 0.1));
    assert(eulers.b == 0);
    assert(eulers.c == 0);
}

void test_multi_axis_basic_rot_angvel_update(void) {
    State s;
    StateInit(&s);
    StatePrint(&s);

    int i;
    StateRotationalFloat ang_vel = { 1, 1, 0 };
    for(i = 0;i < 3160;i++) {
        StateUpdateRotFromAngVel(&s, &ang_vel, .001);
    }

    StatePrint(&s);
}

void test_error_update(void) {
    State s;
    Quaternion error;
    Vector3F eulers = {.001, 0, 0};
    StateInit(&s);
    QuaternionFromEulers(&eulers, &error);

    StateUpdateError(&s, &error, .001);
    StateErrorPrint(&s);
    StateUpdateError(&s, &error, .001);
    StateErrorPrint(&s);
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

