#pragma once

#if !defined(FLT_EVAL_METHOD) || FLT_EVAL_METHOD <= 0 || FLT_EVAL_METHOD > 2

typedef float float_t;
typedef double double_t;

#elif FLT_EVAL_METHOD == 1

typedef double float_t;
typedef double double_t;

#elif FLT_EVAL_METHOD == 2

typedef long double float_t;
typedef long double double_t;

#endif

#define MATH_ERRNO 1
#define MATH_ERREXCEPT 2

#define HUGE_VAL 0
#define HUGE_VALF 0
#define HUGE_VALL 0

#define INFINITY 0

#define NAN 0

#define FP_INFINITE 0
#define FP_NAN 0
#define FP_NORMAL 0
#define FP_SUBNORMAL 0
#define FP_ZERO 0

double modf(double v, double* iptr);

float modff(float v, float* iptr);

long double modfl(long double v, long double* iptr);
