#ifndef __OclMD__CpuBases__
#define __OclMD__CpuBases__

#include "RealType.h"
#include "Vec3.h"
#include "AbstractBases.h"
#include "System.h"
#include "ContextImpl.h"
#include "CpuPlatform.h"

namespace OclMD {
//
class CpuCalculateForcesAndEnergyBase : public CalculateForcesAndEnergyBase {
public:
    CpuCalculateForcesAndEnergyBase(const Platform& platform, std::string className)
    :CalculateForcesAndEnergyBase(platform,className){
        
    }
    
    /// declare virtual private functions declared in abstract class
    void initialise(const System& system);

    void prepare(ContextImpl& context);
    
    Real calculate(ContextImpl& context);
};


class CpuDataBase : public DataBase {
public:
//    CpuDataBase(const Platform& platform, std::string className, CpuPlatform::PlaformData& data)
//    :DataBase(platform,className),pData_(data){
//        
//    }
    CpuDataBase(const Platform& platform, std::string className)
    :DataBase(platform,className){
        
    }
    
    /// implement virtual private functions declared in abstract class
    void initialise(const System& system);
    
    void setPositions(ContextImpl& context, const std::vector<Vec3>& positions);
    
    void getForces(ContextImpl& context, std::vector<Vec3>& forces);
    
    void setPeriodicBox(ContextImpl& context, const Vec3& x, const Vec3& y, const Vec3& z);
    
    void getPeriodicBox(ContextImpl& context, Vec3& x, Vec3& y, Vec3& z);
    
private:
//    OclMD::CpuPlatform::PlaformData* pData_;
};

    
/**
 * classname CpuCalculateNonBondedForceBase
 */

class CpuCalculateNonBondedForceBase : public CalculateNonBondedForceBase {
public:
    CpuCalculateNonBondedForceBase(const Platform& platform, std::string className) : CalculateNonBondedForceBase(platform,className){
        
    }
    
    void initialise(const System& system, const NonBondedForce& force);
    
    Real calculate(ContextImpl& context);
};

} // end namespace

#endif /* defined(__OclMD__CpuBases__) */
