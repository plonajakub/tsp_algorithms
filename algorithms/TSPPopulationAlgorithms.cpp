#include "TSPPopulationAlgorithms.h"
#include "../utilities/TSPUtils.h"
#include "../utilities/Random.h"


int TSPPopulationAlgorithms::geneticAlgorithm(const IGraph *tspInstance, const GeneticAlgorithmParameters &parameters,
                                              std::vector<int> &outSolution) {

    const int INSTANCE_SIZE = tspInstance->getVertexCount();

    if (INSTANCE_SIZE <= 2) {
        return TSPGreedyAlgorithms::createNaturalPermutation(tspInstance, outSolution);
    }

    TSelectionFunction performSelection = parameters.selectionFunction;
    TMutationCore mutationCore = parameters.mutationCoreFunction;
    TCrossoverCore crossoverCore = parameters.crossoverCoreFunction;

    std::vector<Specimen> population, selected, elites;
    Specimen bestSpecimen;

    createRandomPopulation(tspInstance, parameters.populationSize, bestSpecimen, population);

    for (int generation = 0; generation < parameters.nGenerations; ++generation) {
        // selection
        std::sort(population.begin(), population.end(),
                  [](const Specimen &s1, const Specimen &s2) { return s1 > s2; });
        performSelection(population, selected);

        // Save elites
        for (int eliteIdx = 0; eliteIdx < parameters.nElites; ++eliteIdx) {
            elites.emplace_back(population[eliteIdx]);
        }

        performCrossover(selected, parameters.crossoverProbability, crossoverCore);
        performMutation(selected, parameters.mutationProbability, mutationCore);
        population = selected;

        for (auto &specimen : population) {
            specimen.targetFunctionValue = TSPUtils::calculateTargetFunctionValue(tspInstance, specimen.permutation);
            if (specimen > bestSpecimen) {
                bestSpecimen = specimen;
            }
        }

        // Apply elites
        std::sort(selected.begin(), selected.end(),
                  [](const Specimen &s1, const Specimen &s2) { return s1 > s2; });
        for (int eliteIdx = 0; eliteIdx < parameters.nElites; ++eliteIdx) {
            selected[selected.size() - 1 - eliteIdx] = elites[eliteIdx];
        }

        selected.clear();
        elites.clear();
    }

    outSolution = bestSpecimen.permutation;
    return bestSpecimen.targetFunctionValue;
}

void
TSPPopulationAlgorithms::createRandomPopulation(const IGraph *tspInstance, int populationSize,
                                                Specimen &outBestSpecimen,
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

void
TSPPopulationAlgorithms::performMutation(std::vector<Specimen> &selected, double mutationProbability,
                                         TMutationCore mutationCore) {
    const int specimenLastPermIdx = selected.front().permutation.size() - 1;

    int i, j;
    for (auto &selectedSpecimen : selected) {
        if (Random::getRealClosed(0, 1) > mutationProbability) {
            continue;
        }
        i = Random::getInt(0, specimenLastPermIdx);
        j = Random::getInt(0, specimenLastPermIdx);
        if (i == j) {
            if (Random::getBool(true, 0.5)) {
                // Go upward if true
                if (j != specimenLastPermIdx) {
                    ++j;
                } else {
                    j = 0;
                }
            } else {
                // Go downward if false
                if (j != 0) {
                    --j;
                } else {
                    j = specimenLastPermIdx;
                }
            }
        }
        mutationCore(i, j, selectedSpecimen.permutation);
    }
}

// region Mutation cores

void TSPPopulationAlgorithms::transpositionCore(int i, int j, std::vector<int> &specimenPermutation) {
    std::swap(specimenPermutation[i], specimenPermutation[j]);
}

void TSPPopulationAlgorithms::insertionCore(int i, int j, std::vector<int> &specimenPermutation) {
    int elementToMove = specimenPermutation[j];
    specimenPermutation.erase(specimenPermutation.begin() + j);
    specimenPermutation.insert(specimenPermutation.begin() + i, elementToMove);
}

void TSPPopulationAlgorithms::inversionCore(int i, int j, std::vector<int> &specimenPermutation) {
    if (j < i) {
        std::swap(i, j);
    }

    for (int lIdx = i, rIdx = j; lIdx < rIdx; ++lIdx, --rIdx) {
        std::swap(specimenPermutation[lIdx], specimenPermutation[rIdx]);
    }
}

// endregion


void TSPPopulationAlgorithms::performCrossover(std::vector<Specimen> &selected, double crossoverProbability,
                                               TCrossoverCore crossoverCore) {
    const int selectedLastIdx = selected.size() - 1;

    for (int idx = 0; idx < selectedLastIdx; idx += 2) {
        if (Random::getRealClosed(0, 1) > crossoverProbability) {
            continue;
        }
        crossoverCore(selected[idx].permutation, selected[idx + 1].permutation);
    }

}

void TSPPopulationAlgorithms::OX(std::vector<int> &s1, std::vector<int> &s2) {

}