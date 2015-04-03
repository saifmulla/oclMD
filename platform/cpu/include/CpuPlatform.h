//
//  CpuPlatform.h
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#ifndef __OclMD__CpuPlatform__
#define __OclMD__CpuPlatform__

#include "RealType.h"
#include "Vec3.h"
#include "Platform.h"
#include <vector>
#include <iostream>

namespace OclMD {

class CpuPlatform : public Platform {
public:
    //forward declaration for obtaining platform data
    class PlatformData;
    CpuPlatform();
    const std::string& getName() const {
        static const std::string name = "CPU";
        return name;
    }
    bool supportsDoublePrecision() const;
    ~CpuPlatform(){}
};

class CpuPlatform::PlatformData {
public:
    PlatformData(int numParticles);
    ~PlatformData();
    int numParticles_;
    int stepCount_;
    Real time_;
    void* positions_;
    void* forces_;
    void* periodicBoxSize_;
};
}//end namespace

#endif /* defined(__OclMD__CpuPlatform__) */
