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

#include "Platform.h"
#include "CpuPlatform.h"
#include "Vec3.h"
#include <vector>
#include <string>

namespace OclMD {

/// forward declarations
class System;
class ForceImpl;


class ContextImpl {
public:
    ContextImpl(System& system, Platform* platform);
    
    /// set data functions
    void setPositions(std::vector<Vec3>& positions);
private:
    System& system_;
    std::vector<OclMD::ForceImpl*> forceImpls_;
    Platform* platform_;
    void* platformData_;
};
    
}// end namespace

#endif
