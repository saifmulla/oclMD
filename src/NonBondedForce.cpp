//
//  NonBondedForce.cpp
//  OclMD
//
//  Created by Saif Mulla on 01/04/2015.
//
//
#include "Force.h"
#include "NonBondedForce.h"

OclMD::NonBondedForce::NonBondedForce(int moleculeTypes):method_(CutOffPeriodic),cutOffDistance_(2.0),numMoleculeTypes_(moleculeTypes),moleculeList_(0)
{
//    moleculeList_ = new vector<ParticleInfo*>(numMoleculeTypes_);
//    moleculeList_[0].push_back(new NonBondedForce::ParticleInfo(Vec3(0.0,0.0,0.0),6.39,3.12,1,0));
}

OclMD::NonBondedForce::~NonBondedForce(){
//    if(moleculeList_!=NULL){
//        delete moleculeList_;
//        moleculeList_ = 0;
//        std::cout << "Delted moleculeList_" << std::endl;
//    }
//    if(ljpairList_!=NULL)
//    {
//        delete ljpairList_;
//        ljpairList_ = 0;
//    }
}
double OclMD::NonBondedForce::getCutOffDistance() const {
    return cutOffDistance_;
}


int OclMD::NonBondedForce::addLJPair(Real sigma, Real epsilon, Real rCut,
                                     Real rMin, Real dr, int pairA, int PairB){
    ljpairList_.push_back(NonBondedForce::LJPairs(sigma,epsilon,rCut,rMin,dr,pairA,PairB));
    return ljpairList_.size();
}

void OclMD::NonBondedForce::addParticle(Real siteMass, int moleculeId,
                                        Vec3 siteRefPos, Real siteCharge,
                                        Real fraction, int siteId){
    moleculeList_.push_back(NonBondedForce::ParticleInfo(siteRefPos,siteMass,siteCharge,fraction,siteId,moleculeId));
}
OclMD::NonBondedForce::ParticleInfo::ParticleInfo()
:siteReferencePosition_(Vec3(0.0,0.0,0.0)),siteMass_(0.0),
siteCharge_(0.0),siteId_(-1){
}

OclMD::NonBondedForce::ParticleInfo::ParticleInfo(Vec3 siteRefPos, Real siteMass,
                                                  Real siteCharge, Real fraction,
                                                  int siteId, int moleculeId)
:siteReferencePosition_(siteRefPos),siteMass_(siteMass),
siteCharge_(siteCharge),siteId_(siteId),
moleculeId_(moleculeId),frozen_(false),fraction_(fraction){
    if(siteMass_==REALVAL)
        frozen_ = true;
}

//OclMD::NonBondedForce::ParticleInfo::~ParticleInfo(){
//    std::cout << "invoked ParticleInfo destructor" << std::endl;
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

