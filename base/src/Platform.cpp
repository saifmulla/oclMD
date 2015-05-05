#include "oclmd/Platform.h"
#include "oclmd/Base.h"
#include "oclmd/BaseFactory.h"


using namespace OclMD;

/// globally initialise static variable platformType
Platform* Platform::platformType = 0;

/// destructor implementation
OclMD::Platform::~Platform(){
}

/// static function to set the Platform variable which
/// actually sets the derived platform used.
void OclMD::Platform::registerPlatform(Platform* platform){
    platformType = platform;
}

Platform& OclMD::Platform::getPlatform(){
    return *platformType;
}

//void Platform::registerBaseFactory(const std::string& name,
//                                     BaseFactory* factory){
//    baseFactories[name] = factory;
//}

Base Platform::createBase(const std::string& name,
                               ContextImpl& impl) const {
//    return Base(baseFactories.find(name)->second->createBaseImpl(name,*this,impl));
    return Base(this->getBaseFactory()->createBaseImpl(name,*this,impl));
}