#ifndef OclMD_CpuBaseFactory_h
#define OclMD_CpuBaseFactory_h

#include "oclmd/BaseFactory.h"

namespace OclMD {

class CpuBaseFactory : public BaseFactory {
public:
    BaseImpl* createBaseImpl(std::string name,
                             const Platform& platform,
                             ContextImpl& context) const;
};
}
#endif