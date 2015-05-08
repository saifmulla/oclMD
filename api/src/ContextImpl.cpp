
#include "oclmd/Base.h"
#include "oclmd/BaseInterfaces.h"
#include "oclmd/System.h"
#include "oclmd/Force.h"
#include "oclmd/impl/ContextImpl.h"
#include "oclmd/impl/ForceImpl.h"


/// default constructor
OclMD::ContextImpl::ContextImpl(System& system, Platform* platform)
:system_(system),forceImpls_(0),platform_(platform)
{
    /// first check if the system contains more than zero number of particles
    if(system.getNumParticles()==0)
        throw OclMDException("System cannot be 0 number of particles");

    /// if platform object not explicitly passed
    /// then consider default platform which is CPU
    if(platform_==0){
//        CpuPlatform* platform = new CpuPlatform();
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
    
    /// initialise baseData implementations
    internalDataBase = platform_->createBase(OclMD::BaseData::className(),*this);
    internalDataBase.getAs<OclMD::BaseData>().initialise(system_);
    
    /// initialise internal force class
    forceKernel = platform_->createBase(OclMD::BaseCalculateForcesAndEnergy::className(),
                                        *this);
    forceKernel.getAs<OclMD::BaseCalculateForcesAndEnergy>().initialise(system_);
    /// set periodic box for internal
    OclMD::Vec3 tempPeriodicBox[3];
    system.getDimensions(tempPeriodicBox[0],tempPeriodicBox[1],tempPeriodicBox[2]);
    internalDataBase.getAs<OclMD::BaseData>().setPeriodicBox(*this,
                                                             tempPeriodicBox[0],
                                                             tempPeriodicBox[1],
                                                             tempPeriodicBox[2]);
    /// once everything initialised
}

OclMD::ContextImpl::~ContextImpl(){
    for (int i = 0; i<forceImpls_.size(); i++)
        delete forceImpls_[i];
    /// delete internal data created in platform
    platform_->deleteData(*this);
}
void* OclMD::ContextImpl::getPlatformData() const {
    return platformData_;
}

void OclMD::ContextImpl::setPlatformData(void* data){
    platformData_ = data;
}

void OclMD::ContextImpl::setPositions(const std::vector<Vec3>& positions){
    internalDataBase.getAs<OclMD::BaseData>().setPositions(*this,positions);
}

void OclMD::ContextImpl::getForces(std::vector<Vec3>& forces){
    internalDataBase.getAs<OclMD::BaseData>().getForces(*this,forces);
}

void OclMD::ContextImpl::getVirial(std::vector<OclMD::Tensor<double> >& virial){
    internalDataBase.getAs<OclMD::BaseData>().getVirial(*this,virial);
}

void OclMD::ContextImpl::getPotentialEnergy(std::vector<Real>& pe){
    internalDataBase.getAs<OclMD::BaseData>().getPotentialEnergy(*this,pe);
}

Real OclMD::ContextImpl::getTotalEnergy() {
    return 0.0;
}

void OclMD::ContextImpl::CalculateForcesandEnergy(){
    forceKernel.getAs<OclMD::BaseCalculateForcesAndEnergy>().prepare(*this);
    for(int f = 0; f < system_.getNumForces(); f++){
        forceImpls_[f]->calculateForces(*this);
    }
    
    forceKernel.getAs<OclMD::BaseCalculateForcesAndEnergy>().calculate(*this);
}

OclMD::System& OclMD::ContextImpl::getSystem(){
    return system_;
}
