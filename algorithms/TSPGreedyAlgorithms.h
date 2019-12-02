#ifndef PEA_P1_TSPGREEDYALGORITHMS_H
#define PEA_P1_TSPGREEDYALGORITHMS_H


#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <algorithm>

#include "../utilities/TSPUtils.h"
#include "TSPHelperStructures.h"

// outSolution is a permutation of vertices (not cycle) - MUST be provided (as an argument) empty
class TSPGreedyAlgorithms {

public:
    static int nearestNeighbour(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int greedy(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int createNaturalPermutation(const IGraph *tspInstance, std::vector<int> &outSolution);
};


#endif //PEA_P1_TSPGREEDYALGORITHMS_H
