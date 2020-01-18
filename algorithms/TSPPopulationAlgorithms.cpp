#include "TSPPopulationAlgorithms.h"
#include "../utilities/TSPUtils.h"
#include "../utilities/Random.h"


int TSPPopulationAlgorithms::geneticAlgorithm(const IGraph *tspInstance, const GeneticAlgorithmParameters &parameters,
                                              std::vector<int> &outSolution) {

    const int INSTANCE_SIZE = tspInstance->getVertexCount();

    TSelectionFunction performSelection = parameters.selectionFunction;

    std::vector<Specimen> population, selected, nextGeneration, elites;
    Specimen bestSpecimen;

    createRandomPopulation(tspInstance, parameters.populationSize, bestSpecimen, population);

    for (int generation = 0; generation < parameters.nGenerations; ++generation) {
        std::sort(population.begin(), population.end(),
                  [](const Specimen &s1, const Specimen &s2) { return s1 > s2; });

        performSelection(population, selected);

        // Save elites
        for (int eliteIdx = 0; eliteIdx < parameters.nElites; ++eliteIdx) {
            elites.emplace_back(population[eliteIdx]);
        }


        nextGeneration = selected; //Test
//        performCrossover(selected, parameters.crossoverProbability, nextGeneration, bestSolution, bestSolutionValue);
//        performMutation(nextGeneration, parameters.mutationProbability, bestSolution, bestSolutionValue);
        population = nextGeneration;

        // Apply elites
        std::sort(population.begin(), population.end(),
                  [](const Specimen &s1, const Specimen &s2) { return s1 > s2; });
        for (int eliteIdx = 0; eliteIdx < parameters.nElites; ++eliteIdx) {
            population[population.size() - 1 - eliteIdx] = elites[eliteIdx];
        }

        selected.clear();
        nextGeneration.clear();
        elites.clear();
    }

    outSolution = bestSpecimen.permutation;
    return bestSpecimen.targetFunctionValue;
}

void
TSPPopulationAlgorithms::createRandomPopulation(const IGraph *tspInstance, int populationSize, Specimen &outBestSpecimen,
                                                std::vector<Specimen> &outPopulation) {
    Specimen currentSpecimen;
    int bestSpecimenIdx = -1;

    for (int specimenIdx = 0; specimenIdx < populationSize; ++specimenIdx) {
        currentSpecimen.permutation.clear();
        currentSpecimen.targetFunctionValue = TSPGreedyAlgorithms::createRandomPermutation(tspInstance,
                                                                                           currentSpecimen.permutation);
        if (bestSpecimenIdx == -1 || currentSpecimen > outPopulation[bestSpecimenIdx]) {
            bestSpecimenIdx = specimenIdx;
        }
        outPopulation.emplace_back(currentSpecimen.permutation, currentSpecimen.targetFunctionValue);
    }

    outBestSpecimen = outPopulation[bestSpecimenIdx];
}

void TSPPopulationAlgorithms::rouletteSelection(const std::vector<Specimen> &population,
                                                std::vector<Specimen> &outSelected) {
    double fitnessSumOverPopulation = 0;
    // Holds edges of wheel chunks (cumulative values)
    std::vector<double> rouletteWheel(population.size(), 0);

    for (const Specimen &specimen : population) {
        fitnessSumOverPopulation += specimen.getFitness();
    }

    rouletteWheel[0] = population[0].getFitness() / fitnessSumOverPopulation;
    for (int specimenIdx = 1; specimenIdx < population.size() - 1; ++specimenIdx) {
        rouletteWheel[specimenIdx] = population[specimenIdx].getFitness() / fitnessSumOverPopulation;
        rouletteWheel[specimenIdx] += rouletteWheel[specimenIdx - 1];
    }
    rouletteWheel[population.size() - 1] = 1;

    double roulettePick;
    int specimenPickIdx;
    while (outSelected.size() != population.size()) {
        roulettePick = Random::getRealClosed(0, 1);
        for (specimenPickIdx = 0; roulettePick > rouletteWheel[specimenPickIdx]; ++specimenPickIdx) {}
        outSelected.emplace_back(population[specimenPickIdx]);
    }
}