//
//  Force.h
//  OclMD
//
//  Created by Saif Mulla on 31/03/2015.
//
//

#ifndef OclMD_Force_h
#define OclMD_Force_h


namespace OclMD {
    
class ForceImpl;
    
class Force {
private:
    int numForces;
public:
    Force():numForces(0){
    }
    
    virtual ~Force(){}
    
    int getNumForces() const;
    
    void setNumForces(int forces);

protected:
    friend class ContextImpl;
    virtual ForceImpl* createImpl() = 0;
    
};
}//end namespace oclMD

#endif
