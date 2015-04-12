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

void OclMD::CpuNonBondedIxn::calculateForces(int numberParticles,
                                             std::vector<Vec3>& positions,
                                             std::vector<Vec3>& forces,
                                             std::vector<Real>& pE,
                                             std::vector<tensor>& virial){

    for (int i=0; i<numberParticles; i++)
    {
        vector atomI = positions[i];/// get one atom for atom I
        for (int j = i+1; j<numberParticles;j++)
        {
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
            if(pairRcutSqr(i,j,rsIsJMagSq))
            {
                Real rsIsJMag = Mag(rsIsJMagSq);
                
                Real force = forceLJPairs(i,j,rsIsJMagSq);
                
                vector forceContribution = (rsIsJ/rsIsJMagSq) * fraction;
                
                //add calculated force to each atomic force
                forces[i] += forceContribution;
                forces[j] += -forceContribution;
                
                /**
                 * calculate potential energy based on LJ potential equation
                 * supply atom ids to determine sigma and epsilon based on 
                 * pairs
                 */
                Real pe = fraction * energyLJPairs(0,0,rsIsJMag);
                pE[i] += 0.5 * pe;
                pE[j] += 0.5 * pe;
                
                // calculate virial contribution and add to virial of each atom
                
                
                
            }//end of rcutSqr check
            
        }
    }
}

bool OclMD::CpuNonBondedIxn::pairRcutSqr(int a, int b, Real magSqr){
    return true;
}

Real OclMD::CpuNonBondedIxn::forceLJPairs(int a, int b, Real magSqr){
    return 1.0;
}

Real OclMD::CpuNonBondedIxn::energyLJPairs(int a, int b, Real magSqr){
    return 1.0;
}




//******************* end of file *********************************//

