#ifndef PEA_P1_TSPALGORITHMS_H
#define PEA_P1_TSPALGORITHMS_H

#include <vector>
#include <queue>
#include <list>
#include <limits>

#include "../utilities/TSPUtils.h"

struct BBNodeData {
    // ATSP distances
    std::vector<std::vector<int>> distances;

    // Partial paths already added to possible solution
    std::list<std::list<int>> partialPaths;

    // Index of 0 with highest penalty in distances
    std::pair<int, int> highestPenaltyZeroIndex;

    // Current lower bound
    int lowerBound;

    // Number of already added edges to the path (maximum = instanceSize - 1)
    int edgesOnPath;

    BBNodeData(int instanceSize, int edgesOnPath) : distances(instanceSize, std::vector<int>(instanceSize)),
                                                    highestPenaltyZeroIndex(-1, -1) {
        lowerBound = 0;
        this->edgesOnPath = edgesOnPath;
    }
};

class TSPAlgorithms {

public:
    static int bruteForce(const IGraph *tspInstance);

    static int dynamicProgrammingHeldKarp(const IGraph *tspInstance);

    static int branchAndBound(const IGraph *tspInstance);

private:

    static int
    dpGetPartialPathCost(unsigned int partialPathSet, int endVertexIdx,
                         std::vector<std::vector<int>> &partialPathCostTable,
                         const IGraph *tspInstance);
};


#endif //PEA_P1_TSPALGORITHMS_H
