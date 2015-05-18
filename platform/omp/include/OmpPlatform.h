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
 * classname OmpPlatform
 * This class is implementation of base class Platform.
 * This class is intended for openmp platform, which provides
 * multicore functionality for CPU and Xeon PHI co-processors.
 * it contains implementations from pure virtual functions of 
 * base class Platform.
 *
 */
#ifndef OclMD_OmpPlatform_h
#define OclMD_OmpPlatform_h

#include <string>
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#define omp_get_num_threads() 1
#endif
#include "oclmd/Platform.h"
#include "oclmd/RealType.h"
#include "oclmd/impl/ContextImpl.h"
#include "OmpBaseFactory.h"

namespace OclMD {
    
class OmpPlatform : public Platform {
public:
    /// forward declaration of internal class PlatformData
    class PlatformData;
    
    /// constructor
    OmpPlatform();
    
    /// default destructor
    ~OmpPlatform();
    
    /// declare and implement pure virtual platform function
    /// in this platform and provide a string name to it
    const std::string& getName() const {
        static const std::string name = "OMP";
        return name;
    }
    
    /**
     * declare pure virtual function of base class Platform
     * for this platform implementation
     * functionname - supportsDoublePrecision
     * this function will be using CPU 
     * and must support double precision therefore
     * no check are required
     */
    bool supportsDoublePrecision() const {
        return true;
    }
    
    /// declare pure virtual function of base class platform
    void createData(ContextImpl& context) const;
    
    /// declare pure virtual function of base class platform
    void deleteData(ContextImpl& context) const;
    
    /// declare pure virtual function of base class platform
    /// this returns pointer to internal BaseFactory implementation
    /// to base class Platform.
    BaseFactory* getBaseFactory() const;
    
private:
    OmpBaseFactory* factory_;
};

/**
 * @section DESCRIPTION
 * class PlatformData
 * This class is an internal implementation of OmpPlatform class.
 * Essentially this class represents internal data structure
 * for this specific platform. The advantage for creating this 
 * class is that the class is completely free to use any type of
 * data internally such as intrinsics or any kind of platform specific
 * data structure however without impacting anything externally at
 * API level.
 *
 * @section PUBLIC
 *
 */
class OmpPlatform::PlatformData {
public:
    /// constructor
    /// @param numParticles - number of particles in system
    PlatformData(int numPariticles);
    
    /// destructor
    /// delete all the datastructure created for this platform
    /// use this function to deallocate memory and all other cleanup tasks
    ~PlatformData();
    
    int numParticles_;
    int stepCount_;
    Real time_;
    int numThreads_;
    void* positions_;
    void* forces_;
    void* virial_;
    void* pE_;
    void* periodicBoxSize_;
};
    
}// end namespace
#endif /* end OclMD_OmpPlatform_h */