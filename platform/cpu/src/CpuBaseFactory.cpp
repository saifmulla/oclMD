#include "CpuBaseFactory.h"
#include "CpuBases.h"


OclMD::BaseImpl* OclMD::CpuBaseFactory::createBaseImpl(std::string name,
                                                const OclMD::Platform& platform,
                                                OclMD::ContextImpl& context) const {

    if (name == BaseCalculateForcesAndEnergy::className())
        return new CpuBaseCalculateForcesAndEnergy(platform, name);
    else if (name == BaseData::className())
        return new CpuBaseData(platform,name);
    else if (name == BaseCalculateNonBondedForce::className())
        return new OclMD::CpuBaseCalculateNonBondedForce(platform,name);
    else
        throw OclMD::OclMDException((std::string("The supplied abstract base class " + name + " not supported ").c_str()));
    
}
