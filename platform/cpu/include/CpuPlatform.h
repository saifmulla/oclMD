/**
 * @file
 * @author Saif Mulla <s.mulla@ed.ac.uk>
 * @version 1.0
 * 
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 * 
 * classname CpuPlatform
 * This class is the pure CPU implementation of abstract class platform.
 * it contains implementations from pure virtual functions of abstarct class
 * Platform. The CPU platform is the default platform of oclMD code, this enables
 * validations and testing capability of the code.
 *
 */
 

#ifndef __OclMD__CpuPlatform__
#define __OclMD__CpuPlatform__

#include "RealType.h"
#include "Vec3.h"
#include "Platform.h"
#include "ContextImpl.h"
#include "System.h"

#include <vector>
#include <iostream>

namespace OclMD {

class CpuPlatform : public Platform {
public:
    /// forward declaration for obtaining platform data
    class PlatformData;

    /**
     * Constructor which is presently left blank with no significant
     * initilalisations
     */
    CpuPlatform();

    /// default destructor
    ~CpuPlatform(){}

    /// this a implementation of pure virtual function
    const std::string& getName() const {
        static const std::string name = "CPU";
        return name;
    }
    
    /// definition of pure virtual function in this class
    bool supportsDoublePrecision() const;
    
    /// create internal datastructure for platformData
    void createData(ContextImpl& context) const;
    
    /// delete the internal datastructure for platformdata
    void deleteData(ContextImpl& context) const;
};

/**
 * @section DESCRIPTION
 *
 * class PlatformData is a inner class for CpuPlatform
 * providing necessary datastructure to its higher class
 * @access PUBLIC
 */
class CpuPlatform::PlatformData {
public:
    /**
     * constructor that initialise all data structure
     * @param numParticles - number of particles in system
     *
     */
    PlatformData(int numParticles);
    // destructor to delete all initialised pointer data strucure
    ~PlatformData();
    
    int numParticles_;//numParticles in system
    int stepCount_;
    Real time_;
    void* positions_;
    void* forces_;
    void* periodicBoxSize_;
};
}//end namespace

#endif /* defined(__OclMD__CpuPlatform__) */
