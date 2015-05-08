//
//  System.cpp
//  OclMD
//
//  Created by Saif Mulla on 06/03/2015.
//
//

#include<cassert>
#include "oclmd/System.h"

OclMD::System::System()
:moleculeSize_(1),forces_(0),masses_(0)
{
    dimensions_[0] = Vec3(2,0,0);
    dimensions_[1] = Vec3(0,2,0);
    dimensions_[2] = Vec3(0,0,2);
}

OclMD::System::System(const Vec3 boxDimensions[], int moleculeSize)
:moleculeSize_(moleculeSize),forces_(0),masses_(0)
{
    dimensions_[0] = Vec3(boxDimensions[0]);
    dimensions_[1] = Vec3(boxDimensions[1]);
    dimensions_[2] = Vec3(boxDimensions[2]);
}

OclMD::System::~System(){
    //    for (int i=0; i<forces_.size(); i++)
    //        delete forces_[i];

}

void OclMD::System::setDimensions(const Vec3& x,
                                const Vec3& y,
                                const Vec3& z)
{
    dimensions_[0] = x;
    dimensions_[1] = y;
    dimensions_[2] = z;
}

void OclMD::System::getDimensions(Vec3& x,Vec3& y,Vec3& z) const {
    x = Vec3(dimensions_[0]);
    y = Vec3(dimensions_[1]);
    z = Vec3(dimensions_[2]);
}

int OclMD::System::addParticle(Real mass){
    masses_.push_back(mass);
    return masses_.size()-1;
}

int OclMD::System::getNumForces() const {
    return forces_.size();
}

int OclMD::System::getNumParticles() const {
    return masses_.size();
}

int OclMD::System::getMoleculeSize() const {
    return moleculeSize_;
}

const OclMD::Force& OclMD::System::getForce(int index) const {
    assert(index >= 0 && index < forces_.size());
    return *forces_[index];
}

OclMD::Force& OclMD::System::getForce(int index) {
    assert(index >= 0 && index < forces_.size());
    return *forces_[index];
}


