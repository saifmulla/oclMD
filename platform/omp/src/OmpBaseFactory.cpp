#include "OmpBaseFactory.h"
#include "OmpBases.h"

OclMD::BaseImpl* OclMD::OmpBaseFactory::createBaseImpl(std::string name,
                                                   const OclMD::Platform& platform,
                                                   OclMD::ContextImpl& context) const {
    
    if (name == OclMD::BaseCalculateForcesAndEnergy::className())
        return new OclMD::OmpBaseCalculateForcesAndEnergy(platform, name);
    else if (name == OclMD::BaseData::className())
        return new OclMD::OmpBaseData(platform,name);
    else if (name == OclMD::BaseCalculateNonBondedForce::className())
        return new OclMD::OmpBaseCalculateNonBondedForce(platform,name);
    else
        throw OclMD::OclMDException((std::string("The supplied abstract base class " + name + " not supported ").c_str()));
    
}