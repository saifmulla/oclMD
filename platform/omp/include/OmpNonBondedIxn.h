#ifndef OclMD_OmpNonBondedIxn_h
#define OclMD_OmpNonBondedIxn_h

#include <vector>
#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"
#include "oclmd/Tensor.h"
#include "oclmd/impl/NonBondedForceImpl.h"

namespace OclMD {
    
    typedef Vec3 vector;//just temporarily assume it as vector for user friendlyness
    typedef Tensor<double> tensor; // type define a tensor to simplify it
    class OmpNonBondedIxn {
    public:
        OmpNonBondedIxn(const NonBondedForceImpl::LJInfo** ljinfo);//default constructor
        ~OmpNonBondedIxn();//destructor
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
        //    bool pairRcutSqr(int a, int b,Real magSqr);
        
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
        Real forceLJPairs(const Real rij, const Real sigma, const Real epsilon);
        
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
        Real energyLJPairs(const Real rsIsJmagSqr, const Real sigma, const Real epsilon);
    private:
        const NonBondedForceImpl::LJInfo** ljPairs;
    };
}
#endif /* defined(OclMD_OmpNonBondedIxn_h) */
