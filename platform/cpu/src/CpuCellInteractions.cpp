#include "CpuCellInteractions.h"

OclMD::CpuCellInteractions::CpuCellInteractions(Vec3* boxDimension,Real rCut)
:referredPositions_(0),boxDimensions_(boxDimension),rCut_(rCut),cellIndexes_(0),
corneringCells_(0),referredCells_(0),leftSideCells_(0),rightSideCells_(0),
middleCells_(0){
    totalCells_ = 0;
    totalCornerCells_ = 0;
    nCellsRight_ = 0;
    nCellsLeft_ = 0;
    roundedRcut_ = (int) floor(rCut_);
    nCellsX_ = (int) floor(boxDimensions_[0][0]/rCut_);
    nCellsY_ = (int) floor(boxDimensions_[1][1]/rCut_);
    nCellsZ_ = (int) floor(boxDimensions_[2][2]/rCut_);
    roundedBoxDims_[0] = (int) floor(boxDimensions_[0][0]);
    roundedBoxDims_[1] = (int) floor(boxDimensions_[1][1]);
    roundedBoxDims_[2] = (int) floor(boxDimensions_[2][2]);
}

OclMD::CpuCellInteractions::~CpuCellInteractions(){
    if (referredPositions_!=NULL)
        delete referredPositions_;
    if (cellIndexes_!=NULL)
        delete cellIndexes_;
    if (corneringCells_ != NULL)
        delete corneringCells_;
}

int OclMD::CpuCellInteractions::getNumReferredPositions(){
    return sizeof(referredPositions_)/(sizeof(Real)*3);
}

void OclMD::CpuCellInteractions::initialise(){
    /**
     * create cells
     * essentially dividing the domain into cubes of rcut size
     * keep a counter of number of cells and number cell indexes
     * also keeping the starting and ending point of cell inside the domain
     * precisely the position of the cell.
     */
    
    std::vector<int> cellindexes;
    std::vector<int> corneringcells;
    std::vector<int> leftsidecells;
    std::vector<int> rightsidecells;
    std::vector<int> middleCells;
    
    for (int z = 0; z < nCellsZ_; z++) {
        for (int y = 0; y < nCellsY_; y++) {
            for (int x = 0; x < nCellsX_; x++) {
                totalCells_++;
                int index = totalCells_ - 1;
                cellindexes.push_back(index);
            }//x dimension array
        }//y dimension array
    }//z dimension array
    
}

const int* OclMD::CpuCellInteractions::getCellIndexes() const {
    return cellIndexes_;
}

const int* OclMD::CpuCellInteractions::getCorneringCellIndexes() const {
    return corneringCells_;
}

const int* OclMD::CpuCellInteractions::getLeftSideCellIndexes() const {
    return leftSideCells_;
}

const int* OclMD::CpuCellInteractions::getRightSideCellIndexes() const {
    return rightSideCells_;
}

void OclMD::CpuCellInteractions::generateCellInteractionList() {
    std::vector<std::vector<int> > neighbourlist(totalCells_);
    
    const int d3d = nCellsZ_ * nCellsX_;
    
    for (int z = 1; z < (nCellsZ_-1); z++) {
        for (int y = 1; y < (nCellsY_-1); y++) {
            for (int x = 1; x < (nCellsX_-1); x++) {
                int index = (z*nCellsZ_*nCellsZ_) + (y * nCellsY_) + x;
                /// starting from back side
                /// exact bottom below
                neighbourlist[index].push_back(index-d3d-nCellsY_-1);
                neighbourlist[index].push_back(index-d3d-nCellsY_);
                neighbourlist[index].push_back(index-d3d-nCellsY_+1);
                /// exact behind
                neighbourlist[index].push_back(index-d3d-1);
                neighbourlist[index].push_back(index-d3d);
                neighbourlist[index].push_back(index-d3d+1);
                /// behind top
                neighbourlist[index].push_back(index-d3d+nCellsY_-1);
                neighbourlist[index].push_back(index-d3d+nCellsY_);
                neighbourlist[index].push_back(index-d3d+nCellsY_+1);
                /// now in xy dimension starting from bottom
                /// bottom left
                neighbourlist[index].push_back(index-nCellsY_-1);
                /// bottom
                neighbourlist[index].push_back(index-nCellsY_);
                /// botom right
                neighbourlist[index].push_back(index-nCellsY_+1);
                /// left
                neighbourlist[index].push_back(index-1);
                /// right
                neighbourlist[index].push_back(index+1);
                /// now bottom left
                neighbourlist[index].push_back(index+nCellsY_-1);
                /// bottom
                neighbourlist[index].push_back(index+nCellsY_);
                /// botom right
                neighbourlist[index].push_back(index+nCellsY_+1);
                /// secondly add cell in Z dimension
                /// bottom cells in z direction
                neighbourlist[index].push_back(index+d3d-nCellsY_-1);
                neighbourlist[index].push_back(index+d3d-nCellsY_);
                neighbourlist[index].push_back(index+d3d-nCellsY_+1);
                /// front cells
                neighbourlist[index].push_back(index+d3d-1);
                neighbourlist[index].push_back(index+d3d);
                neighbourlist[index].push_back(index+d3d+1);
                /// top cells in z direction
                neighbourlist[index].push_back(index+d3d+nCellsY_-1);
                neighbourlist[index].push_back(index+d3d+nCellsY_);
                neighbourlist[index].push_back(index+d3d+nCellsY_+1);
            }// end x
        }// end y
    }// end z
    
    cellInteractionList_ = (int**) malloc(sizeof(int*) * totalCells_);
    
    for (int c = 0; c < totalCells_; c++) {
        int dimsize = neighbourlist[c].size();
        if (dimsize != 0) {
            cellInteractionList_[c] = (int*) malloc(sizeof(int) * dimsize);
//            std::cout << "CellID #" << c << " => [";
            for (int d = 0; d < dimsize; d++) {
                cellInteractionList_[c][d] = neighbourlist[c][d];
//                std::cout << neighbourlist[c][d] << ",";
            }
//            std::cout << "]" << std::endl;
        }
    }
}

void OclMD::CpuCellInteractions::generatePositionCellIndexes(std::vector<Vec3>& positions){
    
    std::vector<int> cellPosition(positions.size());
    std::vector<std::vector<int> > positionsInCells(totalCells_);
    
    for (int p = 0; p < positions.size(); p++) {
        if (positions[p][0] == 0.0
            && positions[p][1] == 0.0
            && positions[p][2] == 0.0) {
            /// if all the values of position is zero then certainly
            /// it belongs to cell 0
            cellPosition[p] = 0;
            positionsInCells[0].push_back(p);
        }
        else{
            
        }
    }
}
void OclMD::CpuCellInteractions::generateReferredPositions(
                                            std::vector<OclMD::Vec3>& realPositions)
{
    std::vector<OclMD::Vec3> tempRefPositions;
    
    for (int p = 0; p < realPositions.size(); p++) {
        if (realPositions[p][0] < rCut_) {
            OclMD::Vec3 posx = realPositions[p];
            OclMD::Vec3 posy = realPositions[p];
            OclMD::Vec3 posz = realPositions[p];
            /// add referred position to XYZ dimention in the domain
            posx[0] += boxDimensions_[0][0];
            tempRefPositions.push_back(posx);
            
            posy[1] += boxDimensions_[1][1];
            tempRefPositions.push_back(posy);
            
            posz[2] += boxDimensions_[2][2];
            tempRefPositions.push_back(posz);
            
            /// check if the position is in corner
            
        }
    }
}
