#include "oclmd/System.h"
#include "OmpPlatform.h"

OclMD::OmpPlatform::OmpPlatform():factory_(new OclMD::OmpBaseFactory()){
}

OclMD::OmpPlatform::~OmpPlatform(){
}

OclMD::BaseFactory* OclMD::OmpPlatform::getBaseFactory() const {
    return factory_;
}

void OclMD::OmpPlatform::createData(ContextImpl& context) const {
    context.setPlatformData(new OmpPlatform::PlatformData(context.getSystem().getNumParticles()));
}

void OclMD::OmpPlatform::deleteData(ContextImpl& context) const {
    OmpPlatform::PlatformData* data = reinterpret_cast<OmpPlatform::PlatformData*>(context.getPlatformData());
    delete data;
}

OclMD::OmpPlatform::PlatformData::PlatformData(int numParticles)
:numParticles_(numParticles),stepCount_(0),time_(0.0),numThreads_(omp_get_num_threads()){
    positions_ = new std::vector<OclMD::Vec3>(numParticles_);
    forces_ = new std::vector<OclMD::Vec3>(numParticles_);
    virial_ = new std::vector<OclMD::Tensor<double> >(numParticles_);
    pE_ = new std::vector<Real>(numParticles_);
    periodicBoxSize_ = new OclMD::Vec3();
}

OclMD::OmpPlatform::PlatformData::~PlatformData(){
    delete (std::vector<OclMD::Vec3>*) positions_;
    delete (std::vector<OclMD::Vec3>*) forces_;
    delete (OclMD::Vec3*) periodicBoxSize_;
    delete (std::vector<OclMD::Tensor<double> >*) virial_;
    delete (std::vector<Real>*) pE_;
}
