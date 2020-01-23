#ifndef PEA_P1_GENETICALGORITHMPARAMETERS_H
#define PEA_P1_GENETICALGORITHMPARAMETERS_H

#include "../TSPPopulationAlgorithms.h"

class GeneticAlgorithmParameters {
public:
    int populationSize; // >= 2
    int nGenerations; // >= 1
    double crossoverProbability; // in [0, 1]
    double mutationProbability; // in [0, 1]
    int nElites; // [0, populationSize]

    TSPPopulationAlgorithms::TSelectionFunction selectionFunction;
    TSPPopulationAlgorithms::TMutationCore mutationCoreFunction;
    TSPPopulationAlgorithms::TCrossoverCore crossoverCoreFunction;
    TSPPopulationAlgorithms::TCreatePopulation createPopulationFunction;

    GeneticAlgorithmParameters() : populationSize(-1), nGenerations(-1), crossoverProbability(-1),
                                   mutationProbability(-1), nElites(-1), selectionFunction(nullptr),
                                   mutationCoreFunction(nullptr), crossoverCoreFunction(nullptr),
                                   createPopulationFunction(nullptr) {}
};


#endif //PEA_P1_GENETICALGORITHMPARAMETERS_H
