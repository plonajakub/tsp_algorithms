#ifndef PEA_P1_TSPGREEDYALGORITHMS_H
#define PEA_P1_TSPGREEDYALGORITHMS_H

#include "../utilities/TSPUtils.h"

// outSolution is a permutation of vertices (not cycle) - MUST be provided (as an argument) empty
class TSPGreedyAlgorithms {

public:
    static int nearestNeighbour(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int greedy(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int createNaturalPermutation(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int createRandomPermutation(const IGraph *tspInstance, std::vector<int> &outSolution);

    using fTSPAlgorithm = decltype(&nearestNeighbour);
};

#endif //PEA_P1_TSPGREEDYALGORITHMS_H
