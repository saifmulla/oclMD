#ifndef __OclMD__CpuBases__
#define __OclMD__CpuBases__

#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"
#include "oclmd/Tensor.h"
#include "oclmd/BaseInterfaces.h"
#include "oclmd/System.h"
#include "oclmd/impl/ContextImpl.h"
#include "oclmd/impl/NonBondedForceImpl.h"
#include "CpuPlatform.h"
#include "CpuNonBondedIxn.h"
#include "CpuInteractionCells.h"

namespace OclMD {
//
class CpuBaseCalculateForcesAndEnergy : public BaseCalculateForcesAndEnergy {
public:
    CpuBaseCalculateForcesAndEnergy(const Platform& platform, std::string className)
    :BaseCalculateForcesAndEnergy(platform,className){
        
    }
    
    /// declare virtual private functions declared in abstract class
    void initialise(const System& system);

    void prepare(ContextImpl& context);
    
    Real calculate(ContextImpl& context);
    
private:
    CpuInteractionCells* interactionCells_;
};

class CpuBaseData : public BaseData {
public:
//    CpuBaseData(const Platform& platform, std::string className, CpuPlatform::PlaformData& data)
//    :BaseData(platform,className),pData_(data){
//        
//    }
    CpuBaseData(const Platform& platform, std::string className)
    :BaseData(platform,className){
        
    }
    
    /// implement virtual private functions declared in abstract class
    void initialise(const System& system);
    
    void setPositions(ContextImpl& context, const std::vector<Vec3>& positions);
    
    void getForces(ContextImpl& context, std::vector<Vec3>& forces);
    
    void getVirial(ContextImpl& context, std::vector<Tensor<double> >& virial);
    
    void getPotentialEnergy(ContextImpl& context, std::vector<double>& pe);
    
    void setPeriodicBox(ContextImpl& context, const Vec3& x, const Vec3& y, const Vec3& z) const;
    
    void getPeriodicBox(ContextImpl& context, Vec3& x, Vec3& y, Vec3& z) const;
    
private:
//    CpuPlatform::PlaformData pData_;
};

    
/**
 * classname CpuCalculateNonBondedForceBase
 */
//class CpuNonBondedIxn;
class CpuBaseCalculateNonBondedForce : public BaseCalculateNonBondedForce {
public:
    CpuBaseCalculateNonBondedForce(const Platform& platform, std::string className) : BaseCalculateNonBondedForce(platform,className){
        
    }
    
    void initialise(const System& system,
                    const NonBondedForceImpl& force
                    );
    
    void preprocess();
    
    Real calculate(ContextImpl& context);
    
private:
    CpuNonBondedIxn* nonbondedixn;
    CpuInteractionCells* interactionCells_;
};

} // end namespace

#endif /* defined(__OclMD__CpuBases__) */
