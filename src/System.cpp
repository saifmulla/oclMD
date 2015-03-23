//
//  System.cpp
//  OclMD
//
//  Created by Saif Mulla on 06/03/2015.
//
//

#include<cassert>
#include "System.h"

using namespace OclMD;

System::System()
:numParticles_(0),moleculeSize_(1)
{
    dimensions_[0] = Vec3(2,0,0);
    dimensions_[1] = Vec3(0,2,0);
    dimensions_[2] = Vec3(0,0,2);
    moleculeMasses_ = (double*) malloc(sizeof(double)*moleculeSize_);
    for(int i=0;i<moleculeSize_;i++)
        moleculeMasses_[i] = 0.0;
}

System::System(const Vec3 boxDimensions[], int numberofparticles, int moleculeSize)
:numParticles_(numberofparticles),moleculeSize_(moleculeSize)
{
    moleculeMasses_ = (double*) malloc(sizeof(double)*moleculeSize);
    dimensions_[0] = Vec3(boxDimensions[0]);
    dimensions_[1] = Vec3(boxDimensions[1]);
    dimensions_[2] = Vec3(boxDimensions[2]);
    for(int i=0;i<moleculeSize_;i++)
        moleculeMasses_[i] = 0.0;

}

System::~System(){
//    for (int i=0; i<forces_.size(); i++)
//        delete forces_[i];
    
    //delete moleculeMasses
    free(moleculeMasses_);
}

void System::setDimensions(const Vec3& x,const Vec3& y,const Vec3& z)
{
    dimensions_[0] = x;
    dimensions_[1] = y;
    dimensions_[2] = z;
}

void System::getDimensions(Vec3& x,Vec3& y,Vec3& z) const {
    x = Vec3(dimensions_[0]);
    y = Vec3(dimensions_[1]);
    z = Vec3(dimensions_[2]);
}

int System::getNumParticles() const {
    return numParticles_;
}

void System::setNumParticles(int numberofparticles)
{
    numParticles_ = numberofparticles;
}

int System::getMoleculeSize() const {
    return moleculeSize_;
}

void System::setMoleculeMass(int index, double mass){
    assert(index >= 0 && index < moleculeSize_);
    moleculeMasses_[index] = mass;
}

double System::getMoleculeMass(int index) const {
    assert(index >= 0 && index < moleculeSize_);
    return moleculeMasses_[index];
}

const Force& System::getForce(int index) const {
    assert(index >= 0 && index < forces_.size());
    return *forces_[index];
}

Force& System::getForce(int index) {
    assert(index >= 0 && index < forces_.size());
    return *forces_[index];
}


