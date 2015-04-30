

#include "ContextImpl.h"
#include "System.h"
#include "ForceImpl.h"


/// default constructor
OclMD::ContextImpl::ContextImpl(System& system, Platform* platform):system_(system),platform_(platform),forceImpls_(0)
{
    /// first check if the system contains more than zero number of particles
    if(system.getNumParticles()==0)
        throw OclMDException("System cannot be 0 number of particles");

    /// if platform object not explicitly passed
    /// then consider default platform which is CPU
    if(platform_==NULL){
        CpuPlatform* platform = new CpuPlatform();
        platform_ = platform;
    }
    Platform::registerPlatform(platform_);
    platform_->createData(*this);
    
    std::string name = platform_->getPlatform().getName();
    std::cout << "Using Platform " << name.c_str() << std::endl;
    std::cout << "Initialising system with " << system.getNumParticles() << " Particles " << std::endl;
    /// get list of forceImpl from System list of forces in the system.
    for (int fi = 0; fi < system.getNumForces(); fi++) {
        forceImpls_.push_back(system.getForce(fi).createImpl());
        forceImpls_[fi]->initialise(*this);
    }
    
    /// once everything initialised
}

void* OclMD::ContextImpl::getPlatformData() const {
    return platformData_;
}

void OclMD::ContextImpl::setPlatformData(void* data){
    platformData_ = data;
}
void OclMD::ContextImpl::setPositions(std::vector<Vec3>& positions){
    
}

void OclMD::ContextImpl::getForces(std::vector<Vec3>& forces){
    
}

void OclMD::ContextImpl::CalculateForcesandEnergy(){
    
}

OclMD::System& OclMD::ContextImpl::getSystem(){
    return system_;
}
