#ifndef PEA_P1_TSPALGORITHMSTEST_H
#define PEA_P1_TSPALGORITHMSTEST_H

#include <vector>

#include "../utilities/TSPUtils.h"
#include "../algorithms/TSPExactAlgorithms.h"
#include "../algorithms/TSPGreedyAlgorithms.h"
#include "../algorithms/TSPLocalSearchAlgorithms.h"
#include "../algorithms/helper_structures/LocalSearchParameters.h"


class TSPAlgorithmsTest {
public:
    void run() const;

private:

    //region Exact algorithms

    void bruteForceTest() const;
    void bruteForceTreeTest() const;
    void dynamicProgrammingHeldKarpTest() const;
    void branchAndBoundTest() const;

    //endregion

    //region Greedy algorithms

    void nearestNeighbourTest() const;
    void greedyTest() const;

    //endregion

    void simulatedAnnealingTest() const;

    // instanceFiles: map with paths to the instances in form {<directory of instances>, <vector with instance file names>}
    // first file name in the vector is a name of a solution file for instances in the directory
    void testExactOrGreedyAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                                    int (*tspAlgorithm)(const IGraph *, std::vector<int> &),
                                    bool isSolutionApproximated, const std::string &testName) const;

    void testLocalSearchAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                                    TSPLocalSearchAlgorithms::fLocalSearchAlgorithm fLocalSearchAlgorithm,
                                    const LocalSearchParameters &parameters, const std::string &testName) const;

    bool isSolutionValid(IGraph *tspInstance, const std::vector<int> &solutionPermutation,
                         int solutionPathCost) const;
};


#endif //PEA_P1_TSPALGORITHMSTEST_H
