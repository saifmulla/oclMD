#ifndef OclMD_BaseImpl_h
#define OclMD_BaseImpl_h

#include <string>
#include <cassert>
#include "Platform.h"

namespace OclMD {
    
/**
 * A BaseImpl defines the internal implementation of a Base object.  A subclass will typically
 * declare an abstract execute() method which defines the API for executing the Base.  Other classes
 * will in turn subclass it and provide concrete implementations of the execute() method.
 */

class  BaseImpl {
public:
    /**
     * Create a BaseImpl.
     *
     * @param name      the name of the Base to create
     * @param platform  the Platform that created this Base
     */
    BaseImpl(const Platform& platform, std::string name);
    virtual ~BaseImpl() {
        assert(referenceCounter == 0);
    }
    /**
     * Get the name of this Base.
     */
    std::string getFuncName() const;
    /**
     * Get the Platform that created this BaseImpl.
     */
    const Platform& getPlatform();
    
    int incrementCounter();
    
    int decrementCounter();
    
    int getReferenceCounter() const;
private:
    friend class Base;
    const Platform* platform;
    std::string funcName;
    int referenceCounter;
};
    
} // namespace OclMD


#endif
