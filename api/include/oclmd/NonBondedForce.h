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

#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"
#include "oclmd/Force.h"

using namespace std;

namespace OclMD {
    
class NonBondedForce : public Force {
public:
    /**
     * @ inner class Particle
     * this class contains information about each molecules
     * kind of molecule in system
     * this class stores all kind of molecule information
     * such as number of atoms or sites of the molecule,
     * mass, charges etc.
     */

    class ParticleInfo {

    public:
        /// site reference position for polyAtomic molecule else set to zero
        Vec3 siteReferencePosition_;
        /// mass of particle
        Real siteMass_;
        /// charge for polyAtomic Molecule or else set to zero
        Real siteCharge_;
        /// siteId - zeror based index representing atom index of molecule
        int siteId_;
        /// moleculeId - zero based index identifying atom to which molecule
        /// it belongs
        int moleculeId_;
        /// frozen - boolean value to determine if atom is frozen
        /// true if value of mass is zero else false
        bool frozen_;
        /// fraction default will be 1.0 otherwise should be specified
        Real fraction_;
        
        
        /**
         * contructor 
         * this is a default constructor 
         * later find way to hide this constructor to abstain from using it
         */
        ParticleInfo();
        
        /**
         * parameterized constructor setting values for particle
         * @param siteRefPos - set Vec3 based datastructor for sitereferenceposition 
         * of atom, set to zero in case of monotomic atom or molecule with one site
         * @param siteMass - mass of site
         * @param siteCharge - charge of atom, zero for monoatomic
         * @siteID - zero based representation of atom in molecule
         * @moleculeID - molecule to which this atom belongs
         */
        ParticleInfo(Vec3 siteRefPos, Real siteMass, Real siteCharge,
                     Real fraction, int siteId, int moleculeId);
        
        //assignment operator
//        ParticleInfo operator=(const ParticleInfo& x)
//        {
//            this->siteReferencePosition_ = x.siteReferencePosition_;
//            this->siteMass_ = x.siteMass_;
//            this->siteCharge_ = x.siteCharge_;
//            this->fraction_ = x.fraction_;
//            this->frozen_ = x.frozen_;
//            this->siteId_ = x.siteId_;
//            this->moleculeId_ = x.moleculeId_;
//        }

//        ~ParticleInfo();
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
        /**
         * Structure Pairs
         * this is used to store LJ potential pairs of atoms
         * essentially its the atom index of the molecules
         * it is used as member variable in LJPairs class below
         */
        struct Pairs{
            int one;
            int two;
        };
        
    public:
        Real sigma_;/// sigma
        Real epsilon_;/// epsilon
        Real rCut_;/// cutoff radium between atoms
        Real rMin_;/// minimum cutoff radius between atoms
        Real dr_;/// dr
        Real rCutSqr_; //square of cutoff radius
        struct Pairs pairs_; /// pair of atom index to calculate potential
        
        /// default constructor
        LJPairs();
        
        /**
         * parameterised constructor
         * @param sigma - double/float Real type
         * @param epsilon - Real type
         * @param rCut - Real type
         * @param rMin - Real type
         * @param dr - Real type
         * @param pairA - A particle index of LJ pair atoms int type
         * @param pairB - B particle index of LJ pair atoms int type
         */
        
        LJPairs(Real sigma, Real epsilon, Real rCut, Real rMin, Real dr, int pairA, int PairB);
    };


    /// from here starts declaration for NonBondedForce class
    
    /**
     * constructor
     * @param moleculeType - specify number of molecule types in simulation
     * default value is set to 1 if no value supplied
     */
    NonBondedForce(int moleculeTypes = 1);
    
    /// destructor
    ~NonBondedForce();
    
    /// utility functions
    
    /**
     * function addLJPair
     * this function is used to initialise and the list of LJPairs type
     * @param sigma
     * @param epsilon
     * @param rCut
     * @param rMin
     * @param dr
     * @param pairA - lhs index of atom in the pair
     * @param pairB - rhs index of atom in the pair
     *
     */
    int addLJPair(Real sigma, Real epsilon, Real rCut, Real rMin, Real dr, int pairA, int PairB);
    
    /**
     * function addParticle
     * this function is used is used to propogate or initialise the list of 
     * ParticleInfo type
     *
     * This function contain default values for all arguments except siteMass 
     * and MoleculeId, which are kind of required in any case. 
     * Although the default values are
     * set for convinience of MonoAtomic atom type, ideally a monoAtomic or 
     * argon molecule or atom does not contains reference positions, charge. 
     * subsequently being only one atom the siteId is always 0
     */
    void addParticle(Real siteMass, int moleculeId,
                     Vec3 siteRefPos = Vec3(REALVAL,REALVAL,REALVAL),
                     Real siteCharge = REALVAL, Real fraction = 1.0,
                     int siteId = 0);
    
    /**
     * get the non bonded method by returning
     * @param NonBondedMethods type
     */
    NonBondedForce::NonBondedMethods getNonBondedMethod() const {
        return method_;
    }
    /// set the nonbonded method supplied
    void setNonBondedMethod(NonBondedMethods method);
    /// set cutOff distance for simulation
    void setCutOffDistance(double distance);
    /// getCutOff distance
    double getCutOffDistance() const;
    
    /// getList of LJPairs
    vector<OclMD::NonBondedForce::LJPairs>& getListLJPairs();
    
    /// get list of ParticleInfo
    vector<NonBondedForce::ParticleInfo>& getListParticleInfo();
    
protected:
    ForceImpl* createImpl();
private:
    NonBondedMethods method_;
    Real cutOffDistance_;
    /**
     * This variable is to identify the number of molecules
     * in the system, there could be 1 or more type or kind 
     * of molecules
     */
    int numMoleculeTypes_;
    /**
     * the vector list of ParticleInfo
     * stores information about each type of molecule
     */
    vector<ParticleInfo> moleculeList_;
    /**
     * The vector list of LJPairs
     * will contain list of LJ potential to be calculated
     * between atoms of molecules
     */
    vector<LJPairs> ljpairList_;
    
};// end class

}//end namespace
#endif
