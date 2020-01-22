#ifndef PEA_P1_TSPPOPULATIONALGORITHMS_H
#define PEA_P1_TSPPOPULATIONALGORITHMS_H


#include <vector>
#include <list>
#include "../structures/graphs/IGraph.h"
#include "helper_structures/Specimen.h"


class GeneticAlgorithmParameters;

class TSPPopulationAlgorithms {

public:
    static int geneticAlgorithm(const IGraph *tspInstance, const GeneticAlgorithmParameters &parameters,
                                std::vector<int> &outSolution);

    using TSelectionFunction = void (*)(const std::vector<Specimen> &population, std::vector<Specimen> &selected);
    using TMutationCore = void (*)(int i, int j, std::vector<int> &specimenPermutation);
    using TCrossoverCore = void (*)(std::vector<int> &s1, std::vector<int> &s2);

    static void rouletteSelection(const std::vector<Specimen> &population, std::vector<Specimen> &outSelected);

    static void tournamentSelection(const std::vector<Specimen> &population, std::vector<Specimen> &outSelected);

    static void inversionCore(int i, int j, std::vector<int> &specimenPermutation);

    static void insertionCore(int i, int j, std::vector<int> &specimenPermutation);

    static void transpositionCore(int i, int j, std::vector<int> &specimenPermutation);

    static void OX(std::vector<int> &s1, std::vector<int> &s2);

private:

    static void
    createRandomPopulation(const IGraph *tspInstance, int populationSize, Specimen &outBestSpecimen,
                           std::vector<Specimen> &outPopulation);

    static void performMutation(std::vector<Specimen> &selected, double mutationProbability,
                                TMutationCore mutationCore);

    static void performCrossover(std::vector<Specimen> &selected, double crossoverProbability,
                                 TCrossoverCore crossoverCore);


};

#include "helper_structures/GeneticAlgorithmParameters.h"

#endif //PEA_P1_TSPPOPULATIONALGORITHMS_H
