//
//  CpuNonBondedIxn.cpp
//  OclMD
//
//  Created by Saif Mulla on 03/04/2015.
//
//

#include "CpuNonBondedIxn.h"

OclMD::CpuNonBondedIxn::CpuNonBondedIxn(const OclMD::NonBondedForceImpl::LJInfo** ljinfo):ljPairs(ljinfo){
}

OclMD::CpuNonBondedIxn::~CpuNonBondedIxn(){
    if(ljPairs!=NULL)
        delete ljPairs;
}

void OclMD::CpuNonBondedIxn::calculateForces(int numberParticles,
                                             std::vector<Vec3>& positions,
                                             std::vector<Vec3>& forces,
                                             std::vector<Real>& pE,
                                             std::vector<tensor>& virial
                                             )
{

#ifdef FULLDEBUG
    std::cout << "Calcualting forces inside CPUNONBONDEDIXN" << std::endl;
#endif
    for (int i=0; i<numberParticles; i++)
    {
        vector atomI = positions[i];/// get one atom for atom I
        for (int j = i+1; j<numberParticles;j++)
        {
            ///periodic boundary condition
            
            /// get one atom for atom interaction
            vector atomJ = positions[j];
            Real fraction = 1.0;
            // distance delta between two atoms positions
            vector rsIsJ = atomI - atomJ;
            //get magnitude square for distance delta
            Real rsIsJMagSq = MagSqr(rsIsJ);

            /**
             * determine rcutSqr between two interacting atoms
             * essentially this is based on the Lennard Jones potential
             * interactions between two atoms. Here it is simply checked 
             * if the atoms interacting are in interaction range of supplied
             * rcut. Therefore the value is
             * obtained by supplying the atom id to get appropriate 
             * rCutSqr from the list if available
             */
            const OclMD::NonBondedForceImpl::LJInfo& lj = ljPairs[0][0];
            /**
             * check if the distance IJ magSquare is less than the 
             * rCutSqr defined for the LJ pair if it is within
             * then perform pair-wise force calculation
             */

            if(rsIsJMagSq < lj.rCutSqr)
            {
                Real rsIsJMag = Mag(rsIsJMagSq);
                
                Real force = forceLJPairs(rsIsJMag,lj.sigma,lj.epsilon);
                force *= 1.0;
                vector forceContribution = rsIsJ/rsIsJMag;
                forceContribution *= force; // multiply the force result with vector
                
                //add calculated force to each atomic force
                forces[i] += forceContribution;
                forces[j] += -forceContribution;
                
                /**
                 * calculate potential energy based on LJ potential equation
                 * supply atom ids to determine sigma and epsilon based on 
                 * pairs
                 */
                Real pe = fraction * energyLJPairs(rsIsJMag,lj.sigma,lj.epsilon);
                pE[i] += 0.5 * pe;
                pE[j] += 0.5 * pe;
                
                /// calculate virial contribution and add to virial of each atom
                Tensor<double> virialContribution = outerProduct<double>(forceContribution,rsIsJ);
                virial[i] += virialContribution;
                virial[j] += virialContribution;
                
                
            }//end of rcutSqr check
            
        }
    }
}

Real OclMD::CpuNonBondedIxn::forceLJPairs(const Real rij,
                                          const Real sigma,
                                          const Real epsilon)
{
    Real ps6 = POW(sigma,6);
    Real ps12 = POW(sigma,12);
    Real rij13 = POW(rij,13);
    Real rij7 = POW(rij,7);
    
    Real numerator1 = 48 * epsilon * ps12;
    numerator1 /= rij13;
    Real numerator2 = -24 * epsilon * ps6;
    numerator2 /= rij7;
    /// return the result back
    return (numerator1 + numerator2);
}

Real OclMD::CpuNonBondedIxn::energyLJPairs(const Real rij,
                                           const Real sigma,
                                           const Real epsilon){
    Real div = sigma / rij;
    Real result = POW(div,12);
    result -= POW(div,6);
    result *= 4.0 * epsilon;
    return result;
}




//******************* end of file *********************************//

