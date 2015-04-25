//
//  NonBondedForceImpl.h
//  OclMD
//
//  Created by Saif Mulla on 24/04/2015.
//
//

#ifndef OclMD_NonBondedForceImpl_h
#define OclMD_NonBondedForceImpl_h

#include <vector>
#include "RealType.h"
#include "ForceImpl.h"
#include "NonBondedForce.h"


namespace OclMD {

/// class declaration
class NonBondedForceImpl : public ForceImpl {

public:
    NonBondedForceImpl(NonBondedForce& force);
    ~NonBondedForceImpl();
    void initialise(ContextImpl& impl);

    /**
     * calculate pair-wise forces and also 
     * return total energy calculated between
     * the system.
     */
    Real calculateForces(ContextImpl& impl);
    
    Force& getOwner(){
        return owner_;
    }
private:
    NonBondedForce owner_;
    std::vector<NonBondedForce::LJPairs>* ljPairs_;
    std::vector<NonBondedForce::ParticleInfo>* listParticles_;
    Real maxRcut_;
    Real maxRcutSqr_;
    int moleculeSize_;
    int moleculeTypes_;
    
};
}// end namespace

#endif
