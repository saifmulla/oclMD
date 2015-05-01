#include "oclmd/Platform.h"
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

void Platform::createData(ContextImpl& context) const {

}

void Platform::deleteData(ContextImpl& context) const {

}
