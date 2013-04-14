#include <math.h>

#include "quaternion.h"

void QuaternionFromEulers(const Vector3F *eulers, Quaternion *q) {
    float a_2 = eulers->a / 2;
    float b_2 = eulers->b / 2;
    float c_2 = eulers->c / 2;
    float cos_a_2 = cos(a_2);
    float cos_b_2 = cos(b_2);
    float cos_c_2 = cos(c_2);
    float sin_a_2 = sin(a_2);
    float sin_b_2 = sin(b_2);
    float sin_c_2 = sin(c_2);

    q->a = (cos_a_2 * cos_b_2 * cos_c_2) +
           (sin_a_2 * sin_b_2 * sin_c_2);

    q->b = (sin_a_2 * cos_b_2 * cos_c_2) -
           (cos_a_2 * sin_b_2 * sin_c_2);

    q->c = (cos_a_2 * sin_b_2 * cos_c_2) +
           (sin_a_2 * cos_b_2 * sin_c_2);

    q->d = (cos_a_2 * cos_b_2 * sin_c_2) -
           (sin_a_2 * sin_b_2 * cos_c_2);
}

void QuaternionToEulers(const Quaternion *q, Vector3F *dest) {
    dest->a = atanf((2 * ((q->a*q->b) + (q->c*q->d)))
        / (1 - (2 * ((q->b*q->b) + (q->c*q->c))))
        );
    dest->b = asinf(2 * ((q->a * q->c) - (q->d * q->b)));
    dest->c = atanf((2 * ((q->a * q->d) + (q->b * q->c)))
        / (1 - (2 * ((q->c*q->c) + (q->d*q->d))))
        );
}

void QuaternionMultiply(const Quaternion *q,
                        const Quaternion *r,
                        Quaternion *t) {
    t->a = (r->a * q->a) - (r->b * q->b) - (r->c * q->c) - (r->d * q->d);
    t->b = (r->a * q->b) + (r->b * q->a) - (r->c * q->d) + (r->d * q->c);
    t->c = (r->a * q->c) + (r->b * q->d) + (r->c * q->a) - (r->d * q->b);
    t->d = (r->a * q->d) - (r->b * q->c) + (r->c * q->b) + (r->d * q->a);
}
