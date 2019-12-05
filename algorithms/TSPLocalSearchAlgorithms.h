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

class LocalSearchParameters;

class TSPLocalSearchAlgorithms {

public:
    static int simulatedAnnealing(const IGraph *tspInstance, const LocalSearchParameters &parameters,
                                  std::vector<int> &outSolution);

    using fLocalSearchAlgorithm = decltype(&simulatedAnnealing);

    [[nodiscard]] static double
    geometricCoolingScheme(double currentTemperature, double initialTemperature,
                           double multiplier, int currentIterationOrTime);

    [[nodiscard]] static std::vector<int> swapNeighbourhood(int i, int j, std::vector<int> currentSolution);

    [[nodiscard]] static int swapNeighbourhoodTFDifference(const IGraph *tspInstance, int i, int j,
                                                                  const std::vector<int> &currentSolution,
                                                                  const std::vector<int> &nextSolution,
                                                                  int currentSolutionValue);

    [[nodiscard]] static double sigmoidFunction(double x);

    using fCoolingScheme = decltype(&geometricCoolingScheme);
    using fNeighbourhood = decltype(&swapNeighbourhood);
    using fNeighbourhoodDiff = decltype(&swapNeighbourhoodTFDifference);

    friend class LocalSearchParameters;
};

#include "helper_structures/LocalSearchParameters.h"

#endif //PEA_P1_TSPLOCALSEARCHALGORITHMS_H