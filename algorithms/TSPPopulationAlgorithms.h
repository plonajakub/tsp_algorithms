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

    using TPopulation = std::list<Specimen>;
    using TSelectionFunction = void (*)(TPopulation &population, TPopulation &outSelected,
                                        TPopulation &outNotSelected);

    void rouletteSelection(TPopulation &population, TPopulation &outSelected, TPopulation &outNotSelected);


private:

    static void
    createRandomPopulation(const IGraph *tspInstance, int populationSize,
                           std::vector<int> &outBestSolution, int &outBestSolutionValue,
                           TPopulation &outPopulation);

};

#include "helper_structures/GeneticAlgorithmParameters.h"

#endif //PEA_P1_TSPPOPULATIONALGORITHMS_H
