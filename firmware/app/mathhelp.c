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

void Vector4FCopy(const Vector4F *src, Vector4F *dest) {
    dest->a = src->a;
    dest->b = src->b;
    dest->c = src->c;
    dest->d = src->d;
}

float Vector4FLengthSquared(const Vector4F *v) {
    return (v->a * v->a) + (v->b * v->b) +
           (v->c * v->c) + (v->d * v->d);
}

void Vector4FScale(const Vector4F *v, float c, Vector4F *dest) {
    dest->a = v->a * c;
    dest->b = v->b * c;
    dest->c = v->c * c;
    dest->d = v->d * c;
}

void Vector4FAdd(const Vector4F *a, const Vector4F *b, Vector4F *dest) {
    dest->a = a->a + b->a;
    dest->b = a->b + b->b;
    dest->c = a->c + b->c;
    dest->d = a->d + b->d;
}

int Vector3FEqual(const Vector3F *a, const Vector3F *b) {
    return a->a == b->a && a->b == b->b && a->c == b->c;
}

int Vector4FEqual(const Vector4F *a, const Vector4F *b) {
    return a->a == b->a && a->b == b->b && a->c == b->c && a->d == b->d;
}

int NearEqual(float a, float b, float error) {
    return a < (b + error) && a > (b - error);
}

void MatrixMultiply3x3_4(const Vector3F *a,
                         const Vector4F *b,
                         Vector4F *result) {
    int i, j;
    float *a_f = (float*)a;
    float **b_f = (float**)b;
    float *res_f = (float*)result;
    float sum;

    for(i = 0; i < 4; ++i) {
        sum = 0;
        for(j = 0;j < 3;++j) {
            sum += a_f[j] * b_f[j][i];
        }

        res_f[i] = sum;
    }
}
