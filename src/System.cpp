//
//  System.cpp
//  OclMD
//
//  Created by Saif Mulla on 06/03/2015.
//
//

#include "System.h"

using namespace OclMD;

System::System()
:numParticles_(0),moleculeSize_(1)
{
    dimensions_[0] = Vec3(2,0,0);
    dimensions_[1] = Vec3(0,2,0);
    dimensions_[2] = Vec3(0,0,2);
    moleculeMasses_ = (double*) malloc(sizeof(double)*moleculeSize_);
}

void System::setDimensions(const Vec3& x,const Vec3& y,const Vec3& z)
{
    dimensions_[0] = x;
    dimensions_[1] = y;
    dimensions_[2] = z;
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
