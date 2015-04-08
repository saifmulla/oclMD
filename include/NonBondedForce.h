//
//  NonBondedForce.h
//  OclMD
//
//  Created by Saif Mulla on 31/03/2015.
//
//

#ifndef OclMD_NonBondedForce_h
#define OclMD_NonBondedForce_h

#include <iostream>
#include <stdio.h>
#include <vector>

#include "RealType.h"
#include "Vec3.h"
#include "Force.h"

using namespace std;

namespace OclMD {
    class MoleculeInfo;
    class LJPairs;
    
class NonBondedForce : public Force {
public:
    /**
     * @ inner class MoleculeInfo
     * this class contains information about each molecules
     * kind of molecule in system
     * this class stores all kind of molecule information
     * such as number of atoms or sites of the molecule,
     * mass, charges etc.
     */

    class MoleculeInfo {

    public:
        Vec3 siteReferencePosition_;
        Real siteMass_;
        Real siteCharge_;
        int siteId_;
        
        MoleculeInfo();
        
        MoleculeInfo(Vec3 siteRefPos, Real siteMass, Real siteCharge, int siteId);

//        ~MoleculeInfo();
    };

    enum NonBondedMethods{
        NoCutoff = 0,
        CutOffPeriodic = 1
    };
    
    /**
     * @class LJPairs
     *
     * This class stores information on L-J interactions between
     * sites
     * information such as sigma, epsilon, rcut etc are stored. The
     * nonbonded class creates a list of such L-J potential objects
     */
    class LJPairs {
    private:
        struct Pairs{
            int one;
            int two;
        };
    public:
        Real sigma_;
        Real epsilon_;
        Real rCut_;
        Real rMin_;
        Real dr_;
        struct Pairs pairs_;
        
        LJPairs();
        
        LJPairs(Real sigma, Real epsilon, Real rCut, Real rMin, Real dr, int pairA, int PairB);
    };

    /// nonBondedForce
    NonBondedForce(int moleculeTypes);
    ~NonBondedForce();
    NonBondedForce::NonBondedMethods getNonBondedMethod() const {
        return method_;
    }
    void setNonBondedMethod(NonBondedMethods method);
    void setCutOffDistance(double distance);
    double getCutOffDistance() const;
private:
    NonBondedMethods method_;
    Real cutOffDistance_;
    /**
     * This variable is to identify the type of molecules
     * in the system such as water, argon etc.
     */
    int numMoleculeTypes_;
    vector<MoleculeInfo>* moleculeList_;
    vector<LJPairs>* ljpairList_;
    
};// end class

}//end namespace
#endif
