//
//  NonBondedForce.h
//  OclMD
//
//  Created by Saif Mulla on 31/03/2015.
//
//

#ifndef OclMD_NonBondedForce_h
#define OclMD_NonBondedForce_h

#include <iostream>
#include <stdio.h>

#include "Force.h"

namespace OclMD {

class NonBondedForce : public Force {
public:
    enum NonBondedMethods{
        NoCutoff = 0,
        CutOffPeriodic = 1
    };
    NonBondedForce();
    NonBondedForce::NonBondedMethods getNonBondedMethod() const {
        return method_;
    }
    void setNonBondedMethod(NonBondedMethods method);
    void setCutOffDistance(double distance);
    double getCutOffDistance() const;
private:
    NonBondedMethods method_;
    double cutOffDistance_;
    
};// end class
    
}//end namespace
#endif
