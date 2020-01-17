#include "TSPPopulationAlgorithms.h"
#include "../utilities/TSPUtils.h"
#include "../utilities/Random.h"
#include <list>


int TSPPopulationAlgorithms::geneticAlgorithm(const IGraph *tspInstance, const GeneticAlgorithmParameters &parameters,
                                              std::vector<int> &outSolution) {

    const int INSTANCE_SIZE = tspInstance->getVertexCount();

    TSelectionFunction performSelection = parameters.selectionFunction;

    TPopulation population;
    TPopulation selected, notSelected;
    TPopulation newGeneration;
    TPopulation elite;
    std::vector<int> bestSolution;
    int bestSolutionValue = std::numeric_limits<int>::max();

    createRandomPopulation(tspInstance, parameters.populationSize, bestSolution, bestSolutionValue, population);

    for (int generation = 0; generation < parameters.nGenerations; ++generation) {
        performSelection(population, selected, notSelected);
//        selectElite(population, elite);
//        performCrossover(selected, parameters.crossoverProbability, newGeneration, bestSolution, bestSolutionValue);
//        performMutation(newGeneration, parameters.mutationProbability, bestSolution, bestSolutionValue);
//        mergeNextGeneration(newGeneration, notSelected, elite, parameters.populationSize, population);
    }

    outSolution = bestSolution;
    return bestSolutionValue;
}

void
TSPPopulationAlgorithms::createRandomPopulation(const IGraph *tspInstance, int populationSize,
                                                std::vector<int> &outBestSolution, int &outBestSolutionValue,
                                                TPopulation &outPopulation) {
    outPopulation.clear();

    std::vector<int> solution;
    int solutionTargetFunctionValue;

    for (int specimenIdx = 0; specimenIdx < populationSize; ++specimenIdx) {
        solution.clear();
        solutionTargetFunctionValue = TSPGreedyAlgorithms::createRandomPermutation(tspInstance, solution);
        if (solutionTargetFunctionValue < outBestSolutionValue) {
            outBestSolution = solution;
            outBestSolutionValue = solutionTargetFunctionValue;
        }
        outPopulation.emplace_back(solution, solutionTargetFunctionValue);
    }
}

void TSPPopulationAlgorithms::rouletteSelection(TSPPopulationAlgorithms::TPopulation &population,
                                                TSPPopulationAlgorithms::TPopulation &outSelected,
                                                TSPPopulationAlgorithms::TPopulation &outNotSelected) {
    outSelected.clear();
    outNotSelected.clear();

    double fitnessFunctionSum = 0.0;
    for (const auto &specimen : population) {
        fitnessFunctionSum += specimen.getFitness();
    }

    population.sort(
            [](const Specimen &s1, const Specimen &s2) { return s1.getFitness() < s2.targetFunctionValue; });

    for (const auto &specimen : population) {
        if (Random::getRealClosed(0, 1) <= specimen.getFitness() / fitnessFunctionSum) {
            outSelected.emplace_back(specimen);
        } else {
            outNotSelected.emplace_back(specimen);
        }
    }

}