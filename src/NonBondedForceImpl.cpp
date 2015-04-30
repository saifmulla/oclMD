//
//  NonBondedForceImpl.cpp
//  OclMD
//
//  Created by Saif Mulla on 24/04/2015.
//
//
#include "OclMDException.h"
#include "ContextImpl.h"
#include "NonBondedForceImpl.h"


OclMD::NonBondedForceImpl::NonBondedForceImpl(NonBondedForce& owner)
:owner_(owner),ljPairs_(0),listParticles_(0),maxRcut_(0.0),maxRcutSqr_(0.0),
siteIds_(0)
{
}

OclMD::NonBondedForceImpl::~NonBondedForceImpl(){
}

OclMD::NonBondedForceImpl::LJInfo** OclMD::NonBondedForceImpl::getLJInfo() const {
    return ljPairs_;
}

void OclMD::NonBondedForceImpl::initialise(ContextImpl& impl)
{

#ifdef FULLDEBUG
    std::cout << "Initialising NonBondedForceImpl " << std::endl;
#endif
    /**
     * reinitialise all the setting specified inside the nonBondedForce 
     * class by using the object copied in the owner object.
     * essentially we are reinitialising to create an internal data structure
     * which will be completely private and which the algorithm is familiar with.
     */
    int particleInfoSize = owner_.getListParticleInfo().size();
    /// now allocate memory for the list of ParticleInfo array
    listParticles_ = new std::vector<NonBondedForce::ParticleInfo>(particleInfoSize);
    /// initialise siteId list
    siteIds_ = (int*) malloc(sizeof(int)*particleInfoSize);
    /// TODO: later ensure that check the mass of each particle to determine moleculeID
    
    for (int pi = 0; pi<particleInfoSize; pi++) {
        const NonBondedForce::ParticleInfo& tempPI = owner_.getListParticleInfo()[pi];
        (*listParticles_)[pi] = OclMD::NonBondedForce::ParticleInfo(
                                          Vec3(tempPI.siteReferencePosition_),
                                          tempPI.siteMass_,
                                          tempPI.siteCharge_,
                                          tempPI.fraction_,
                                          tempPI.siteId_,
                                          tempPI.moleculeId_);
        siteIds_[pi] = pi;
    }
    
    /// now setup LJPairs information
    particleInfoSize = owner_.getListLJPairs().size();
    /// lazy initialise memory
    ljPairs_ = new LJInfo*[particleInfoSize];
    for (int lj = 0; lj<particleInfoSize; lj++) {
        const NonBondedForce::LJPairs& templj = owner_.getListLJPairs()[lj];
        ljPairs_[lj] = new LJInfo[1];
        ljPairs_[lj][0] = LJInfo(templj.sigma_,templj.epsilon_,templj.rMin_,
                                 templj.dr_,templj.rCut_,templj.rCutSqr_);
    }
    
}

Real OclMD::NonBondedForceImpl::calculateForces(ContextImpl& impl){
    
}
