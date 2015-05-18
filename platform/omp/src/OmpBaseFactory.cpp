#include "OmpBaseFactory.h"

OclMD::BaseImpl* OclMD::OmpBaseFactory::createBaseImpl(std::string name,
                                                   const OclMD::Platform& platform,
                                                   OclMD::ContextImpl& context) const {
    return 0;
}