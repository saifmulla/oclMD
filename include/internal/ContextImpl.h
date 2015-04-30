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
#include "Platform.h"
#include "CpuPlatform.h"
#include "Vec3.h"
#include "Base.h"

namespace OclMD {

/// forward declarations
class System;
class ForceImpl;


class ContextImpl {
public:
    ContextImpl(System& system, Platform* platform);
    
    void CalculateForcesandEnergy();
    /// set data functions
    void setPositions(std::vector<Vec3>& positions);
    
    void getForces(std::vector<Vec3>& forces);
    
    System& getSystem();
    
    /// set the datastructure for internal platform
    void setPlatformData(void* data);
    
    /// get the datastructure of platform from internal platform
    void* getPlatformData() const;
private:
    System& system_;
    std::vector<OclMD::ForceImpl*> forceImpls_;
    Platform* platform_;
    void* platformData_;
//    OclMD::Base forceBase, dataBase;
};
    
}// end namespace

#endif
