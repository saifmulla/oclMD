#ifndef OclMD_BaseFactory_h
#define OclMD_BaseFactory_h

#include "oclmd/BaseImpl.h"

namespace OclMD {

class BaseFactory {

public:
    virtual BaseImpl* createBaseImpl(std::string name, const Platform& platform, ContextImpl& context) const = 0;
    
    virtual ~BaseFactory(){
        
    }
};
}
#endif