#include "state.h"

void StateZeroRotationalShort(StateRotationalShort *state) {
    state->roll = 0;
    state->pitch = 0;
    state->yaw = 0;
}
