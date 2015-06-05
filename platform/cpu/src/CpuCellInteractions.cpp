#include "CpuCellInteractions.h"

OclMD::CpuCellInteractions::CpuCellInteractions(Vec3* boxDimension,Real rCut)
:referredPositions_(0),boxDimensions_(boxDimension),rCut_(rCut),cellIndexes_(0),
corneringCells_(0),referredCells_(0),leftSideCells_(0),rightSideCells_(0){
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
    
    for (int z = 0; z < nCellsZ_; z++) {
        for (int y = 0; y < nCellsY_; y++) {
            for (int x = 0; x < nCellsX_; x++) {
                totalCells_++;
                int index = totalCells_ - 1;
                cellindexes.push_back(index);

                /// check if the z index lies in first or last list
                if (z==0 || z > (nCellsZ_ - 2)) {
                    /// then check if y is zero or the last list
                    if (y==0||y > (nCellsY_ - 2)){
                        corneringcells.push_back(index);
                        totalCornerCells_++;
                    }
                    else if(x==0 || x > (nCellsX_ - 2)){
                        corneringcells.push_back(index);
                        totalCornerCells_++;
                    }
                
                    /// check condition to determine cell lies on
                    /// left or right side
                    if(x == 0)
                        leftsidecells.push_back(index);
                    else if(x > (nCellsX_- 2))
                        rightsidecells.push_back(index);
                }
                else if(x==0 || x > (nCellsX_ - 2)){
                    corneringcells.push_back(index);
                    totalCornerCells_++;
                    /// check condition to determine cell lies on
                    /// left or right side
                    if(x == 0 && (y==0 || y > (nCellsY_ - 2)))
                        leftsidecells.push_back(index);
                    else if(x > (nCellsX_- 2) && (y==0 || y > (nCellsY_ - 2)))
                        rightsidecells.push_back(index);

                }
            }//x dimension array
        }//y dimension array
    }//z dimension array
    
    
    cellIndexes_ = (int*) malloc(sizeof(int)*totalCells_);
    
    /// copy temporary cellIndexes to newly allocated memory
    for (int i = 0; i < totalCells_; i++) {
        cellIndexes_[i] = cellindexes[i];
    }
    
    int size_cornering_cells = corneringcells.size();
    corneringCells_ = (int*) malloc(sizeof(int)*size_cornering_cells);
    /// copy tempory cornering cells to newly allocated memory
    for (int i = 0; i < size_cornering_cells; i++)
        corneringCells_[i] = corneringcells[i];
    
    /// determine refferred cells
    int tempsize = leftsidecells.size();
    leftSideCells_ = (int*) malloc(sizeof(int)*tempsize);
    for (int j = 0; j < tempsize; j++) {
        leftSideCells_[j] = leftsidecells[j];
    }
    nCellsLeft_ = tempsize;
    
    tempsize = rightsidecells.size();
    rightSideCells_ = (int*) malloc(sizeof(int)*tempsize);
    for (int j = 0; j < tempsize; j++) {
        rightSideCells_[j] = rightsidecells[j];
    }
    nCellsRight_ = tempsize;
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
