/* math.h */ 
/*----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//--------------------------------------------------------------------------------------*/

#ifndef XCore_math_h
#define XCore_math_h

#ifdef __STDBUILD
#include <sysroot/usr/include/limits.h>
#else
#include <limits.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* types */ 

typedef float float_t;

typedef double double_t;

/* float consts */ 

#define HUGE_VAL        (__builtin_huge_val())

#define HUGE_VALF       (__builtin_huge_valf())

#define HUGE_VALL       (__builtin_huge_vall())

#define INFINITY        (__builtin_inf())

#define NAN             __STD_UNDEFINED

/* float classes */ 

#define FP_ZERO         1

#define FP_SUBNORMAL    2

#define FP_NORMAL       3

#define FP_INFINITE     4

#define FP_NAN          5

/* ilogb consts */ 

#define FP_ILOGB0       (INT_MIN)

#define FP_ILOGBNAN     (INT_MAX)

/* error modes */ 

#define MATH_ERRNO      1

#define MATH_ERREXCEPT  2

extern int __std_math_errhandling();

#define math_errhandling   (__std_math_errhandling())

/* classification functions */ 

#define __std_isl(x) (sizeof ((x))==sizeof (long double))
#define __std_isd(x) (sizeof ((x))==sizeof (double))


extern int __std_fpclassf(float);
extern int __std_fpclass(double);
extern int __std_fpclassl(long double);

#define fpclassify(x) ( __std_isl(x)?__std_fpclassl((x)):( __std_isd(x)?__std_fpclass((x)):__std_fpclasslf((x)) ) )

extern int __std_isfinitef(float);
extern int __std_isfinite(double);
extern int __std_isfinitel(long double);

#define isfinite(x) ( __std_isl(x)?__std_isfinitel((x)):(__std_isd(x)?__std_isfinite((x)):__std_isfinitef((x)) ) )

extern int __std_isinff(float);
extern int __std_isinf(double);
extern int __std_isinfl(long double);

#define isinf(x) ( __std_isl(x)?__std_isinfl((x)):(__std_isd(x)?__std_isinf((x)):__std_isinff((x)) ) )

extern int __std_isnanf(float);
extern int __std_isnan(double);
extern int __std_isnanl(long double);

#define isnan(x) ( __std_isl(x)?__std_isnanl((x)):(__std_isd(x)?__std_isnan((x)):__std_isnanf((x)) ) )

extern int __std_isnormalf(float);
extern int __std_isnormal(double);
extern int __std_isnormall(long double);

#define isnormal(x) ( __std_isl(x)?__std_isnormall((x)):(__std_isd(x)?__std_isnormal((x)):__std_isnormalf((x)) ) )

extern int signbitf(float);
extern int signbit(double);
extern int signbitl(long double);

#define signbit(x) ( __std_isl(x)?__std_signbitl((x)):(__std_isd(x)?__std_signbit((x)):__std_signbitf((x)) ) )

/* trigonometric functions */ 

extern float acosf(float);
extern double acos(double);
extern long double acosl(long double);

extern float asinf(float);
extern double asin(double);
extern long double asinl(long double);

extern float atanf(float);
extern double atan(double);
extern long double atanl(long double);

extern float atan2f(float,float);
extern double atan2(double,double);
extern long double atan2l(long double,long double);

extern float cosf(float);
extern double cos(double);
extern long double cosl(long double);

extern float sinf(float);
extern double sin(double);
extern long double sinl(long double);

extern float tanf(float);
extern double tan(double);
extern long double tanl(long double);

/* hyperbolic functions */ 

extern float acoshf(float);
extern double acosh(double);
extern long double acoshl(long double);

extern float asinhf(float);
extern double asinh(double);
extern long double asinhl(long double);

extern float atanhf(float);
extern double atanh(double);
extern long double atanhl(long double);

extern float coshf(float);
extern double cosh(double);
extern long double coshl(long double);

extern float sinhf(float);
extern double sinh(double);
extern long double sinhl(long double);

extern float tanhf(float);
extern double tanh(double);
extern long double tanhl(long double);

/* exp and log functions */ 

extern float expf(float);
extern double exp(double);
extern long double expl(long double);

extern float exp2f(float);
extern double exp2(double);
extern long double exp2l(long double);

extern float expm1f(float);
extern double expm1(double);
extern long double expm1l(long double);

extern float frexpf(float,int *);
extern double frexp(double,int *);
extern long double frexpl(long double,int *);

