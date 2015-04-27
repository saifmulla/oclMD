#ifndef OclMD_BaseImpl_h
#define OclMD_BaseImpl_h

#include <string>
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
//        assert(referenceCount == 0);
    }
    /**
     * Get the name of this Base.
     */
    std::string getFuncName() const;
    /**
     * Get the Platform that created this BaseImpl.
     */
    const Platform& getPlatform();
private:
//    friend class Base;
    const Platform* platform;
    std::string funcName;
//    int referenceCount;
};
    
} // namespace OclMD


#endif
