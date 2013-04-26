#include "tests/test_help.h"
#include "app/state.h"

#include <stdio.h>

void StatePrint(const State *state) {
    const StateRotationalFloat *rot_eulers = &state->rot_eulers;
    printf("Roll: %f\tPitch: %f\tYaw: %f\n",
           rot_eulers->roll,
           rot_eulers->pitch,
           rot_eulers->yaw);
}

int test_basic_state_angvel_update(void) {
    State s;
    StateInit(&s);
    StatePrint(&s);

    int i;
    StateRotationalFloat ang_vel = { 1, 0, 0 };
    for(i = 0;i < 100;i++) {
        StateUpdateFromAngVel(&s, &ang_vel, .01);
    }

    StatePrint(&s);
    return 0;
}

int main(int argc, char **argv) {
    TestInfo tests[] = {
        { "Basic state updating", test_basic_state_angvel_update },
        { 0, 0 }
    };

    run_tests(tests);
    return 0;
}

