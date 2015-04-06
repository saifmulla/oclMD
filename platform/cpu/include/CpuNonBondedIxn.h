//
//  CpuNonBondedIxn.h
//  OclMD
//
//  Created by Saif Mulla on 03/04/2015.
//
//

#ifndef __OclMD__CpuNonBondedIxn__
#define __OclMD__CpuNonBondedIxn__

#include <vector>
#include "Vec3.h"

namespace OclMD {

class CpuNonBondedIxn {
public:
    CpuNonBondedIxn();//default constructor
    ~CpuNonBondedIxn();//destructor
    void calculateForces();
};
}
#endif /* defined(__OclMD__CpuNonBondedIxn__) */
