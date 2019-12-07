#ifndef PEA_P1_TSPUTILS_H
#define PEA_P1_TSPUTILS_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <list>

#include "../structures/DoublyLinkedList.h"
#include "../structures/Table.h"
#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/ListGraph.h"
#include "../algorithms/TSPExactAlgorithms.h"


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

    static int calculateTargetFunctionValue(const IGraph *tspInstance, const std::list<int> &vertexPermutation);

    static int calculateTargetFunctionValue(const IGraph *tspInstance, int fixedStartVertex,
                                            const std::vector<int> &vertexPermutation);

    static int calculateTargetFunctionValue(const IGraph *tspInstance, int fixedStartVertex,
                                            const std::list<int> &vertexPermutation);

    bool static isSolutionValid(IGraph *tspInstance, const std::vector<int> &solutionPermutation,
                         int solutionPathCost);

    bool static areSolutionsEqual(const std::vector<int> &solution1, const std::vector<int> &solution2);

private:

};

// Prints cycle (but takes permutation)
std::ostream& operator<<(std::ostream &ostr, std::vector<int> permutation);

#endif //PEA_P1_TSPUTILS_H
