#ifndef PEA_P1_TSPALGORITHMS_H
#define PEA_P1_TSPALGORITHMS_H

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <algorithm>

#include "../utilities/TSPUtils.h"

struct EdgeCities {
    int i;
    int j;

    EdgeCities() = default;

    EdgeCities(int i, int j) : i(i), j(j) {}
};

struct Penalties {
    int row;
    int column;

    Penalties() = default;

    Penalties(int row, int column) : row(row), column(column) {}
};
struct BBNodeData {
    // ATSP distances
    std::vector<std::vector<int>> distances;

    // Partial paths already added to possible solution
    std::list<std::list<int>> partialPaths;

    // Index of 0 with highest penalty in distances
    EdgeCities highestZeroPenaltiesIndexes;

    // Highest penalties of 0 on both axis
    Penalties highestZeroPenalties;

    // Current lower bound
    int lowerBound;

    // Number of already added edges to the path (maximum = instanceSize)
    int edgesOnPath;

    BBNodeData() = default;

    BBNodeData(int instanceSize, int edgesOnPath) : distances(instanceSize, std::vector<int>(instanceSize)),
                                                    highestZeroPenaltiesIndexes(-1, -1) {
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

    static void bbCalculateLowerBoundAndDesignateHighestZeroPenalty(BBNodeData &nodeData);

    static void bbCreateLeftNodeData(BBNodeData &nodeData);

    static void bbCreateRightNodeData(BBNodeData &nodeData);

    static int bbGetCycleCost(BBNodeData &nodeData);
};


#endif //PEA_P1_TSPALGORITHMS_H
