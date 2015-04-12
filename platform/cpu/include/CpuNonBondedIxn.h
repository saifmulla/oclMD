//
//  CpuNonBondedIxn.h
//  OclMD
//
//  Created by Saif Mulla on 03/04/2015.
//
//

#ifndef __OclMD__CpuNonBondedIxn__
#define __OclMD__CpuNonBondedIxn__

#include <vector>
#include "Vec3.h"
#include "Tensor.h"

namespace OclMD {

typedef Vec3 vector;//just temporarily think it as vector for user friendlyness
typedef Tensor<double> tensor; // type define a tensor to simplify it
class CpuNonBondedIxn {
public:
    CpuNonBondedIxn();//default constructor
    ~CpuNonBondedIxn();//destructor
    /**
     * @function calculateForces
     * this function calcualate pair-wise interactions between atoms
     * alongside it calculated L-J potential between atoms and also
     * energy
     * @param numberParticles - number of particles in the system
     * @param positions - positions of vec3 type equal to number of particles
     * @param forces - forces of vec3 type equal to number of particles
     * @param atomId
     */
    void calculateForces(int numberParticles, std::vector<Vec3>& positions,
                         std::vector<Vec3>& forces,
                         std::vector<Real>& pE,
                         std::vector<tensor>& virial);
//                        , std::vector<int>& atomId,
//                         std::vector<int>& moleculeId);
    
    /**
     * @function pairRcutSqr
     * @param siteId a atom
     * @param siteId b atom
     * @param double/Real magnitude square of delta distance of between atoms
     * return @param bool
     *
     * determines if the supplied magnitude square is less than maximum 
     * rcut Square for the LJ potential between the two sites if withing
     * range return true else false
     */
    bool pairRcutSqr(int a, int b,Real magSqr);
    
    /**
     * @function forceLJPairs
     * @param siteId a atom
     * @param siteId b atom
     * @param double/Real magnitude of delta distance of between atoms
     * return @param real/double
     *
     * calculate the equation for LJ potential for force based on 
     * Lennard-Jones Potential Equation 
     * reference link - http://chemwiki.ucdavis.edu/Physical_Chemistry/Intermolecular_Forces/Lennard-Jones_Potential
     *
     */
    Real forceLJPairs(int a, int b, Real magSqr);
    
    /**
     * @function energyLJPairs
     *
     * @param siteId a atom
     * @param siteId b atom
     * @param double/Real magnitude of delta distance of between atoms
     * return @param real/double
     *
     * calcuate the energy equation based on LJ potential on two atom pairs
     * refer the above link for equation
     * 4*epsilon * ((sigma/magsqr)^12 - (sigma/magsqr)^6)
     *
     */
    Real energyLJPairs(int a, int b, Real magSqr);
     
     
     
     
     
     
     
};
}
#endif /* defined(__OclMD__CpuNonBondedIxn__) */
