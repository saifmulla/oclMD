//
//  Header.h
//  OclMD
//
//  Created by Saif Mulla on 01/04/2015.
//
//

#ifndef OclMD_Header_h
#define OclMD_Header_h

#include <cmath>
/**
 * if realtype is not set by default define it and set value to 2
 * 1 => float
 * 2 => double
 * 3 => long double
 */
#ifndef REALTYPE
#define REALTYPE 2
#endif

// check value of REALTYPE and set float and double accordingly
#if REALTYPE == 1
    typedef float Real;
#define REALSIZE 4
#define REALVAL 0.0f
#define SQRT sqrtf
#define POW powf
#define SIN sinf
#define COS cosf
#define TAN tanf

#elif REALTYPE == 2
    typedef double Real;
#define REALSIZE 8
#define REALVAL 0.0
#define SQRT sqrt
#define POW pow
#define SIN sin
#define COS cos
#define TAN tan

#elif REALTYPE == 3
    typedef long double Real;
#define REALSIZE 16
#define REALVAL 0.0
#define SQRT sqrtf
#define POW pow
#define SIN sin
#define COS cos
#define TAN tan

#endif
//end real check


#endif
