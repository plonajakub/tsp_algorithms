#ifndef PEA_P1_TSPUTILS_H
#define PEA_P1_TSPUTILS_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

#include "../structures/DoublyLinkedList.h"
#include "../structures/Table.h"
#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/ListGraph.h"
#include "../algorithms/TSPAlgorithms.h"


class TSPUtils {
public:

    enum TSPType {
        Symmetric, Asymmetric
    };

    static std::string
    loadTSPInstance(IGraph **pGraph, const std::string &path, TSPUtils::TSPType tspType = Asymmetric);

    // Returns map with entries {<instance file name>, <solution value>}
    static std::map<std::string, int> loadTSPSolutionValues(const std::string &file);

    static TSPType getTSPType(const std::string &path);

    static int calculateTargetFunctionValue(const IGraph *tspInstance, const DoublyLinkedList<int> &vertexPermutation);

    static int calculateTargetFunctionValue(const IGraph *tspInstance, const std::vector<int> &vertexPermutation);

    static int calculateTargetFunctionValue(const IGraph *tspInstance, int fixedStartVertex,
                                            const std::vector<int> &vertexPermutation);

    // instanceFiles: map with paths to the instances in form {<directory of instances>, <vector with instance file names>}
    // first file name in the vector is a name of a solution file for instances in the directory
    static void testAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                              int (*tspAlgorithm)(const IGraph *),
                              const std::string &testName);

    static void performTests();

    // Returns random value from [leftLimit, rightLimit) interval
    static int getRand(int leftLimit, int rightLimit);

private:

};


#endif //PEA_P1_TSPUTILS_H
