
//
//  CpuPlatform.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include "CpuPlatform.h"
using namespace std;
OclMD::CpuPlatform::CpuPlatform(){
    
}

bool OclMD::CpuPlatform::supportsDoublePrecision() const {
    return true;
}

OclMD::CpuPlatform::PlatformData::PlatformData(int numParticles)
:numParticles_(numParticles),stepCount_(0),time_(0.0){
    positions_ = new std::vector<Vec3>(numParticles_);
    forces_ = new std::vector<Vec3>(numParticles_);
    periodicBoxSize_ = new OclMD::Vec3();
}

OclMD::CpuPlatform::PlatformData::~PlatformData(){
    delete (vector<Vec3>*) positions_;
    delete (vector<Vec3>*) forces_;
    delete (Vec3*) periodicBoxSize_;
}