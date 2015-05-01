
#include "oclmd/Base.h"

OclMD::Base::Base() : impl(0){
}

OclMD::Base::Base(OclMD::BaseImpl* impl) : impl(impl){
}

OclMD::Base::Base(const Base& copy) : impl(copy.impl){
    impl->incrementCounter();
}

OclMD::Base::~Base(){
    if(impl){
#ifdef FULLDEBUG
        std::cout << "Destructor in Base, reference counter "
        << impl->getReferenceCounter() << std::endl;
#endif
        impl->decrementCounter();
        if(impl->getReferenceCounter() == 0)
            delete impl;
    }
}

OclMD::Base& OclMD::Base::operator=(const OclMD::Base& copy){
    impl = copy.impl;
    impl->incrementCounter();
    return *this;
}

std::string OclMD::Base::getName() const {
    return impl->getFuncName();
}

const OclMD::BaseImpl& OclMD::Base::getImpl() const {
    return *impl;
}
