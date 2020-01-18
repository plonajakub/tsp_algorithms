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

    using TSelectionFunction = void (*)(std::vector<Specimen> &population, std::vector<Specimen> &selected);

    void rouletteSelection(const std::vector<Specimen> &population, std::vector<Specimen> &outSelected);


private:

    static void
    createRandomPopulation(const IGraph *tspInstance, int populationSize, Specimen &bestSpecimen,
                           std::vector<Specimen> &outPopulation);

};

#include "helper_structures/GeneticAlgorithmParameters.h"

#endif //PEA_P1_TSPPOPULATIONALGORITHMS_H
