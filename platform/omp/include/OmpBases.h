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
 * classname OmpBases
 * This class is implementation of abstract base classes declared in BaseInterfaces.
 * This class is an implementation for OpenMP platform intended to
 * run on multicore CPU and Xeon PHI co-processors.
 * This file contains implementation of variour abstract class with
 * pure virtual functions or interfaces in other terms.
 *
 */

#ifndef OclMD_OmpBases_h
#define OclMD_OmpBases_h

#include <vector>
#include "oclmd/RealType.h"
#include "oclmd/BaseInterfaces.h"
#include "OmpPlatform.h"
#include "OmpNonBondedIxn.h"

namespace OclMD {

/**
 * className OmpBaseCalculateForcesAndEnergy
 * This is an implementation of pure abstract base class 
 * BaseCalculateForcesAndEnergy
 *
 */
class OmpBaseCalculateForcesAndEnergy : public BaseCalculateForcesAndEnergy {
public:
    OmpBaseCalculateForcesAndEnergy(const Platform& platform, std::string className)
    :BaseCalculateForcesAndEnergy(platform,className){
        
    }
    
    /// declare virtual private functions declared in abstract class
    void initialise(const System& system);
    
    void prepare(ContextImpl& context);
    
    Real calculate(ContextImpl& context);
};
    

class OmpBaseData : public BaseData {
public:
    OmpBaseData(const Platform& platform, std::string className)
    :BaseData(platform,className){
        
    }
    
    /// implement virtual private functions declared in abstract class
    void initialise(const System& system, ContextImpl& context);
    
    void setPositions(ContextImpl& context, const std::vector<Vec3>& positions);
    
    void setReferredPositions(ContextImpl& context, const std::vector<std::vector<Vec3> >& referredPositions);
    
    void setCellOccupancyList(ContextImpl& context,
                              const std::vector<std::vector<int> >& celloccupancy);
    
    void setReferredCellParticles(ContextImpl& context,
                                  const std::vector<std::vector<int> >& referredcellparticles);
    
    void getForces(ContextImpl& context, std::vector<Vec3>& forces);
    
    void getVirial(ContextImpl& context, std::vector<Tensor<double> >& virial);
    
    void getPotentialEnergy(ContextImpl& context, std::vector<double>& pe);
    
    void setPeriodicBox(ContextImpl& context, const Vec3& x, const Vec3& y, const Vec3& z) const;
    
    void getPeriodicBox(ContextImpl& context, Vec3& x, Vec3& y, Vec3& z) const;
    
    const std::vector<int>* getCellOccupancyListByCell(int cellId);
    
    const std::vector<int>* getRefCellParticlesByCell(int cellId);
    
    void* getInteractionCells();
};


/**
 * classname CpuCalculateNonBondedForceBase
 */
//class CpuNonBondedIxn;
class OmpBaseCalculateNonBondedForce : public BaseCalculateNonBondedForce {
public:
    OmpBaseCalculateNonBondedForce(const Platform& platform, std::string className) : BaseCalculateNonBondedForce(platform,className){
        
    }
    
    void initialise(const System& system,
                    const NonBondedForceImpl& force,
                    ContextImpl& context
                    );
    
    void preprocess(void* interactionCells);
    
    Real calculate(ContextImpl& context);
    
private:
    OmpNonBondedIxn* nonbondedixn;
};

}//end namespace

#endif /* end OclMD_OmpBases_h */
