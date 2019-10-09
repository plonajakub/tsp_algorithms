#ifndef PEA_P1_GRAPHUTILS_H
#define PEA_P1_GRAPHUTILS_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "../structures/DoublyLinkedList.h"
#include "../structures/Table.h"
#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/ListGraph.h"


class GraphUtils {
public:

    enum TSPType {
        Symmetric, Asymmetric
    };

    static std::string loadTSPInstance(IGraph **pGraph, TSPType tspType, const std::string &path);

    static TSPType getTSPType(const std::string &path);

    static int getTargetFunctionValue(const IGraph *tspInstance, const DoublyLinkedList<int> &vertexPermutation);

    // Returns random value from [leftLimit, rightLimit) interval
    static int getRand(int leftLimit, int rightLimit);

private:

};


#endif //PEA_P1_GRAPHUTILS_H
