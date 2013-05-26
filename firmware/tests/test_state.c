#include "tests/test_help.h"
#include "app/state.h"

#include <stdio.h>
#include <assert.h>

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
    for(i = 0;i < 314159;i++) {
        StateUpdateRotFromAngVel(&s, &ang_vel, .001);
    }

    StatePrint(&s);
    Vector3F eulers;
    QuaternionToEulers(&s.r_b_to_i, &eulers);
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Basic state updating", test_single_axis_basic_rot_angvel_update },
        { "Single axis large rotation",
            test_single_axis_large_rot_angvel_update },
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}
