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
    std::vector<Real> charges_;
    /**
     * direct interaction list from OpenFOAM
     */
    std::vector<std::vector<int> > dil_;
    /// neighbourhood cell list
    std::vector<std::vector<int> > neighbouringCells_;
    
    /// number of total cells
    int nCells_;
    /// number of total reffered cells
    int nRefCells_;

    
public:
    System();
    
    System(const Vec3 boxDimensions[], const int moleculesize);
    
    /**
     * parameterised constructor specifically to collect 
     * cell information and referred cell informatin from 
     * openfoam
     */
    System(const std::vector<std::vector<int> > dil,
           const std::vector<std::vector<int> > neighbouringCells,
           int ncells,
           int nrefcells);
    
    ~System();
    
    void getDimensions(Vec3& x,Vec3& y,Vec3& z) const;
    
    void setDimensions(const Vec3& x,const Vec3& y,const Vec3& z);
    
    int addParticle(Real mass);
    
    int addCharge(Real charge);
    
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
    
    /// get the pointers to dil list
    const std::vector<std::vector<int> >& getDil() const;
    
    /// get pointer to neighbourhood list
    const std::vector<std::vector<int> >& getNeighbouringCells() const;
    
    /// get number of total cells
    int getnCells() const {
        return nCells_;
    }
    
    /// get number of referrence cells
    int getnRefCells() const {
        return nRefCells_;
    }
    
};
    
}

#endif
