#ifndef PEA_P1_TSPALGORITHMS_H
#define PEA_P1_TSPALGORITHMS_H

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <algorithm>

#include "../utilities/TSPUtils.h"
#include "TSPHelperStructures.h"


class TSPAlgorithms {

    // outSolution is a permutation of vertices (not cycle) - MUST be provided (as an argument) empty
public:
    static int bruteForce(const IGraph *tspInstance, std::vector<int> &outSolution);

    // DFS
    static int bruteForceTree(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int dynamicProgrammingHeldKarp(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int branchAndBound(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int nearestNeighbour(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int greedy(const IGraph *tspInstance, std::vector<int> &outSolution);

    // For tests
    static int branchAndBound0Heuristics(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int branchAndBoundNNHeuristic(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int branchAndBoundGHeuristic(const IGraph *tspInstance, std::vector<int> &outSolution);

    static int branchAndBound2Heuristics(const IGraph *tspInstance, std::vector<int> &outSolution);

private:

    static void
    bruteForceTreeRecursiveBuild(std::vector<int> &availableElements, std::vector<int> &usedElements,
                                 int &bestSolutionValue, const IGraph *tspInstance,
                                 std::vector<int> &solution);

    static int
    dpGetPartialPathCost(unsigned int partialPathSet, int endVertexIdx,
                         std::vector<std::vector<int>> &partialPathCostTable,
                         const IGraph *tspInstance);

    static void bbCalculateLowerBoundAndDesignateHighestZeroPenalties(BBNodeData &nodeData);

    static void
    bbDesignateHighestZeroPenalty(BBNodeData &nodeData, std::list<std::pair<EdgeCities, int>> &matrixZeroes);

    static void bbUpdateLeftNodeData(BBNodeData &nodeData);

    static void bbUpdateRightNodeData(BBNodeData &nodeData);

    static int bbCalculateUpperBoundFromNaturalPermutation(const IGraph *tspInstance, std::vector<int> &outSolution);

};


#endif //PEA_P1_TSPALGORITHMS_H
