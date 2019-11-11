#ifndef PEA_P1_TSPHELPERSTRUCTURES_H
#define PEA_P1_TSPHELPERSTRUCTURES_H

#include <vector>
#include <list>

struct TSPEdge {
    int i;
    int j;
    int cost;

    TSPEdge() : i(-1), j(-1), cost(std::numeric_limits<int>::max()) {
    };

    TSPEdge(int i, int j, int cost) : i(i), j(j), cost(cost) {}
};

struct EdgeCities {
    int i;
    int j;

    EdgeCities() : i(-1), j(-1) {
    };

    EdgeCities(int i, int j) : i(i), j(j) {}
};

struct BBNodeData {
    // ATSP distances
    std::vector<std::vector<int>> distances;

    // Partial paths already added to possible solution
    std::vector<std::list<int>> partialPaths;

    // Number of already added edges to the path (maximum = instanceSize)
    int edgesOnPath;

    // True if the node can't be processed further, otherwise false
    bool isFinal;

    // Indexes of 0 with the highest penalty in distances
    EdgeCities highestZeroPenaltiesIndexes;

    // Highest penalty of 0
    int highestZeroPenalty;

    // Current lower bound
    int lowerBound;

    BBNodeData() { init(); }

    explicit BBNodeData(int instanceSize) : distances(instanceSize, std::vector<int>(instanceSize)) { init(); }

private:
    void init() {
        edgesOnPath = 0;
        isFinal = false;
        highestZeroPenalty = 0;
        lowerBound = 0;
    }
};


#endif //PEA_P1_TSPHELPERSTRUCTURES_H
