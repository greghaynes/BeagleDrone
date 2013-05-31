#include "mathhelp.h"
#include "state.h"

static MotorState p_gains[3] = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 } };

static MotorState i_gains[3] = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 } };

static MotorState d_gains[3] = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 } };

/* Scale values propotionally so no value is over 1 */
void MotorRescale(MotorState *s) {
    float *vals = (float*)s;
    int i;
    int max_ndx = 0;
    for(i = 1;i < 4;++i) {
        if(vals[i] > vals[max_ndx])
            max_ndx = i;
    }

    if(max_ndx > 1) {
        // Rescale
        float scale = 1 / vals[max_ndx];
        for(i = 0;i < 4;++i)
            vals[i] *= scale;
    }
}

void StateSetSetpoint(State *state,
                      const Vector3F *eulers) {
    QuaternionFromEulers(eulers, &state->setpoint);
}

void StateUpdateError(State *state,
                      const Quaternion *error,
                      float time_delta) {
    Quaternion tmp, err_delta, q_dt;
    QuaternionCopy(&state->error_p, &tmp);
    QuaternionZero(&q_dt);

    // Set error_p
    QuaternionCopy(error, &state->error_p);

    // Calculate error_d
    QuaternionDifference(error, &tmp, &err_delta);
    QuaternionLerp(&q_dt, &err_delta, 1 / time_delta, &state->error_d);

    // This only works for small values of error!
    QuaternionLerp(error, &q_dt, time_delta, &q_dt);
    QuaternionMultiply(&q_dt, &state->error_i, &state->error_i);
}

void StateUpdateMotors(State *state) {
    MotorState *motors = &state->motor_state;

    // P
    MotorState p_state;
    Vector3F eulers;
    QuaternionToEulers(&state->error_p, &eulers);
    MatrixMultiply3x3_4(&eulers, p_gains, &p_state);

    // I
    MotorState i_state;
    QuaternionToEulers(&state->error_i, &eulers);
    MatrixMultiply3x3_4(&eulers, i_gains, &i_state);

    // D
    MotorState d_state;
    QuaternionToEulers(&state->error_d, &eulers);
    MatrixMultiply3x3_4(&eulers, d_gains, &d_state);

    Vector4FZero(motors);
    Vector4FAdd(&p_state, motors, motors);
    Vector4FAdd(&i_state, motors, motors);
    Vector4FAdd(&d_state, motors, motors);

    MotorRescale(motors);
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
    Quaternion error;
    StateUpdateRotFromAngVel(state, ang_vel, time_delta);
    QuaternionDifference(&state->r_b_to_i, &state->setpoint, &error);
    StateUpdateError(state, &error, time_delta);
}

void StateInit(State *s) {
    QuaternionZero(&s->r_b_to_i);
    QuaternionZero(&s->setpoint);
    QuaternionZero(&s->error_p);
    QuaternionZero(&s->error_i);
    QuaternionZero(&s->error_d);
    Vector4FZero(&s->motor_state);
}

