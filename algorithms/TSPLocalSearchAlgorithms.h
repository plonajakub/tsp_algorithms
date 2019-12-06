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

    // initialTemperature > 0, parameter > 0
    [[nodiscard]] static double
    linearCoolingScheme(double currentTemperature, double initialTemperature,
                        double parameter, int currentIterationOrTime);

    // initialTemperature > 0, parameter in (0, 1)
    [[nodiscard]] static double
    geometricCoolingScheme(double currentTemperature, double initialTemperature,
                           double parameter, int currentIterationOrTime);

    // initialTemperature > 0, parameter > 0
    [[nodiscard]] static double
    logarithmicCoolingScheme(double currentTemperature, double initialTemperature,
                             double parameter, int currentIterationOrTime);

    [[nodiscard]] static std::vector<int> swapNeighbourhood(int i, int j, std::vector<int> currentSolution);

    [[nodiscard]] static std::vector<int> insertNeighbourhood(int i, int j, std::vector<int> currentSolution);

    [[nodiscard]] static std::vector<int> invertNeighbourhood(int i, int j, std::vector<int> currentSolution);

    [[nodiscard]] static int swapNeighbourhoodTFValue(const IGraph *tspInstance, int i, int j,
                                                      const std::vector<int> &currentSolution,
                                                      const std::vector<int> &nextSolution,
                                                      int currentSolutionValue);

    [[nodiscard]] static int insertNeighbourhoodTFValue(const IGraph *tspInstance, int i, int j,
                                                      const std::vector<int> &currentSolution,
                                                      const std::vector<int> &nextSolution,
                                                      int currentSolutionValue);

    [[nodiscard]] static int invertNeighbourhoodTFValue(const IGraph *tspInstance, int i, int j,
                                                        const std::vector<int> &currentSolution,
                                                        const std::vector<int> &nextSolution,
                                                        int currentSolutionValue);

    [[nodiscard]] static double sigmoidFunction(double x);

    using fCoolingScheme = decltype(&geometricCoolingScheme);
    using fNeighbourhood = decltype(&swapNeighbourhood);
    using fNeighbourhoodDiff = decltype(&swapNeighbourhoodTFValue);

    friend class LocalSearchParameters;
};

#include "helper_structures/LocalSearchParameters.h"

#endif //PEA_P1_TSPLOCALSEARCHALGORITHMS_H
