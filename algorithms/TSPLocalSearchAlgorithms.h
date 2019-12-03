#ifndef PEA_P1_TSPLOCALSEARCHALGORITHMS_H
#define PEA_P1_TSPLOCALSEARCHALGORITHMS_H

#include <map>
#include <vector>
#include <set>
#include <list>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <string>

#include "TSPGreedyAlgorithms.h"
#include "../utilities/Random.h"
#include "../structures/graphs/IGraph.h"

class TSPLocalSearchAlgorithms {

public:
    static int simulatedAnnealing(const IGraph *tspInstance, const std::map<std::string, std::string> &parameters,
                                  std::vector<int> &outSolution);

private:
    inline static void geometricCoolingScheme(double multiplier, double &temperature);

    inline static std::vector<int> swapNeighbourhood(int i, int j, std::vector<int> currentSolution);

    inline static int swapNeighbourhoodTFDifference(const IGraph *tspInstance, int i, int j,
                                                    const std::vector<int> &currentSolution,
                                                    const std::vector<int> &nextSolution,
                                                    int currentSolutionValue);

    inline static double sigmoidFunction(double x);
};


#endif //PEA_P1_TSPLOCALSEARCHALGORITHMS_H
