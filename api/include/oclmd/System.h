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
#include <vector>
#include <stdlib.h>
#include "oclmd/Vec3.h"


namespace OclMD {
    
class Force;
    
class System {
    
private:
    Vec3 dimensions_[3];
    //    int numParticles_;
    int moleculeSize_;
    std::vector<Force*> forces_;
    std::vector<Real> masses_;
    
public:
    System();
    
    System(const Vec3 boxDimensions[], const int moleculesize);
    
    ~System();
    
    void getDimensions(Vec3& x,Vec3& y,Vec3& z) const;
    
    void setDimensions(const Vec3& x,const Vec3& y,const Vec3& z);
    
    int addParticle(Real mass);
    
    int getNumParticles() const;
    
    int getMoleculeSize() const;
    
    void setMoleculeSize(int size) {
        moleculeSize_ = size;
    }
    
    int addForce(Force* force){
        forces_.push_back(force);
        return forces_.size()-1;
    }
    
    int getNumForces() const;
    
    const Force& getForce(int index) const;
    
    Force& getForce(int index);
    
};
    
}

#endif
