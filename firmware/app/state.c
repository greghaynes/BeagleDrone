#include "mathhelp.h"
#include "state.h"

void StateSetSetpoint(State *state,
                      const Vector3F *eulers) {
    QuaternionFromEulers(eulers, &state->setpoint);
}

void StateUpdateError(State *state,
                      const Quaternion *error,
                      float time_delta) {
    Quaternion q_dt;
    QuaternionCopy(error, &state->error_p);

    // This only works for small values of error!
    QuaternionCopy(error, &q_dt);
}

void StateUpdateRotFromAngVel(State *state,
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
    QuaternionMultiply(rot_quat, &delta_quat, rot_quat);
    QuaternionNormalize(rot_quat);
}

/*! \brief Update state from angular velocity */
void StateUpdateFromAngVel(State *state,
                           const StateRotationalFloat *ang_vel,
                           float time_delta) {
    StateUpdateRotFromAngVel(state, ang_vel, time_delta);
}

void StateInit(State *s) {
    QuaternionZero(&s->r_b_to_i);
    QuaternionZero(&s->setpoint);
    QuaternionZero(&s->error_p);
    QuaternionZero(&s->error_i);
    QuaternionZero(&s->error_d);
    Vector3FZero((Vector3F*)&s->rot_eulers);
}

