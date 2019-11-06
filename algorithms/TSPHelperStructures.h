#ifndef PEA_P1_TSPHELPERSTRUCTURES_H
#define PEA_P1_TSPHELPERSTRUCTURES_H

#include <vector>
#include <list>

struct EdgeCities {
    int i;
    int j;

    EdgeCities() = default;

    EdgeCities(int i, int j) : i(i), j(j) {}
};

//region B&B

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
    std::vector<std::list<int>> partialPaths;

    // Number of already added edges to the path (maximum = instanceSize)
    int edgesOnPath;

    // Index of 0 with highest penalty in distances
    EdgeCities highestZeroPenaltiesIndexes;

    // Highest penalties of 0 on both axis
    Penalties highestZeroPenalties;

    // Current lower bound
    int lowerBound;

    BBNodeData() = default;

    BBNodeData(int instanceSize, int edgesOnPath) : distances(instanceSize, std::vector<int>(instanceSize)),
                                                    highestZeroPenaltiesIndexes(-1, -1) {
        lowerBound = 0;
        this->edgesOnPath = edgesOnPath;
    }
};

//endregion

#endif //PEA_P1_TSPHELPERSTRUCTURES_H
