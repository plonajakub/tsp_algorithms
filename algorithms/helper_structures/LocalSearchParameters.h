#ifndef PEA_P1_LOCALSEARCHPARAMETERS_H
#define PEA_P1_LOCALSEARCHPARAMETERS_H

#include "../TSPGreedyAlgorithms.h"
#include "../TSPLocalSearchAlgorithms.h"

class LocalSearchParameters {

public:
    double initialTemperature;
    double coolingSchemeMultiplier;
    int epochIterationsNumber;
    int iterationsNumber;
    TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction;
    TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction;
    TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction;

    LocalSearchParameters() : initialTemperature(-1), coolingSchemeMultiplier(-1), epochIterationsNumber(-1),
                              iterationsNumber(-1), coolingSchemeFunction(nullptr), nextNeighbourFunction(nullptr),
                              initialSolutionFunction(nullptr) {}

    LocalSearchParameters(double initialTemperature, double coolingSchemeMultiplier, int epochIterationsNumber,
                          int iterationsNumber, TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction,
                          TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction,
                          TSPGreedyAlgorithms::fTSPAlgorithm initialSolutionFunction)
            : initialTemperature(initialTemperature), coolingSchemeMultiplier(coolingSchemeMultiplier),
              epochIterationsNumber(epochIterationsNumber), iterationsNumber(iterationsNumber),
              coolingSchemeFunction(coolingSchemeFunction), nextNeighbourFunction(nextNeighbourFunction),
              initialSolutionFunction(initialSolutionFunction) {}
};


#endif //PEA_P1_LOCALSEARCHPARAMETERS_H
