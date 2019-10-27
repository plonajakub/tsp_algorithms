#ifndef PEA_P1_TSPALGORITHMS_H
#define PEA_P1_TSPALGORITHMS_H

#include <vector>

#include "../utilities/TSPUtils.h"

class TSPAlgorithms {

public:
    static int bruteForce(const IGraph *tspInstance);

    static int dynamicProgrammingHeldKarp(const IGraph *tspInstance);

private:

    static int
    dpGetPartialPathCost(unsigned int partialPathSet, int endVertexIdx, std::vector<std::vector<int>> &partialPathCostTable,
                         const IGraph *tspInstance);
};


#endif //PEA_P1_TSPALGORITHMS_H
