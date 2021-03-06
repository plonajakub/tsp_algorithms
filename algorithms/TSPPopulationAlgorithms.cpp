#include "TSPPopulationAlgorithms.h"
#include "../utilities/TSPUtils.h"
#include "../utilities/Random.h"
#include "helper_structures/LocalSearchParameters.h"


int TSPPopulationAlgorithms::geneticAlgorithm(const IGraph *tspInstance, const GeneticAlgorithmParameters &parameters,
                                              std::vector<int> &outSolution) {

    const int INSTANCE_SIZE = tspInstance->getVertexCount();

    if (INSTANCE_SIZE <= 2) {
        return TSPGreedyAlgorithms::createNaturalPermutation(tspInstance, outSolution);
    }

    if (parameters.populationSize < 2
        || parameters.nGenerations < 1
        || parameters.crossoverProbability < 0 || parameters.crossoverProbability > 1
        || parameters.mutationProbability < 0 || parameters.mutationProbability > 1
        || parameters.nElites < 0
        || parameters.tournamentSize < 1) {
        throw std::invalid_argument("Algorithm supplied with invalid numeric parameter(s)");
    }
    if (parameters.selectionFunction != TSPPopulationAlgorithms::rouletteSelection
        && parameters.selectionFunction != TSPPopulationAlgorithms::tournamentSelection) {
        throw std::invalid_argument("Algorithm supplied with invalid selection function");
    }
    if (parameters.mutationCoreFunction != TSPPopulationAlgorithms::inversionCore
        && parameters.mutationCoreFunction != TSPPopulationAlgorithms::insertionCore
        && parameters.mutationCoreFunction != TSPPopulationAlgorithms::transpositionCore) {
        throw std::invalid_argument("Algorithm supplied with invalid mutation core function");
    }
    if (parameters.crossoverCoreFunction != TSPPopulationAlgorithms::OX) {
        throw std::invalid_argument("Algorithm supplied with invalid crossover core function");
    }
    if (parameters.createPopulationFunction != TSPPopulationAlgorithms::createRandomPopulation
        && parameters.createPopulationFunction != TSPPopulationAlgorithms::createPopulationWithSA) {
        throw std::invalid_argument("Algorithm supplied with invalid population creation function");
    }

    TSelectionFunction performSelection = parameters.selectionFunction;
    TMutationCore mutationCore = parameters.mutationCoreFunction;
    TCrossoverCore crossoverCore = parameters.crossoverCoreFunction;
    TCreatePopulation createPopulation = parameters.createPopulationFunction;

    const int nElites = std::min(parameters.nElites, parameters.populationSize);
    const int nTournamentParticipants = std::min(parameters.tournamentSize, parameters.populationSize);

    std::vector<Specimen> population, selected, elites;
    Specimen bestSpecimen;

    createPopulation(tspInstance, parameters.populationSize, bestSpecimen, population);

    for (int generation = 0; generation < parameters.nGenerations; ++generation) {
        if (performSelection == TSPPopulationAlgorithms::tournamentSelection) {
            performSelection(population, selected, nTournamentParticipants);
        } else {
            performSelection(population, selected, -1);
        }

        // Save elites
        std::sort(population.begin(), population.end(),
                  [](const Specimen &s1, const Specimen &s2) { return s1 > s2; });
        for (int eliteIdx = 0; eliteIdx < nElites; ++eliteIdx) {
            elites.emplace_back(population[eliteIdx]);
        }


        performCrossover(selected, parameters.crossoverProbability, crossoverCore);
//        for (auto &specimen : selected) {
//            specimen.targetFunctionValue = TSPUtils::calculateTargetFunctionValue(tspInstance, specimen.permutation);
//            if (specimen > bestSpecimen) {
//                bestSpecimen = specimen;
//            }
//        }

        performMutation(selected, parameters.mutationProbability, mutationCore);

        for (auto &specimen : selected) {
            specimen.targetFunctionValue = TSPUtils::calculateTargetFunctionValue(tspInstance, specimen.permutation);
            if (specimen > bestSpecimen) {
                bestSpecimen = specimen;
            }
        }

        population = selected;

        // Apply elites
        std::sort(population.begin(), population.end(),
                  [](const Specimen &s1, const Specimen &s2) { return s1 > s2; });
        for (int eliteIdx = 0; eliteIdx < nElites; ++eliteIdx) {
            population[population.size() - 1 - eliteIdx] = elites[eliteIdx];
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

void
TSPPopulationAlgorithms::createPopulationWithSA(const IGraph *tspInstance, int populationSize,
                                                Specimen &outBestSpecimen,
                                                std::vector<Specimen> &outPopulation) {
    Specimen currentSpecimen;
    LocalSearchParameters lsp;
    lsp.setSimulatedAnnealingBestParameters();
    lsp.iterationsNumber = 50;
    int bestSpecimenIdx = -1;
    for (int specimenIdx = 0; specimenIdx < populationSize; ++specimenIdx) {
        currentSpecimen.permutation.clear();
        currentSpecimen.targetFunctionValue = TSPLocalSearchAlgorithms::simulatedAnnealing(tspInstance, lsp,
                                                                                           currentSpecimen.permutation);
        if (bestSpecimenIdx == -1 || currentSpecimen > outPopulation[bestSpecimenIdx]) {
            bestSpecimenIdx = specimenIdx;
        }
        outPopulation.emplace_back(currentSpecimen.permutation, currentSpecimen.targetFunctionValue);
    }
    outBestSpecimen = outPopulation[bestSpecimenIdx];
}

void TSPPopulationAlgorithms::rouletteSelection(const std::vector<Specimen> &population,
                                                std::vector<Specimen> &outSelected, int parameter) {
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

void TSPPopulationAlgorithms::tournamentSelection(const std::vector<Specimen> &population,
                                                  std::vector<Specimen> &outSelected, int nTournamentParticipants) {
    std::vector<int> specimenInPopIdxs(population.size());
    for (int i = 0; i < population.size(); ++i) {
        specimenInPopIdxs[i] = i;
    }
    std::vector<int> tournamentRound(nTournamentParticipants);

    int randIdx, bestSpecimenIdx;
    while (outSelected.size() != population.size()) {
        for (int &participant : tournamentRound) {
            randIdx = Random::getInt(0, specimenInPopIdxs.size() - 1);
            participant = specimenInPopIdxs[randIdx];
            specimenInPopIdxs.erase(specimenInPopIdxs.begin() + randIdx);
        }
        bestSpecimenIdx = tournamentRound[0];
        for (int k = 1; k < tournamentRound.size(); ++k) {
            if (population[tournamentRound[k]] > population[bestSpecimenIdx]) {
                bestSpecimenIdx = tournamentRound[k];
            }
        }
        outSelected.emplace_back(population[bestSpecimenIdx]);
        specimenInPopIdxs.insert(specimenInPopIdxs.end(), tournamentRound.begin(), tournamentRound.end());
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
    const int specimenSize = s1.size();

    int leftLimit = Random::getInt(0, specimenSize - 1);
    int rightLimit = Random::getInt(0, specimenSize - 1);
    while (rightLimit == leftLimit) {
        rightLimit = Random::getInt(0, specimenSize - 1);
    }
    if (rightLimit < leftLimit) {
        std::swap(rightLimit, leftLimit);
    }

    std::list<int> c1, c2;
    for (int idx = leftLimit; idx <= rightLimit; ++idx) {
        c1.push_back(s2[idx]);
        c2.push_back(s1[idx]);
    }

    int idx;
    std::list<int> appendToC1, appendToC2;
    for (int offset = 1; offset <= specimenSize; ++offset) {
        idx = (rightLimit + offset) % specimenSize;

        if (std::find(c1.begin(), c1.end(), s1[idx]) == c1.end()) {
            appendToC1.emplace_back(s1[idx]);
        }

        if (std::find(c2.begin(), c2.end(), s2[idx]) == c2.end()) {
            appendToC2.emplace_back(s2[idx]);
        }
    }
    c1.splice(c1.end(), appendToC1);
    c2.splice(c2.end(), appendToC2);

    for (int i = 0; i < leftLimit; ++i) {
        std::rotate(c1.rbegin(), std::next(c1.rbegin()), c1.rend());
        std::rotate(c2.rbegin(), std::next(c2.rbegin()), c2.rend());
    }

    s1 = std::vector<int>(c1.begin(), c1.end());
    s2 = std::vector<int>(c2.begin(), c2.end());
}