#ifndef PEA_P1_TSPLOCALSEARCHALGORITHMS_H
#define PEA_P1_TSPLOCALSEARCHALGORITHMS_H

#include <map>
#include <vector>
#include <list>

#include "TSPGreedyAlgorithms.h"
#include "../structures/graphs/IGraph.h"

class TSPLocalSearchAlgorithms {

public:
    static int simulatedAnnealing(const IGraph *tspInstance, const std::map<std::string, std::string> &parameters,
                                  std::vector<int> &outSolution);

private:

};


#endif //PEA_P1_TSPLOCALSEARCHALGORITHMS_H
