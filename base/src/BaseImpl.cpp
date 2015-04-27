#include "BaseImpl.h"

using namespace OclMD;

BaseImpl::BaseImpl(const Platform& platform, std::string name)
:platform(&platform),funcName(name){
    
}

std::string BaseImpl::getFuncName() const {
    return funcName;
}

const Platform& BaseImpl::getPlatform(){
    return *platform;
}

