
#include "oclmd/Base.h"

OclMD::Base::Base() : impl(0){
}

OclMD::Base::Base(OclMD::BaseImpl* impl) : impl(impl){
}

OclMD::Base::Base(const Base& copy) : impl(copy.impl){
    if(impl)
        impl->referenceCounter++;
}

OclMD::Base::~Base(){
    if(impl){
        impl->referenceCounter--;
        if(impl->referenceCounter == 0)
            delete impl;
    }
}

OclMD::Base& OclMD::Base::operator=(const OclMD::Base& copy){
    if(impl){
        impl->referenceCounter--;
        if(impl->referenceCounter==0)
            delete impl;
    }
    impl = copy.impl;
    if(impl)
        impl->referenceCounter++;
    
    return *this;
}

std::string OclMD::Base::getName() const {
    return impl->getFuncName();
}

const OclMD::BaseImpl& OclMD::Base::getImpl() const {
    return *impl;
}

