#include "BaseImpl.h"

OclMD::BaseImpl::BaseImpl(const Platform& platform,
                   std::string name)
:platform(&platform),
funcName(name),
referenceCounter(1){
    
}

std::string OclMD::BaseImpl::getFuncName() const {
    return funcName;
}

const OclMD::Platform& OclMD::BaseImpl::getPlatform(){
    return *platform;
}

int OclMD::BaseImpl::incrementCounter(){
    return ++referenceCounter;
}

int OclMD::BaseImpl::decrementCounter(){
    return --referenceCounter;
}

int OclMD::BaseImpl::getReferenceCounter() const {
    return referenceCounter;
}

