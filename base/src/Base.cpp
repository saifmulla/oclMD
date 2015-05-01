
#include "oclmd/Base.h"

OclMD::Base::Base() : impl(0){
}

OclMD::Base::Base(OclMD::BaseImpl* impl) : impl(impl){
}

OclMD::Base::Base(const Base& copy) : impl(copy.impl){
    impl->referenceCounter;
}

OclMD::Base::~Base(){
    if(impl){
#ifdef FULLDEBUG
        std::cout << "Destructor in Base, reference counter "
        << impl->referenceCounter << std::endl;
#endif
        impl->decrementCounter();
        if(impl->referenceCounter == 0)
            delete impl;
    }
}

OclMD::Base& OclMD::Base::operator=(const OclMD::Base& copy){
    impl = copy.impl;
    impl->referenceCounter++;
    return *this;
}

std::string OclMD::Base::getName() const {
    return impl->getFuncName();
}

const OclMD::BaseImpl& OclMD::Base::getImpl() const {
    return *impl;
}

