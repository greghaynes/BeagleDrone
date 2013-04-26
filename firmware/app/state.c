#include "mathtypes.h"
#include "state.h"

/*! \brief Update state from angular velocity */
void StateUpdateFromAngVel(State *state,
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

void StateInit(State *s) {
    Vector4FZero(&s->r_b_to_i);
    Vector3FZero((Vector3F*)&s->rot_eulers);
}

