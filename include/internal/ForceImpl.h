//
//  ForceImpl.h
//  OclMD
//
//  Created by Saif Mulla on 24/04/2015.
//
//

#ifndef OclMD_ForceImpl_h
#define OclMD_ForceImpl_h

namespace OclMD {

//forward declaration
class ContextImpl;
class Force;

class ForceImpl {
public:
    virtual ~ForceImpl(){
    }
    
    virtual void initialise(ContextImpl& impl) = 0;
    
    virtual Real calculateForces(ContextImpl& impl) = 0;
    
    virtual Force& getOwner() = 0;
};
}// end namespace

#endif
