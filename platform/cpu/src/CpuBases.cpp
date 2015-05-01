//
//  CpuBases.cpp
//  OclMD
//
//  Created by Saif Mulla on 28/04/2015.
//
//

#include "CpuBases.h"


/// utility static functions

static std::vector<OclMD::Vec3>& extractPositions(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Vec3>*) data->positions_);
}

static std::vector<OclMD::Vec3>& extractForces(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Vec3>*) data->forces_);
}

static std::vector<OclMD::Tensor<double>>& extractVirial(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Tensor<double>>*) data->virial_);
}

static std::vector<double>& extractPE(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<double>*) data->pE_);
}


void OclMD::CpuBaseCalculateForcesAndEnergy::initialise(const System& system){
    
}

void OclMD::CpuBaseCalculateForcesAndEnergy::prepare(ContextImpl& context){
    
}

Real OclMD::CpuBaseCalculateForcesAndEnergy::calculate(ContextImpl& context){
    
}

/// definition of class CpuBaseData

void OclMD::CpuBaseData::initialise(const System& system){
    
}

void OclMD::CpuBaseData::setPositions(ContextImpl& context,
                                      const std::vector<Vec3>& positions){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<OclMD::Vec3>& dataPositions = extractPositions(context);
    for(int i = 0; i < numparticles; i++){
        dataPositions[i] = positions[i];
    }
    
}

void OclMD::CpuBaseData::getForces(ContextImpl& context,
                                   std::vector<Vec3>& forces){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<OclMD::Vec3>& dataForces = extractForces(context);
    for (int i = 0; i < numparticles; i++) {
        dataForces[i] = forces[i];
    }
    
}

void OclMD::CpuBaseData::setPeriodicBox(ContextImpl& context,
                                        const Vec3& x, const Vec3& y, const Vec3& z){
    
}

void OclMD::CpuBaseData::getPeriodicBox(ContextImpl& context,
                                        Vec3& x, Vec3& y, Vec3& z){
    
};


/// definition for class CpuCalculateNonBondedForceBase
void OclMD::CpuBaseCalculateNonBondedForce::initialise(const System& system,
                                                       const NonBondedForceImpl& force)
{
    nonbondedixn = new CpuNonBondedIxn((const OclMD::NonBondedForceImpl::LJInfo**) force.getLJInfo());
}

Real OclMD::CpuBaseCalculateNonBondedForce::calculate(ContextImpl& context)
{
    nonbondedixn->calculateForces(context.getSystem().getNumParticles(),
                                 extractPositions(context),
                                 extractForces(context),
                                 extractPE(context),
                                 extractVirial(context));
                                 
}

