#ifndef OclMD_Platform_h
#define OclMD_Platform_h

#include <string>
#include <vector>

namespace OclMD {

class ContextImpl;

class Platform {

public:
    virtual ~Platform();

    virtual const std::string& getName() const = 0;

    virtual bool supportsDoublePrecision() const = 0;

    virtual void createData(ContextImpl& context) const = 0;

    virtual void deleteData(ContextImpl& context) const = 0;

    Platform& getPlatform();

    /**
    * register a core platform, in which case it
    * is CpuPlatform by default
    */
    static void registerPlatform(Platform* platform);
private:
    static Platform* platformType;
};

}//end namespace
#endif /*OclMD_Platform_h*/

