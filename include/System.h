//
//  System.h
//  OclMD
//
//  Created by Saif Mulla on 06/03/2015.
//
//

#ifndef OclMD_System_h
#define OclMD_System_h

#include <iostream>
#include <stdlib.h>
#include "Vec3.h"


namespace OclMD {

class System {

private:
    Vec3 dimensions_[3];
    int numParticles_;
    int moleculeSize_;
    double* moleculeMasses_;
    
public:
    System();
    void getDimensions(Vec3& x,Vec3& y,Vec3& z) const;
    void setDimensions(const Vec3& x,const Vec3& y,const Vec3& z);
    int getNumParticles() const;
    void setNumParticles(int numberofparticles);
    int getMoleculeSize() const;
    void setMoleculeSize(int size) {
        moleculeSize_ = size;
    }

};
    
}

#endif
