//
//  CpuBases.cpp
//  OclMD
//
//  Created by Saif Mulla on 28/04/2015.
//
//

#include "CpuBases.h"


/// utility static functions

static std::vector<OclMD::Vec3>& extractPositions(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Vec3>*) data->positions_);
}

static std::vector<OclMD::Vec3>& extractForces(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Vec3>*) data->forces_);
}

static std::vector<OclMD::Tensor<double> >& extractVirial(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Tensor<double> >*) data->virial_);
}

static std::vector<double>& extractPE(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<double>*) data->pE_);
}

static OclMD::Vec3& extractBoxDimensions(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *(OclMD::Vec3*) data->periodicBoxSize_;
}

static std::vector<std::vector<OclMD::Vec3> >& extractReferredPositions(OclMD::ContextImpl& context){
    OclMD::CpuPlatform::PlatformData* data = reinterpret_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<std::vector<OclMD::Vec3> >*) data->referredPositions_);
}

void OclMD::CpuBaseCalculateForcesAndEnergy::initialise(const System& system){
    
}

void OclMD::CpuBaseCalculateForcesAndEnergy::prepare(ContextImpl& context){
    /// zero all data structure
    std::vector<OclMD::Vec3>& forces = extractForces(context);
    std::vector<OclMD::Tensor<double> >& virial = extractVirial(context);
    std::vector<double>& pe = extractPE(context);
    
    for (int i = 0; i <context.getSystem().getNumParticles(); i++) {
        forces[i] = OclMD::Vec3(0.0,0.0,0.0);
        virial[i] = OclMD::Tensor<double>(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
        pe[i] = 0.0;
    }
}

Real OclMD::CpuBaseCalculateForcesAndEnergy::calculate(ContextImpl& context){
    return 0.0;
}

/// definition of class CpuBaseData

void OclMD::CpuBaseData::initialise(const System& system, ContextImpl& context){
    
    /**
     * read information about direct interaction list and neighbour cells
     * due to multiple constructors for the System there is a possibility
     * that these arrays could be supplied null or zero therefore check
     * if these array are contained if they are contained then do
     * appropriate assignment.
     * the arrays are initially set to null because in case
     * if the arrays through system are null it would not affect the
     * creation of object in the system.
     */
    
    /// TODO: later make invocation of this functionality more efficient
    std::vector<std::vector<int> > dil;
    std::vector<std::vector<int> > neighbourcells;

    if (system.getnCells()>0) {
        dil.resize(system.getnCells());
        const std::vector<std::vector<int> >& tempdil = system.getDil();
        for (int d = 0; d < system.getnCells(); d++) {
            int size = tempdil[d].size();
            dil[d].resize(size);
            for (int j = 0; j < size; j++) {
                const int tempdj = tempdil[d][j];
                dil[d][j] = tempdj;
            }
        }
        
        neighbourcells.resize(system.getnRefCells());
        const std::vector<std::vector<int> >& temprefcells = system.getNeighbouringCells();
        for (int d = 0; d < system.getnRefCells(); d++) {
            int size = temprefcells[d].size();
            neighbourcells[d].resize(size);
            for (int j = 0; j < size; j++) {
                const int tempdj = temprefcells[d][j];
                neighbourcells[d][j] = tempdj;
            }
        }
    }
    
    
    interactionCells_ = new OclMD::CpuInteractionCells(dil,
                                                       neighbourcells,
                                                       system.getnCells(),
                                                       system.getnRefCells());
    
    OclMD::CpuPlatform::PlatformData* pd = static_cast<OclMD::CpuPlatform::PlatformData*>(context.getPlatformData());
    pd->setReferredPositions(system.getnRefCells());
}

void OclMD::CpuBaseData::setPositions(ContextImpl& context,
                                      const std::vector<Vec3>& positions){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<OclMD::Vec3>& dataPositions = extractPositions(context);
    for(int i = 0; i < numparticles; i++){
        dataPositions[i] = positions[i];
    }
    
}

void OclMD::CpuBaseData::setReferredPositions(ContextImpl& context,
                                              const std::vector<std::vector<Vec3> >& referredPositions){
    /// beaware these positions do not have any specific size so simply follow
    /// deinitialise and reinitialise patter
    int numrefpos = referredPositions.size();
    std::vector<std::vector<OclMD::Vec3> >& refPos = extractReferredPositions(context);
    
    /// firstly clear all the existing positions in the list
    for (int i = 0; i < numrefpos; i++) {
        refPos[i].clear();
    }

    /// now add newly supplied positions to each specific cell
    for (int c = 0; c < refPos.size(); c++) {
        int size = referredPositions[c].size();
        refPos[c].resize(size);
        for (int j = 0; j < size; j++) {
            refPos[c][j] = referredPositions[c][j];
        }
    }
    
}

void* OclMD::CpuBaseData::getInteractionCells(){
    return (void*) interactionCells_;
}

void OclMD::CpuBaseData::setCellOccupancyList(OclMD::ContextImpl& context, const std::vector<std::vector<int> > &cellOccupancy){
    interactionCells_->setCellOccupancy(cellOccupancy);
}

void OclMD::CpuBaseData::setReferredCellParticles(OclMD::ContextImpl& context, const std::vector<std::vector<int> > &referredCellParticles){
    interactionCells_->setRefCellParticles(referredCellParticles);
}

void OclMD::CpuBaseData::getForces(ContextImpl& context,
                                   std::vector<Vec3>& forces){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<OclMD::Vec3>& dataForces = extractForces(context);
    for (int i = 0; i < numparticles; i++) {
        forces[i] = dataForces[i];
    }
    
}

void OclMD::CpuBaseData::getVirial(OclMD::ContextImpl& context, std::vector<OclMD::Tensor<double> >& virial){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<OclMD::Tensor<double> >& dataVirial = extractVirial(context);
    for (int i = 0; i < numparticles; i++) {
        virial[i] = dataVirial[i];
    }
}

void OclMD::CpuBaseData::getPotentialEnergy(OclMD::ContextImpl& context, std::vector<double>& pe){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<double>& dataPE = extractPE(context);
    for (int i = 0; i < numparticles; i++) {
        pe[i] = dataPE[i];
    }
}


void OclMD::CpuBaseData::setPeriodicBox(ContextImpl& context,
                                        const Vec3& x, const Vec3& y, const Vec3& z) const {
    OclMD::Vec3& boxdim = extractBoxDimensions(context);
    boxdim[0] = x[0]; //x axis;
    boxdim[1] = y[1]; //y axis;
    boxdim[2] = z[2]; //z axis;
}

void OclMD::CpuBaseData::getPeriodicBox(ContextImpl& context,
                                        Vec3& x, Vec3& y, Vec3& z) const {
    
};


const std::vector<int>* OclMD::CpuBaseData::getCellOccupancyListByCell(int cellId){
    return interactionCells_->getCellOccupancy(cellId);
}

const std::vector<int>* OclMD::CpuBaseData::getRefCellParticlesByCell(int cellId){
    return interactionCells_->getRefCellParticles(cellId);
}


/// definition for class CpuCalculateNonBondedForceBase
void OclMD::CpuBaseCalculateNonBondedForce::initialise(const System& system,
                                                       const NonBondedForceImpl& force,
                                                       ContextImpl& context)
{
    nonbondedixn = new OclMD::CpuNonBondedIxn((const OclMD::NonBondedForceImpl::LJInfo**) force.getLJInfo());
    interactionCells_ = static_cast<CpuInteractionCells*>(context.getInteractionCells());
}

void OclMD::CpuBaseCalculateNonBondedForce::preprocess(void* interactioncells) {
}


Real OclMD::CpuBaseCalculateNonBondedForce::calculate(ContextImpl& context)
{
    std::vector<OclMD::Vec3>& positions = extractPositions(context);
    std::vector<OclMD::Vec3>& forces = extractForces(context);
    std::vector<OclMD::Tensor<double> >& virial = extractVirial(context);
    std::vector<Real>& pe = extractPE(context);
    
    /**
     * calculate forces for positions in each cells
     * this is to assit the compiler for locality
     * optimisations and predictability access
     */
    
    for (int c = 0; c < interactionCells_->nCells(); c++) {
        /// get the list of position indexes for each cell
        const std::vector<int>* cellOccupancyList = interactionCells_->getCellOccupancy(c);
    
        for (int i = 0; i < cellOccupancyList->size(); i++)
        {
            const Vec3& rI = positions[cellOccupancyList->at(i)];
            Vec3& forceI = forces[cellOccupancyList->at(i)];
            Real& peI = pe[cellOccupancyList->at(i)];
            Tensor<double>& rfI = virial[cellOccupancyList->at(i)];
            
            for (int j = i+1; j < cellOccupancyList->size(); j++)
            {
                const Vec3& rJ = positions[cellOccupancyList->at(j)];
                Vec3& forceJ = forces[cellOccupancyList->at(j)];
                Real& peJ = pe[cellOccupancyList->at(j)];
                Tensor<double>& rfJ = virial[cellOccupancyList->at(j)];
                
                nonbondedixn->calculateForce(rI,rJ,forceI,forceJ,peI,peJ,rfI,rfJ,0,0);
            }
        }
    }

    /**
     * next calcualte forces between all neighbouring cells
     * in this case a cell is picked and also the list its neighbours
     * then in a position is picked for selected cell and then pair-wise 
     * forces are calculated with all positions of its neightbouring cells
     * this procedure is performed for each position in each cell and in all
     * cells.
     */
  
    for (int c = 0; c < interactionCells_->nCells(); c++) {
        /// get the list of position indexes for each cell
        const std::vector<int>* cellOccupancyList = interactionCells_->getCellOccupancy(c);
        /// traverse through each molecule in the cell
        for (int m = 0; m<cellOccupancyList->size(); m++) {
            int index = cellOccupancyList->at(m);
            Vec3& rI = positions[index];
            Vec3& fI = forces[index];
            Real& peI = pe[index];
            Tensor<double>& rfI = virial[index];
            
            const std::vector<int>* dillist = interactionCells_->getDil(c);
            for (int nbc = 0; nbc < dillist->size(); nbc++) {
                int jcellid = dillist->at(nbc);
                const std::vector<int>* celllistj = interactionCells_->getCellOccupancy(jcellid);
                for (int j = 0; j < celllistj->size(); j++) {
                    int jindex = celllistj->at(j);
                    Vec3& rJ = positions[jindex];
                    Vec3& fJ = forces[jindex];
                    Real& peJ = pe[jindex];
                    Tensor<double>& rfJ = virial[jindex];

                    nonbondedixn->calculateForce(rI,rJ,fI,fJ,peI,peJ,rfI,rfJ,0,0);
                }
            }
        }
    }
    
    /// real <-> referred interaction
    const std::vector<std::vector<Vec3> >& refPositions = extractReferredPositions(context);
    for (int r = 0; r < interactionCells_->nRefCells(); r++)
    {
        for (int i=0; i < refPositions[r].size(); i++)
        {
            const Vec3 rJ = refPositions[r][i];
            Vec3 fJ;
            Real peJ = 0.0;
            Tensor<double> rfJ;
            
            /// get the list of real neighbouring cells to this referred cell
            const std::vector<int>* realNeighbours = interactionCells_->getNeighbouringCells(r);
            for (int j = 0; j < realNeighbours->size(); j++)
            {
                int cellidi = realNeighbours->at(j);
                const std::vector<int>* dil = interactionCells_->getDil(cellidi);
                for (int celli = 0; celli < dil->size(); celli++)
                {
                    const std::vector<int>* celllisti = interactionCells_->getCellOccupancy(celli);
                    for (int d = 0; d < celllisti->size(); d++)
                    {
                        const int riIndex = celllisti->at(d);
                        const Vec3& rI = positions[riIndex];
                        Vec3& fI = forces[riIndex];
                        Real& peI = pe[riIndex];
                        Tensor<double>& rfI = virial[riIndex];
                        
                        nonbondedixn->calculateForce(rJ,rI,fI,fJ,peI,peJ,rfI,rfJ,0,0);
                        
                    }// d loop ends
                }// celli loop ends
            }// j loop ends
        }// i loop ends
    }// r loops ends
    
    /*
    for (int c = 0; c<interactionCells_->nCells(); ++c)
    {
        for (int m = 0; m < interactionCells_->getCellOccupancy()[c].size(); ++m)
        {
            OclMD::Vec3* rI = interactionCells_->getCellOccupancy()[c][m];
            
            // for all real cells within DIL
            for (int cJ = 0; cJ < interactionCells_->getDIL()[c].size(); ++cJ)
            {
                int cellJ = interactionCells_->getDIL()[c][cJ]; // place reference/pointer here
                
                for (int mJ = 0; mJ < interactionCells_->getCellOccupancy()[cellJ].size(); ++mJ)
                {
                    OclMD::Vec3* rJ = interactionCells_->getCellOccupancy()[cellJ][mJ];
                    
                    evaluatePair(rI, rJ, pairPotList, electrostatics);
                }
            }
            
            // within owner real cell
            for (int mJ = 0; mJ < interactionCells_->getCellOccupancy()[c].size(); ++mJ)
            {
                OclMD::Vec3* rJ = interactionCells_->getCellOccupancy()[c][mJ];
                
                if (mJ > m)
                {
                    evaluatePair(rI, rJ, pairPotList, electrostatics);
                }
            }
        }
    }
    
    
    // Real-Referred interactions
    for (int r = 0; r<interactionCells_->nRefCells(); ++r)
    {
        
        for (int i = 0; i<interactionCells_->refCellParticles()[r]; ++i)
        {
            OclMD::Vec3* rJ = interactionCells_->refCellParticles()[r][i];
            
            int nRealCells = interactionCells_->neighbouringCells()[r].size();
            
            for (int k = 0; k<nRealCells; ++k)
            {
                int realCell = interactionCells_->neighbouringCells()[r][k];
                
                int nRealMolecules = interactionCells_->getCellOccupancy()[realCell].size();
                
                for (int j = 0; j<nRealMolecules; ++j)
                {
                    OclMD::Vec3* rI = interactionCells_->getCellOccupancy()[realCell][j];
                    
                    evaluatePair(rI, rJ, pairPotList,electrostatics);
                }
            }
        }
    }

    */
//    nonbondedixn->calculateForces(context.getSystem().getNumParticles(),
//                                 extractPositions(context),
//                                 extractForces(context),
//                                 extractPE(context),
//                                 extractVirial(context));
    
    
    return 0.0;
}


