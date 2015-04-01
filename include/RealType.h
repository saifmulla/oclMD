//
//  Header.h
//  OclMD
//
//  Created by Saif Mulla on 01/04/2015.
//
//

#ifndef OclMD_Header_h
#define OclMD_Header_h


/**
 * if realtype is not set by default define it and set value to 2
 * 1 => float
 * 2 => double
 */
#ifndef REALTYPE
#define REALTYPE 2
#endif

// check value of REALTYPE and set float and double accordingly
#if REALTYPE == 1
    typedef float Real;
#else
    typedef double Real;
#endif
//end real check


#endif
