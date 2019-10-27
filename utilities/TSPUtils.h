#ifndef PEA_P1_TSPUTILS_H
#define PEA_P1_TSPUTILS_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

#include "../structures/DoublyLinkedList.h"
#include "../structures/Table.h"
#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/ListGraph.h"


class TSPUtils {
public:

    enum TSPType {
        Symmetric, Asymmetric
    };

    static std::string loadTSPInstance(IGraph **pGraph, const std::string &path, TSPUtils::TSPType tspType = Asymmetric);

    static TSPType getTSPType(const std::string &path);

    static int calculateTargetFunctionValue(const IGraph *tspInstance, const DoublyLinkedList<int> &vertexPermutation);

    static int calculateTargetFunctionValue(const IGraph *tspInstance, const std::vector<int> &vertexPermutation);

    static int calculateTargetFunctionValue(const IGraph *tspInstance, int fixedStartVertex, const std::vector<int> &vertexPermutation);

    // Returns random value from [leftLimit, rightLimit) interval
    static int getRand(int leftLimit, int rightLimit);

private:

};


#endif //PEA_P1_TSPUTILS_H
