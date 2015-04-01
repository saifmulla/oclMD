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
    
class Force {
private:
    int numForces;
public:
    Force():numForces(0){
    }
    
    int getNumForces() const;
    
    void setNumForces(int forces);
};
}//end namespace oclMD

#endif
