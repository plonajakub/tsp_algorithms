#ifndef PEA_P1_GENETICALGORITHMPARAMETERS_H
#define PEA_P1_GENETICALGORITHMPARAMETERS_H

class GeneticAlgorithmParameters {
public:
    int populationSize; // >= 2
    int nGenerations; // >= 1
    int crossoverProbability; // in [0, 1]
    int mutationProbability; // in [0, 1]

    TSPPopulationAlgorithms::TSelectionFunction selectionFunction;
};


#endif //PEA_P1_GENETICALGORITHMPARAMETERS_H
