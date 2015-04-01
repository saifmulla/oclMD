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
#include "Vec3.h"


namespace OclMD {

    class Force;
class System {

private:
    Vec3 dimensions_[3];
    int numParticles_;
    int moleculeSize_;
    double* moleculeMasses_;
    double* moleculeCharges_;
    std::vector<Force*> forces_;
    
public:
    System();
    System(const Vec3 boxDimensions[], const int numberofparticles, const int moleculesize);
    ~System();
    void getDimensions(Vec3& x,Vec3& y,Vec3& z) const;
    void setDimensions(const Vec3& x,const Vec3& y,const Vec3& z);
    int getNumParticles() const;
    void setNumParticles(int numberofparticles);
    int getMoleculeSize() const;
    void setMoleculeSize(int size) {
        moleculeSize_ = size;
    }
    void setMoleculeMass(int index, double mass);
    double getMoleculeMass(int index) const;
    void setMoleculeCharge(int index, double charge);
    const double getMoleculeCharge(int index) const;
    int addForce(Force* force){
        forces_.push_back(force);
        return forces_.size()-1;
    }
    const Force& getForce(int index) const;
    Force& getForce(int index);

};
    
}

#endif
