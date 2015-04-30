//
//  Base.h
//  OclMD
//
//  Created by Saif Mulla on 30/04/2015.
//
//

#ifndef __OclMD__Base__
#define __OclMD__Base__

#include <iostream>
#include <string>
#include "BaseImpl.h"

namespace OclMD {

class Kernel {
public:
    Kernel();
    /// a copy constructor of kernel
    /// create a new kernel out of existing one
    Kernel(const Kernel& copy);
    
    Kernel(BaseImpl* impl);
    
    ~Kernel();
    
    /// a assignment operator overloaded for kernel
    /// essentially assign existing kernel to new
    Kernel& operator=(const Kernel& copy);
    
    /// get string name of kernel
    std::string getName() const;
    
    /// get BaseImpl object reference
    const BaseImpl& getImpl() const;
    
private:
    BaseImpl* impl;
};
}

#endif /* defined(__OclMD__Base__) */
