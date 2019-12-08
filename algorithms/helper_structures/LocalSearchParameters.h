#ifndef PEA_P1_LOCALSEARCHPARAMETERS_H
#define PEA_P1_LOCALSEARCHPARAMETERS_H

#include "../TSPGreedyAlgorithms.h"
#include "../TSPLocalSearchAlgorithms.h"

class LocalSearchParameters {

public:
    // simulated annealing
    double initialTemperature;
    double coolingSchemeParameter;
    int epochIterationsNumber;
    int iterationsNumber; // and tabu search
    TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction;
    TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction; // and tabu search
    TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction; // and tabu search

    // tabu search
    int tabuListSize;
    double cadenzaLengthParameter;
    int iterationsWithoutImprovementToRestart;
    int patternsNumberToCache;

    LocalSearchParameters() : initialTemperature(-1), coolingSchemeParameter(-1), epochIterationsNumber(-1),
                              iterationsNumber(-1), coolingSchemeFunction(nullptr), nextNeighbourFunction(nullptr),
                              initialSolutionFunction(nullptr), tabuListSize(-1), cadenzaLengthParameter(-1),
                              iterationsWithoutImprovementToRestart(-1), patternsNumberToCache(-1) {}

    LocalSearchParameters(double initialTemperature, double coolingSchemeParameter, int epochIterationsNumber,
                          int iterationsNumber, TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction,
                          TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction,
                          TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction)
            : initialTemperature(initialTemperature), coolingSchemeParameter(coolingSchemeParameter),
              epochIterationsNumber(epochIterationsNumber), iterationsNumber(iterationsNumber),
              coolingSchemeFunction(coolingSchemeFunction), nextNeighbourFunction(nextNeighbourFunction),
              initialSolutionFunction(initialSolutionFunction) {}
};


#endif //PEA_P1_LOCALSEARCHPARAMETERS_H
