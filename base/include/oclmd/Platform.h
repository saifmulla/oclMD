#ifndef OclMD_Platform_h
#define OclMD_Platform_h

#include <string>
#include <vector>
#include <map>

namespace OclMD {

class ContextImpl;
class Base;
class BaseFactory;

class Platform {

public:
    virtual ~Platform();

    virtual const std::string& getName() const = 0;

    virtual bool supportsDoublePrecision() const = 0;

    virtual void createData(ContextImpl& context) const = 0;

    virtual void deleteData(ContextImpl& context) const = 0;
    
    virtual BaseFactory* getBaseFactory() const = 0;

    Platform& getPlatform();

    /**
    * register a core platform, in which case it
    * is CpuPlatform by default
    */
    static void registerPlatform(Platform* platform);
    
//    void registerBaseFactory(const std::string& name, BaseFactory* factory);
    
    Base createBase(const std::string& name, ContextImpl& context) const;
    
private:
    static Platform* platformType;
//    std::map<std::string, BaseFactory*> baseFactories;
    
};

}//end namespace
#endif /*OclMD_Platform_h*/

