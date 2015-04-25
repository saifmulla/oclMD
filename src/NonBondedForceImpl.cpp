//
//  NonBondedForceImpl.cpp
//  OclMD
//
//  Created by Saif Mulla on 24/04/2015.
//
//

#include "NonBondedForceImpl.h"
#include "OclMDException.h"

OclMD::NonBondedForceImpl::NonBondedForceImpl(NonBondedForce& owner)
:owner_(owner),ljPairs_(0),listParticles_(0),maxRcut_(0.0),maxRcutSqr_(0.0),
moleculeSize_(1),moleculeTypes_(1)
{
}

OclMD::NonBondedForceImpl::~NonBondedForceImpl(){
}


void OclMD::NonBondedForceImpl::initialise(ContextImpl& impl)
{
    /**
     * reinitialise all the setting specified inside the nonBondedForce 
     * class by using the object copied in the owner object.
     * essentially we are reinitialising to create an internal data structure
     * which will be completely private and which the algorithm is familiar with.
     */
    int particleInfoSize = owner_.getListParticleInfo().size();
    /// now allocate memory for the list of ParticleInfo array
    listParticles_ = new std::vector<NonBondedForce::ParticleInfo>(particleInfoSize);
    /// TODO: later ensure that check the mass of each particle to determine moleculeID
    
    for (int pi = 0; pi<particleInfoSize; pi++) {
        const NonBondedForce::ParticleInfo& tempPI = owner_.getListParticleInfo()[pi];
        (*listParticles_)[pi] = OclMD::NonBondedForce::ParticleInfo(Vec3(tempPI.siteReferencePosition_),
                                          tempPI.siteMass_,
                                          tempPI.siteCharge_,
                                          tempPI.fraction_,
                                          tempPI.siteId_,
                                          tempPI.moleculeId_);
    }
}

Real OclMD::NonBondedForceImpl::calculateForces(ContextImpl& impl){
    
}
