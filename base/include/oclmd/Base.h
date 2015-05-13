#ifndef __OclMD__Base__
#define __OclMD__Base__

#include <iostream>
#include <string>
#include "oclmd/BaseImpl.h"

namespace OclMD {

class Base {
public:
    Base();
    /// a copy constructor of Base
    /// create a new Base out of existing one
    Base(const Base& copy);

    Base(BaseImpl* impl);

    ~Base();

    /// a assignment operator overloaded for Base
    /// essentially assign existing Base to new
    Base& operator=(const Base& copy);

    /// get string name of Base
    std::string getName() const;

    /// get BaseImpl object reference
    const BaseImpl& getImpl() const;
    
    BaseImpl& getImpl();
    
    template <class B>
    const B& getAs() const {
        return dynamic_cast<B&>(*impl);
    }

    template <class B>
    B& getAs(){
        return dynamic_cast<B&>(*impl);
    }

private:
    BaseImpl* impl;
};

}

#endif /* defined(__OclMD__Base__) */
