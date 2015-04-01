//
//  NonBondedForce.cpp
//  OclMD
//
//  Created by Saif Mulla on 01/04/2015.
//
//
#include "Force.h"
#include "NonBondedForce.h"

OclMD::NonBondedForce::NonBondedForce():method_(CutOffPeriodic),cutOffDistance_(0.0){
}

double OclMD::NonBondedForce::getCutOffDistance() const {
    return cutOffDistance_;
}