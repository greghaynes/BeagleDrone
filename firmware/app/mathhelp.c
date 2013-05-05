#include "mathhelp.h"

void Vector3FZero(Vector3F *v) {
    v->a = 0;
    v->b = 0;
    v->c = 0;
}

void Vector4FZero(Vector4F *v) {
    v->a = 0;
    v->b = 0;
    v->c = 0;
    v->d = 0;
}

int Vector3FEqual(const Vector3F *a, const Vector3F *b) {
    return a->a == b->a && a->b == b->b && a->c == b->c;
}

int Vector4FEqual(const Vector4F *a, const Vector4F *b) {
    return a->a == b->a && a->b == b->b && a->c == b->c && a->d == b->d;
}

// The well known 1/sqrt approximation
float ReciprocalSqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x*(1.5f-(xhalf*x*x));
    return x;
}
