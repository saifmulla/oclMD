//
//  Base.cpp
//  OclMD
//
//  Created by Saif Mulla on 30/04/2015.
//
//

#include "Base.h"

OclMD::Kernel::Kernel() : impl(0){
}

OclMD::Kernel::Kernel(OclMD::BaseImpl* impl) : impl(impl){
}

OclMD::Kernel::Kernel(const Kernel& copy) : impl(copy.impl){
    impl->incrementCounter();
}

OclMD::Kernel::~Kernel(){
    if(impl){
#ifdef FULLDEBUG
    std::cout << "Destructor in Kernel, reference counter "
        << impl->getReferenceCounter() << std::endl;
#endif
        impl->decrementCounter();
        if(impl->getReferenceCounter() == 0)
            delete impl;
    }
}

OclMD::Kernel& OclMD::Kernel::operator=(const OclMD::Kernel& copy){
    impl = copy.impl;
    impl->incrementCounter();
    return *this;
}

std::string OclMD::Kernel::getName() const {
    return impl->getFuncName();
}

const OclMD::BaseImpl& OclMD::Kernel::getImpl() const {
    return *impl;
}

