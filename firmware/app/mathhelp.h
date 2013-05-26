#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#define PI 3.141592653589793238462643383
#define PI_DIV_2 1.5707963267948966

typedef struct Vector3F {
    float a, b, c;
} Vector3F;

typedef struct Vector4F {
    float a, b, c, d;
} Vector4F;

void Vector3FZero(Vector3F *v);
void Vector4FZero(Vector4F *v);

void Vector4FCopy(const Vector4F *src, Vector4F *dest);

void Vector4FScale(const Vector4F *v, float c, Vector4F *dest);

void Vector4FAdd(const Vector4F *a, const Vector4F *b, Vector4F *dest);

int Vector3FEqual(const Vector3F *a, const Vector3F *b);
int Vector4FEqual(const Vector4F *a, const Vector4F *b);

int NearEqual(float a, float b, float error);

void MatrixMultiply3x3_4(const Vector3F *a,
                         const Vector4F *b,
                         Vector4F *dest);

#endif

