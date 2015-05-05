
//
//  CpuPlatform.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include "CpuPlatform.h"
//#include "CpuBaseFactory.h"

using namespace std;

OclMD::CpuPlatform::CpuPlatform(){
//    OclMD::CpuBaseFactory* factory = new OclMD::CpuBaseFactory();
}

bool OclMD::CpuPlatform::supportsDoublePrecision() const {
    return true;
}

void OclMD::CpuPlatform::createData(ContextImpl& context) const {
    context.setPlatformData(new CpuPlatform::PlatformData(context.getSystem().getNumParticles()));
#ifdef FULLDEBUG
    std::cout << "CPU platform data created " << std::endl;
#endif
}

void OclMD::CpuPlatform::deleteData(ContextImpl& context) const {
    CpuPlatform::PlatformData* data = reinterpret_cast<PlatformData*>(context.getPlatformData());
    delete data;
}

OclMD::CpuPlatform::PlatformData::PlatformData(int numParticles)
:numParticles_(numParticles),stepCount_(0),time_(0.0){
    positions_ = new std::vector<Vec3>(numParticles_);
    forces_ = new std::vector<Vec3>(numParticles_);
    virial_ = new std::vector<Tensor<double> >(numParticles_);
    pE_ = new std::vector<Real>(numParticles_);
    periodicBoxSize_ = new OclMD::Vec3();
}

OclMD::CpuPlatform::PlatformData::~PlatformData(){
#ifdef FULLDEBUG
    std::cout<< "PlatformData deleted" << std::endl;
#endif
    
    delete (vector<Vec3>*) positions_;
    delete (vector<Vec3>*) forces_;
    delete (Vec3*) periodicBoxSize_;
    delete (vector<Tensor<double> >*) virial_;
    delete (vector<Real>*) pE_;
}
