#include <math.h>

#include "quaternion.h"

void QuaternionZero(Quaternion *q) {
    q->a = 1;
    q->b = 0;
    q->c = 0;
    q->d = 0;
}

void QuaternionCopy(const Quaternion *src, Quaternion *dest) {
    Vector4FCopy(src, dest);
}

void QuaternionNormalize(Quaternion *q) {
    float n = q->a*q->a + q->b*q->b + q->c*q->c + q->d*q->d;
    if(n == 1)
        return;

    // TODO This could be made faster
    n = 1 / sqrt(n);
    q->a *= n;
    q->b *= n;
    q->c *= n;
    q->d *= n;
}

void QuaternionConjugate(Quaternion *q) {
    q->b = -q->b;
    q->c = -q->c;
    q->d = -q->d;
}

void QuaternionInvert(Quaternion *q) {
    QuaternionConjugate(q);
    Vector4FScale(q, 1 / Vector4FLengthSquared(q), q);
}

void QuaternionFromEulers(const Vector3F *eulers, Quaternion *q) {
    float r_2 = eulers->a / 2;
    float p_2 = eulers->b / 2;
    float y_2 = eulers->c / 2;

    float cos_r_2 = cos(r_2);
    float cos_p_2 = cos(p_2);
    float cos_y_2 = cos(y_2);

    float sin_r_2 = sin(r_2);
    float sin_p_2 = sin(p_2);
    float sin_y_2 = sin(y_2);

    float cpcy = cos_p_2 * cos_y_2;
    float spcy = sin_p_2 * cos_y_2;
    float cpsy = cos_p_2 * sin_y_2;
    float spsy = sin_p_2 * sin_y_2;

    q->a = cos_r_2 * cpcy + sin_r_2 * spsy;
    q->b = sin_r_2 * cpcy - cos_r_2 * spsy;
    q->c = cos_r_2 * spcy + sin_r_2 * cpsy;
    q->d = cos_r_2 * cpsy - sin_r_2 * spcy;

    QuaternionNormalize(q);
}

void QuaternionToEulers(const Quaternion *q, Vector3F *dest) {
    float sqa = q->a * q->a;
    float sqb = q->b * q->b;
    float sqc = q->c * q->c;
    float sqd = q->d * q->d;

    float v = 2.0 * (q->c * q->a - q->b * q->d);

    if(NearEqual(v, 1, .001)) {
        dest->a = 0;
        dest->b = PI_DIV_2;
        dest->c = -2.0 * atan2f(q->b, q->a);
    } else if (NearEqual(v, -1, .001)) {
        dest->a = 0;
        dest->b = PI_DIV_2;
        dest->c = 2.0 * atan2f(q->b, q->a);
    } else {
        dest->a = atan2f(2 * (q->c * q->d + q->b * q->a),
                         -sqb - sqc + sqd + sqa);
        dest->b = asinf(2 * (q->a * q->c - q->d * q->b));
        dest->c = atan2f(2.0 * (q->b * q->c + q->d * q->a),
                         sqb - sqc - sqd + sqa);
    }
}

void QuaternionMultiply(const Quaternion *q,
                        const Quaternion *r,
                        Quaternion *t) {
    t->a = (r->a * q->a) - (r->b * q->b) - (r->c * q->c) - (r->d * q->d);
    t->b = (r->a * q->b) + (r->b * q->a) - (r->c * q->d) + (r->d * q->c);
    t->c = (r->a * q->c) + (r->b * q->d) + (r->c * q->a) - (r->d * q->b);
    t->d = (r->a * q->d) - (r->b * q->c) + (r->c * q->b) + (r->d * q->a);
}

void QuaternionDifference(const Quaternion *a,
                          const Quaternion *b,
                          Quaternion *dest) {
    Quaternion tmp;
    QuaternionCopy(b, &tmp);
    QuaternionInvert(&tmp);
    QuaternionMultiply(a, &tmp, dest);
}

float QuaternionDotProduct(const Quaternion *a,
                           const Quaternion *b) {
    return (a->a * b->a) + (a->b * b->b) + (a->c * b->c) + (a->d * b->d);
}

void QuaternionLerp(const Quaternion *a,
                     const Quaternion *b,
                     float t,
                     Quaternion *dest) {
    Quaternion tmp;
    Vector4FScale(a, 1-t, dest);
    Vector4FScale(b, t, &tmp);
    Vector4FAdd(dest, &tmp, dest);
    QuaternionNormalize(dest);
}
