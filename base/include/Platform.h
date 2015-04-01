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

namespace OclMD {

class Platform {
   
public:
    virtual ~Platform();
    virtual const std::string& getName() const = 0;
    
private:
    std::string platformName_;
    
};
}//end namespace
#endif
