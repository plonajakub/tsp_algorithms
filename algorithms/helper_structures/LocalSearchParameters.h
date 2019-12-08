#ifndef PEA_P1_LOCALSEARCHPARAMETERS_H
#define PEA_P1_LOCALSEARCHPARAMETERS_H

#include "../TSPGreedyAlgorithms.h"
#include "../TSPLocalSearchAlgorithms.h"

class LocalSearchParameters {

public:
    // Simulated annealing
    double initialTemperature;
    double coolingSchemeParameter;
    int epochIterationsNumber;
    int iterationsNumber;
    TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction;
    TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction;
    TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction;

    // Tabu search
//    int iterationsNumber;
    int tabuListSize;
    double cadenzaLengthParameter;
    int iterationsWithoutImprovementToRestart;
    int patternsNumberToCache;
//    TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction;
//    TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction;

    LocalSearchParameters() : initialTemperature(-1), coolingSchemeParameter(-1), epochIterationsNumber(-1),
                              iterationsNumber(-1), coolingSchemeFunction(nullptr), nextNeighbourFunction(nullptr),
                              initialSolutionFunction(nullptr), tabuListSize(-1), cadenzaLengthParameter(-1),
                              iterationsWithoutImprovementToRestart(-1), patternsNumberToCache(-1) {}

    // Simulated annealing
    LocalSearchParameters(double initialTemperature, double coolingSchemeParameter, int epochIterationsNumber,
                          int iterationsNumber, TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction,
                          TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction,
                          TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction)
            : initialTemperature(initialTemperature), coolingSchemeParameter(coolingSchemeParameter),
              epochIterationsNumber(epochIterationsNumber), iterationsNumber(iterationsNumber),
              coolingSchemeFunction(coolingSchemeFunction), nextNeighbourFunction(nextNeighbourFunction),
              initialSolutionFunction(initialSolutionFunction) {}

    // Tabu search
    LocalSearchParameters(int iterationsNumber, int tabuListSize, double cadenzaLengthParameter,
                          int iterationsWithoutImprovementToRestart, int patternsNumberToCache,
                          TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction,
                          TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction) :
            iterationsNumber(iterationsNumber), tabuListSize(tabuListSize),
            cadenzaLengthParameter(cadenzaLengthParameter),
            iterationsWithoutImprovementToRestart(iterationsWithoutImprovementToRestart),
            patternsNumberToCache(patternsNumberToCache), initialSolutionFunction(initialSolutionFunction),
            nextNeighbourFunction(nextNeighbourFunction) {}
};


#endif //PEA_P1_LOCALSEARCHPARAMETERS_H
