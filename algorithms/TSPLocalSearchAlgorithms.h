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
#include "TSPHelperStructures.h"
#include "../utilities/Random.h"
#include "../structures/graphs/IGraph.h"

class TSPLocalSearchAlgorithms {

public:
    static int simulatedAnnealing(const IGraph *tspInstance, const LocalSearchParameters &parameters,
                                  std::vector<int> &outSolution);

private:
    [[nodiscard]] inline static double
    geometricCoolingScheme(double currentTemperature, double initialTemperature,
                           double multiplier, int currentIterationOrTime);

    [[nodiscard]] inline static std::vector<int> swapNeighbourhood(int i, int j, std::vector<int> currentSolution);

    [[nodiscard]] inline static int swapNeighbourhoodTFDifference(const IGraph *tspInstance, int i, int j,
                                                                  const std::vector<int> &currentSolution,
                                                                  const std::vector<int> &nextSolution,
                                                                  int currentSolutionValue);

    [[nodiscard]] inline static double sigmoidFunction(double x);

    using fCoolingScheme = decltype(&geometricCoolingScheme);
    using fNeighbourhood = decltype(&swapNeighbourhood);
    using fNeighbourhoodDiff = decltype(&swapNeighbourhoodTFDifference);

};


#endif //PEA_P1_TSPLOCALSEARCHALGORITHMS_H