extern int ilogbf(float);
extern int ilogb(double);
extern int ilogbl(long double);

extern float ldexpf(float,int);
extern double ldexp(double,int);
extern long double ldexpl(long double,int);

extern float logf(float);
extern double log(double);
extern long double logl(long double);

extern float log10f(float);
extern double log10(double);
extern long double log10l(long double);

extern float log1pf(float);
extern double log1p(double);
extern long double log1pl(long double);

extern float log2f(float);
extern double log2(double);
extern long double log2l(long double);

extern float logbf(float);
extern double logb(double);
extern long double logbl(long double);

extern float modff(float,float *);
extern double modf(double,double *);
extern long double modfl(long double,long double *);

extern float scalbnf(float,int);
extern double scalbn(double,int);
extern long double scalbnl(long double,int);

extern float scalblnf(float,long);
extern double scalbln(double,long);
extern long double scalblnl(long double,long);

/* pow and abs functions */ 

extern float cbrtf(float);
extern double cbrt(double);
extern long double cbrtl(long double);

extern float fabsf(float);
extern double fabs(double);
extern long double fabsl(long double);

extern float hypotf(float,float);
extern double hypot(double,double);
extern long double hypotl(long double,long double);

extern float powf(float,float);
extern double pow(double,double);
extern long double powl(long double,long double);

extern float sqrtf(float);
extern double sqrt(double);
extern long double sqrtl(long double);

/* error and gamma functions */ 

extern float erff(float);
extern double erf(double);
extern long double erfl(long double);

extern float erfcf(float);
extern double erfc(double);
extern long double erfcl(long double);

extern float lgammaf(float);
extern double lgamma(double);
extern long double lgammal(long double);

extern float tgammaf(float);
extern double tgamma(double);
extern long double tgammal(long double);

/* round functions */ 

extern float ceilf(float);
extern double ceil(double);
extern long double ceill(long double);

extern float floorf(float);
extern double floor(double);
extern long double floorl(long double);

extern float nearbyintf(float);
extern double nearbyint(double);
extern long double nearbyintl(long double);

extern float rintf(float);
extern double rint(double);
extern long double rintl(long double);

extern long lrintf(float);
extern long lrint(double);
extern long lrintl(long double);

extern long long llrintf(float);
extern long long llrint(double);
extern long long llrintl(long double);

extern float roundf(float);
extern double round(double);
extern long double roundl(long double);

extern long lroundf(float);
extern long lround(double);
extern long lroundl(long double);

extern long long llroundf(float);
extern long long llround(double);
extern long long llroundl(long double);

extern float truncf(float);
extern double trunc(double);
extern long double truncl(long double);

/* rem functions */ 

extern float fmodf(float,float);
extern double fmod(double,double);
extern long double fmodl(long double,long double);

extern float remainderf(float,float);
extern double remainder(double,double);
extern long double remainderl(long double,long double);

extern float remquof(float,float,int *);
extern double remquo(double,double,int *);
extern long double remquol(long double,long double,int *);

/* manipulation functions */ 

extern float copysignf(float,float);
extern double copysign(double,double);
extern long double copysignl(long double,long double);

extern float nanf(const char *);
extern double nan(const char *);
extern long double nanl(const char *);

extern float nextafterf(float,float);
extern double nextafter(double,double);
extern long double nextafterl(long double,long double);

extern float nexttowardf(float,long double);
extern double nexttoward(double,long double);
extern long double nexttowardl(long double,long double);

/* max min functions */ 

extern float fdimf(float,float);
extern double fdim(double,double);
extern long double fdiml(long double,long double);

extern float fminf(float,float);
extern double fmin(double,double);
extern long double fminl(long double,long double);

extern float fmaxf(float,float);
extern double fmax(double,double);
extern long double fmaxl(long double,long double);

/* multiply-add functions */ 

extern float fmaf(float,float,float);
extern double fma(double,double,double);
extern long double fmal(long double,long double,long double);

/* comparision functions */ 

extern int __std_isgreaterf(float,float);
extern int __std_isgreater(double,double);
extern int __std_isgreaterl(long double,long double);
 
#define isgreater(x,y)        __STD_UNDEFINED

#define isgreaterequal(x,y)   __STD_UNDEFINED

#define isless(x,y)           __STD_UNDEFINED

#define islessequal(x,y)      __STD_UNDEFINED

#define islessgreater(x,y)    __STD_UNDEFINED

#define isunordered(x,y)      __STD_UNDEFINED

#ifdef __cplusplus
} // extern "C"
#endif

#endif

