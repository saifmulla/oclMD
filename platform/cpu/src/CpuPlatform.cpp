
//
//  CpuPlatform.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include "CpuPlatform.h"
#include "CpuBases.h"

using namespace std;

OclMD::CpuPlatform::CpuPlatform():factory(new OclMD::CpuBaseFactory()){
//    registerBaseFactory(BaseCalculateForcesAndEnergy::className(),factory);
//    registerBaseFactory(BaseData::className(),factory);
//    registerBaseFactory(BaseCalculateNonBondedForce::className(),factory);
}

OclMD::BaseFactory* OclMD::CpuPlatform::getBaseFactory() const {
    return factory;
}
bool OclMD::CpuPlatform::supportsDoublePrecision() const {
    return true;
}

void OclMD::CpuPlatform::createData(ContextImpl& context) const {
    context.setPlatformData(new CpuPlatform::PlatformData(context.getSystem().getNumParticles()));
}

void OclMD::CpuPlatform::deleteData(ContextImpl& context) const {
    CpuPlatform::PlatformData* data = reinterpret_cast<PlatformData*>(context.getPlatformData());
    delete data;
}

OclMD::CpuPlatform::PlatformData::PlatformData(int numParticles)
:numParticles_(numParticles),stepCount_(0),time_(0.0){
    positions_ = new std::vector<OclMD::Vec3>(numParticles_);
    forces_ = new std::vector<OclMD::Vec3>(numParticles_);
    virial_ = new std::vector<OclMD::Tensor<double> >(numParticles_);
    pE_ = new std::vector<Real>(numParticles_);
    periodicBoxSize_ = new OclMD::Vec3();
}

OclMD::CpuPlatform::PlatformData::~PlatformData(){
    delete (std::vector<OclMD::Vec3>*) positions_;
    delete (std::vector<OclMD::Vec3>*) forces_;
    delete (OclMD::Vec3*) periodicBoxSize_;
    delete (std::vector<OclMD::Tensor<double> >*) virial_;
    delete (std::vector<Real>*) pE_;
}
