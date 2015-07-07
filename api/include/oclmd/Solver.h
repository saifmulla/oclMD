#ifndef OclMD_Solver_h
#define OclMD_Solver_h

#include <vector>
#include "oclmd/RealType.h"
#include "oclmd/Tensor.h"
#include "oclmd/System.h"

namespace OclMD {

class ContextImpl;
class Vec3;
//class Tensor;
class Platform;

class Solver {
public:
    /// constructor only taking System ojbect
    Solver(System& system);
    
    /**
     * Overloaded constructor
     * @param System
     * @param Platform
     */
    Solver(System& system, Platform* platform);
    
    /// destructor
    
    ~Solver();
    
    /// get reference to System object
    System& getSystem() const;
    
    /// get reference to const platform object
    const Platform& getPlatform() const;
    
    /// get reference to non const platform object
    Platform& getPlatform();
    
    /// set positions to the simulation its running
    void setPositions(const std::vector<Vec3>& positions);
    
    /// set refferred positions
    void setReferredPositions(const std::vector<std::vector<Vec3> >& referredpositions);
    
    /// get updated forces from the system.
    void getForces(std::vector<Vec3>& forces);
    
    /// get updated virial values
    void getVirial(std::vector<Tensor<double> >& virial);
    
    /// get potential energy
    void getPotentialEnergy(std::vector<Real>& pe);
    
    /// set cell occupancy list
    void setCellOccupancyList(std::vector<std::vector<int> >& cellOccupancy);
    
    /// set referredcell particles
    void setReferredCellParticles(std::vector<std::vector<int> >& refCellParticles);
    
    /// get object of ContextImpl
    ContextImpl& getImpl();
    
    /// invoke calculate forces and energy
    /**
     * TODO: delete later
     * consider this function temporary as it invalidates the
     * concept of API's, essentially this should be invoked 
     * from another internal class such as an integrator
     * in future
     */
    Real calculateForcesandEnergy();
    
private:
    friend class Platform;
    ContextImpl* impl;
    
};//end class solver

}//end namespace
#endif