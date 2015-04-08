//
//  NonBondedForce.cpp
//  OclMD
//
//  Created by Saif Mulla on 01/04/2015.
//
//
#include "Force.h"
#include "NonBondedForce.h"

OclMD::NonBondedForce::NonBondedForce(int moleculeTypes):method_(CutOffPeriodic),cutOffDistance_(2.0),numMoleculeTypes_(moleculeTypes),moleculeList_(0),ljpairList_(0)
{
    moleculeList_ = new vector<MoleculeInfo>(numMoleculeTypes_);
}

OclMD::NonBondedForce::~NonBondedForce(){
    if(moleculeList_!=NULL){
        delete moleculeList_;
        std::cout << "Delted moleculeList_" << std::endl;
    }
    if(ljpairList_!=NULL)
        delete ljpairList_;
}
double OclMD::NonBondedForce::getCutOffDistance() const {
    return cutOffDistance_;
}

OclMD::NonBondedForce::MoleculeInfo::MoleculeInfo()
:siteReferencePosition_(Vec3(0.0,0.0,0.0)),siteMass_(0.0),
siteCharge_(0.0),siteId_(-1){
}

OclMD::NonBondedForce::MoleculeInfo::MoleculeInfo(Vec3 siteRefPos, Real siteMass, Real siteCharge, int siteId)
:siteReferencePosition_(siteRefPos),siteMass_(siteMass),
siteCharge_(siteCharge),siteId_(siteId){
}

//OclMD::NonBondedForce::MoleculeInfo::~MoleculeInfo(){
//    std::cout << "invoked moleculeInfo destructor" << std::endl;
//}

OclMD::NonBondedForce::LJPairs::LJPairs(
                                        Real sigma, Real epsilon,
                                        Real rCut, Real rMin,
                                        Real dr, int pairA, int PairB)
:sigma_(sigma),epsilon_(epsilon),rCut_(rCut),rMin_(rMin),dr_(dr),pairs_({pairA,PairB})
{
//    pairs_.one = pairA;pairs_.two = PairB;
}

OclMD::NonBondedForce::LJPairs::LJPairs(){
    sigma_ = epsilon_ = rCut_ = dr_ = rMin_ = REALVAL;
}

