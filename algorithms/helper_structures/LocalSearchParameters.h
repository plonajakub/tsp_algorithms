#ifndef PEA_P1_LOCALSEARCHPARAMETERS_H
#define PEA_P1_LOCALSEARCHPARAMETERS_H

#include "../TSPGreedyAlgorithms.h"
#include "../TSPLocalSearchAlgorithms.h"

class LocalSearchParameters {

public:
    enum class SAParameters {
        INITIAL_TEMPERATURE,
        COOLING_SCHEME_PARAMETER,
        EPOCH_ITERATIONS_NUMBER,
        ITERATIONS_NUMBER
    };
    // Simulated annealing
    double initialTemperature; // > 0
    double coolingSchemeParameter; // > 0, for geometricCoolingScheme also < 1
    int epochIterationsNumber; // > 0
    int iterationsNumber; // > 0
    TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction;
    TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction;
    TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction;

    enum class TSParameter {
        ITERATIONS_NUMBER,
        TABU_LIST_SIZE,
        CADENZA_LENGTH_PARAMETER,
        ITERATIONS_WITHOUT_IMPROVEMENT_TO_RESTART,
        PATTERNS_NUMBER_TO_CACHE
    };
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
        initialSolutionFunction = TSPGreedyAlgorithms::createNaturalPermutation;
    }

    void setTabuSearchDefaultParameters() {
        iterationsNumber = 100;
        tabuListSize = 50;
        cadenzaLengthParameter = 1.0 / 8;
        iterationsWithoutImprovementToRestart = 50;
        patternsNumberToCache = 2;
        initialSolutionFunction = TSPGreedyAlgorithms::createNaturalPermutation;
        nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
    }

    void setSimulatedAnnealingBestParameters() {
        initialTemperature = 2000;
        coolingSchemeParameter = 15;
        epochIterationsNumber = 1000;
        iterationsNumber = 500;
        coolingSchemeFunction = TSPLocalSearchAlgorithms::logarithmicCoolingScheme;
        nextNeighbourFunction = TSPLocalSearchAlgorithms::insertNeighbourhood;
        initialSolutionFunction = TSPGreedyAlgorithms::greedy;
    }
};


#endif //PEA_P1_LOCALSEARCHPARAMETERS_H
