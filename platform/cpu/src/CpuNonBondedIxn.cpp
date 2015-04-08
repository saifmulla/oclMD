//
//  CpuNonBondedIxn.cpp
//  OclMD
//
//  Created by Saif Mulla on 03/04/2015.
//
//

#include "CpuNonBondedIxn.h"

OclMD::CpuNonBondedIxn::CpuNonBondedIxn(){
}

OclMD::CpuNonBondedIxn::~CpuNonBondedIxn(){
}

void OclMD::CpuNonBondedIxn::calculateForces(){
    
    std::vector<Vec3> positions(2);
    std::vector<Vec3> forces(2);
    
    positions[0] = Vec3(0,0,0);
    positions[0] = Vec3(2,0,0);
    
    forces[0] = Vec3(0,0,0);
    forces[1] = Vec3(0,0,0);
    
    Vec3 rij = positions[0] - positions[1];
    Real rsijmag = Mag(rij);
    
}

