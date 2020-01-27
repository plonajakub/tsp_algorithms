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
    int tournamentSize; // [1, populationSize]

    enum class GAParameters {
        PopulationSize, NGenerations, CrossoverProbability, MutationProbability, NElites, TournamentSize
    };

    TSPPopulationAlgorithms::TSelectionFunction selectionFunction;
    TSPPopulationAlgorithms::TMutationCore mutationCoreFunction;
    TSPPopulationAlgorithms::TCrossoverCore crossoverCoreFunction;
    TSPPopulationAlgorithms::TCreatePopulation createPopulationFunction;

    GeneticAlgorithmParameters() : populationSize(-1), nGenerations(-1), crossoverProbability(-1),
                                   mutationProbability(-1), nElites(-1), tournamentSize(-1),
                                   selectionFunction(nullptr), mutationCoreFunction(nullptr),
                                   crossoverCoreFunction(nullptr), createPopulationFunction(nullptr) {}

    void setDefaultParameters() {
        populationSize = 50;
        nGenerations = 1000;
        crossoverProbability = 0.9;
        mutationProbability = 0.1;
        nElites = 10;
        tournamentSize = 5;
        createPopulationFunction = TSPPopulationAlgorithms::createRandomPopulation;
        selectionFunction = TSPPopulationAlgorithms::rouletteSelection;
        crossoverCoreFunction = TSPPopulationAlgorithms::OX;
        mutationCoreFunction = TSPPopulationAlgorithms::insertionCore;
    }

    void setBestParameters() {
        populationSize = 50;
        nGenerations = 2000;
        crossoverProbability = 1.0;
        mutationProbability = 0.12;
        nElites = 12;
        tournamentSize = 1;
        createPopulationFunction = TSPPopulationAlgorithms::createRandomPopulation;
        selectionFunction = TSPPopulationAlgorithms::rouletteSelection;
        crossoverCoreFunction = TSPPopulationAlgorithms::OX;
        mutationCoreFunction = TSPPopulationAlgorithms::insertionCore;
    }
};


#endif //PEA_P1_GENETICALGORITHMPARAMETERS_H
