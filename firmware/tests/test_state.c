#include "app/state.h"

#include <stdio.h>

void StatePrint(const State *state) {
    const StateRotationalFloat *rot_eulers = &state->rot_eulers;
    printf("Roll: %f\tPitch: %f\tYaw: %f\n",
           rot_eulers->roll,
           rot_eulers->pitch,
           rot_eulers->yaw);
}

int main(int argc, char **argv) {
    State s;
    StateInit(&s);
    StatePrint(&s);

    return 0;
}

