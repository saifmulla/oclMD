//
//  Platform.h
//  OclMD
//
//  Created by Saif Mulla on 01/04/2015.
//
//

#ifndef OclMD_Platform_h
#define OclMD_Platform_h

#include <string>
#include <vector>

namespace OclMD {

class Platform {
   
public:
    virtual ~Platform();
    virtual const std::string& getName() const = 0;
    virtual bool supportsDoublePrecision() const = 0;
    static void registerPlatform(Platform* platform);
    
private:
    std::string platformName_;
    static std::vector<Platform*>& getPlatforms();
    
};
    
}//end namespace
#endif