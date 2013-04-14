#include "mathtypes.h"
#include "state.h"

void StateZeroRotationalShort(StateRotationalShort *state) {
    state->roll = 0;
    state->pitch = 0;
    state->yaw = 0;
}

/*! \brief Update state from angular velocity */
void StateUpdateFromAngVel(StateFull *state,
                           const StateRotationalFloat *ang_vel,
                           float time_delta) {
    Quaternion *rot_quat = &state->r_b_to_i;

    // We are going to just scale each euler angle independently
    // and load them into a quaternion. This 'works' given that the
    // rotations are sufficiently small that the error can be ignored.
    Vector3F delta_eulers;
    Quaternion delta_quat;
    delta_eulers.a = ang_vel->roll * time_delta;
    delta_eulers.b = ang_vel->pitch * time_delta;
    delta_eulers.c = ang_vel->yaw * time_delta;
    QuaternionFromEulers(&delta_eulers, &delta_quat);

    // Update our rotational state
    QuaternionMultiply(&delta_quat, rot_quat, rot_quat);
}

#ifdef STATE_TEST

int main(int argc, char **argv) {
}

#endif

