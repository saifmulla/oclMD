#ifndef OclMD_OmpBaseFactory_h
#define OclMD_OmpBaseFactory_h

#include <string>
#include "oclmd/BaseFactory.h"

namespace OclMD {
    
class OmpBaseFactory : public BaseFactory {
public:
    BaseImpl* createBaseImpl(std::string name, const Platform& platform,
                             ContextImpl& context) const;
};
}//end namespace
#endif /* end OclMD_OmpBaseFactory_h */