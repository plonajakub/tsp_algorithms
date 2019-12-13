#ifndef PEA_P1_LOCALSEARCHPARAMETERS_H
#define PEA_P1_LOCALSEARCHPARAMETERS_H

#include "../TSPGreedyAlgorithms.h"
#include "../TSPLocalSearchAlgorithms.h"

class LocalSearchParameters {

public:
    // Simulated annealing
    double initialTemperature; // > 0
    double coolingSchemeParameter; // > 0, for geometricCoolingScheme also < 1
    int epochIterationsNumber; // > 0
    int iterationsNumber; // > 0
    TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction;
    TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction;
    TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction;

    // Tabu search
//    int iterationsNumber; // > 0
    int tabuListSize; // > 0
    double cadenzaLengthParameter; // > 0
    int iterationsWithoutImprovementToRestart; // > 0
    int patternsNumberToCache; // > 0
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

    void setSimulatedAnnealingDefaultParameters() {
        initialTemperature = 1000;
        coolingSchemeParameter = 0.95;
        epochIterationsNumber = 500;
        iterationsNumber = 1000;
        coolingSchemeFunction = TSPLocalSearchAlgorithms::geometricCoolingScheme;
        nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
        initialSolutionFunction = TSPGreedyAlgorithms::nearestNeighbour;
    }
};


#endif //PEA_P1_LOCALSEARCHPARAMETERS_H
