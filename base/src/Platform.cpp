//
//  Platform.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include "Platform.h"
using namespace OclMD;

/// globally initialise static variable platformType
Platform* Platform::platformType = 0;

/// destructor implementation
OclMD::Platform::~Platform(){
}

/// static function to set the Platform variable which
/// actually sets the derived platform used.
void OclMD::Platform::registerPlatform(Platform* platform){
    platformType = platform;
}

Platform& OclMD::Platform::getPlatform(){
    return *platformType;
}





