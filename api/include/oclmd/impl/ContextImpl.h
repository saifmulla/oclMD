#ifndef OclMD_ContextImpl_h
#define OclMD_ContextImpl_h

/**
 * @file
 * @author Saif Mulla <s.mulla@ed.ac.uk>
 * @version 1.0
 * @created 27/04/2015
 *
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 * classname ContextImpl
 * This class is the internal implementation of complete context of
 * the simulation being set. It is completely responsible for
 * initial setup and invocation of appropriate objects and
 * datastructure required to successfully run a simulation
 */

#include <vector>
#include <string>

#include "oclmd/Base.h"
#include "oclmd/Platform.h"
//#include "CpuPlatform.h"
#include "oclmd/Vec3.h"
#include "oclmd/Tensor.h"

namespace OclMD {
    
/// forward declarations
class System;
class ForceImpl;


class ContextImpl {
public:
    ContextImpl(System& system, Platform* platform);
    
    /// destructor
    ~ContextImpl();
    
    void CalculateForcesandEnergy();
    /// set data functions
    void setPositions(const std::vector<Vec3>& positions);
    
    void getForces(std::vector<Vec3>& forces);
    
    void getPotentialEnergy(std::vector<Real>& pe);
    
    void getVirial(std::vector<Tensor<double> >& virial);
    
    Real getTotalEnergy();
    
    Platform& getPlatform() {
        return *platform_;
    }
    
    System& getSystem();
    
    /// set the datastructure for internal platform
    void setPlatformData(void* data);
    
    /// get the datastructure of platform from internal platform
    void* getPlatformData() const;
    
//    const void* getPlatformData() const;
private:
    System& system_;
    std::vector<OclMD::ForceImpl*> forceImpls_;
    Base forceKernel, internalDataBase;
    Platform* platform_;
    void* platformData_;
};
    
}// end namespace

#endif
