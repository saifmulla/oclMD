//
//  NonBondedForceImpl.h
//  OclMD
//
//  Created by Saif Mulla on 24/04/2015.
//
//

#ifndef OclMD_NonBondedForceImpl_h
#define OclMD_NonBondedForceImpl_h

#include <cstdlib>
#include <vector>
#include "oclmd/RealType.h"
#include "oclmd/Base.h"
#include "oclmd/NonBondedForce.h"
#include "oclmd/impl/ForceImpl.h"


namespace OclMD {

/// class declaration
class NonBondedForceImpl : public ForceImpl {

public:
    class LJInfo{
    public:
        Real sigma;
        Real epsilon;
        Real rMin;
        Real dr;
        Real rCut;
        Real rCutSqr;

        LJInfo():sigma(0.0),epsilon(0.0),rMin(0.0),
        dr(0.0),rCut(0.0),rCutSqr(0.0){}
        LJInfo(Real s, Real e, Real rm, Real dr, Real rc, Real rcs)
        :sigma(s),epsilon(e),rMin(rm),
        dr(dr),rCut(rc),rCutSqr(rcs){}
    };

    NonBondedForceImpl(NonBondedForce& force);
    ~NonBondedForceImpl();
    void initialise(ContextImpl& context);

    /**
     * calculate pair-wise forces and also 
     * return total energy calculated between
     * the system.
     */
    Real calculateForces(ContextImpl& context);
    
    /**
     * invoke any preprocessing functionality
     * before calculating forces.
     */
    void prepare(ContextImpl& context);
    
    Force& getOwner(){
        return owner_;
    }
    
    /// get LJpair by two indexes
    LJInfo* getLJInfo(int i,int j){
        return &ljPairs_[i][j];
    }
    
    LJInfo** getLJInfo() const;
    
private:
    NonBondedForce owner_;
    LJInfo** ljPairs_;
    std::vector<NonBondedForce::ParticleInfo>* listParticles_;
    int* siteIds_;
    Real maxRcut_;
    Real maxRcutSqr_;
    Base baseKernel_;
//    int moleculeSize_;
//    int moleculeTypes_;
    
};
}// end namespace

#endif
