#include "TSPLocalSearchAlgorithms.h"


int TSPLocalSearchAlgorithms::simulatedAnnealing(const IGraph *tspInstance,
                                                 const std::map<std::string, std::string> &parameters,
                                                 std::vector<int> &outSolution) {
    const int INSTANCE_SIZE = tspInstance->getVertexCount();

    double temperature = std::stod(parameters.at("temperature"));
    double coolingSchemeMultiplier = std::stod(parameters.at("coolingSchemeMultiplier"));
    int epochIterationsCount = std::stoi(parameters.at("epochIterationsCount"));
    int currentEpochIteration = 0;
    int iterationsCount = std::stoi(parameters.at("iterationsCount"));
    int currentIteration = 0;
    std::vector<int> currentSolution, nextSolution, bestSolution;
    int currentSolutionValue, nextSolutionValue, bestSolutionValue;

    fCoolingScheme applyCoolingScheme = nullptr;
    TSPGreedyAlgorithms::fTSPAlgorithm startSolution = nullptr;
    fNeighbourhood getNextNeighbour = nullptr;
    fNeighbourhoodDiff applyTargetFunctionDifference = nullptr;

    if (parameters.at("applyCoolingScheme") == "geometricCoolingScheme") {
        applyCoolingScheme = geometricCoolingScheme;
    }

    if (parameters.at("startSolution") == "greedy") {
        startSolution = TSPGreedyAlgorithms::greedy;
    }

    if (parameters.at("getNextNeighbour") == "swapNeighbourhood") {
        getNextNeighbour = swapNeighbourhood;
        applyTargetFunctionDifference = swapNeighbourhoodTFDifference;
    }

    if (applyCoolingScheme == nullptr || startSolution == nullptr || getNextNeighbour == nullptr ||
        applyTargetFunctionDifference ==
        nullptr) {
        throw std::exception();
    }

    currentSolutionValue = startSolution(tspInstance, currentSolution);
    nextSolution = currentSolution;
    nextSolutionValue = currentSolutionValue;
    bestSolution = currentSolution;
    bestSolutionValue = currentSolutionValue;
    int i, j;
    while (currentIteration < iterationsCount) {
        while (currentEpochIteration < epochIterationsCount) {
            i = Random::getInt(0, INSTANCE_SIZE - 1);
            j = Random::getInt(0, INSTANCE_SIZE - 1);
            if (i == j) {
                if (Random::getBool(true, 0.5)) {
                    // Go upward if true
                    if (j != INSTANCE_SIZE - 1) {
                        ++j;
                    } else {
                        j = 0;
                    }
                } else {
                    // Go downward if false
                    if (j != 0) {
                        --j;
                    } else {
                        j = INSTANCE_SIZE - 1;
                    }
                }
            }

            nextSolution = getNextNeighbour(i, j, currentSolution);
            nextSolutionValue = applyTargetFunctionDifference(tspInstance, i, j, currentSolution, nextSolution,
                                                              currentSolutionValue);

            if (Random::getRealClosed(0.0, 1.0) <=
                sigmoidFunction(currentSolutionValue - nextSolutionValue) / temperature) {
                currentSolution = nextSolution;
                currentSolutionValue = nextSolutionValue;
            }
            if (nextSolutionValue < bestSolutionValue) {
                bestSolutionValue = nextSolutionValue;
                bestSolution = nextSolution;
            }
            ++currentEpochIteration;
        }
        ++currentIteration;
        temperature = applyCoolingScheme(coolingSchemeMultiplier, temperature, currentEpochIteration);
    }
    outSolution = bestSolution;
    return bestSolutionValue;
}


double TSPLocalSearchAlgorithms::geometricCoolingScheme(double temperature, double multiplier, int iterationOrTime) {
    return temperature * multiplier;
}


std::vector<int> TSPLocalSearchAlgorithms::swapNeighbourhood(int i, int j, std::vector<int> currentSolution) {
    std::swap(currentSolution[i], currentSolution[j]);
    return currentSolution;
}


int TSPLocalSearchAlgorithms::swapNeighbourhoodTFDifference(const IGraph *tspInstance, int i, int j,
                                                            const std::vector<int> &currentSolution,
                                                            const std::vector<int> &nextSolution,
                                                            int currentSolutionValue) {
    const int lastVertexIdx = tspInstance->getVertexCount() - 1;
    if (j < i) {
        std::swap(i, j);
    }

    int iLeft;
    if (i == 0) {
        iLeft = lastVertexIdx;
    } else {
        iLeft = i - 1;
    }

    int iRight;
    if (i == lastVertexIdx) {
        iRight = 0;
    } else {
        iRight = i + 1;
    }

    int jLeft;
    if (j == 0) {
        jLeft = lastVertexIdx;
    } else {
        jLeft = j - 1;
    }

    int jRight;
    if (j == lastVertexIdx) {
        jRight = 0;
    } else {
        jRight = j + 1;
    }

    std::set<std::pair<int, int>> edges;
    edges.emplace(iLeft, i);
    edges.emplace(i, iRight);
    edges.emplace(jLeft, j);
    edges.emplace(j, jRight);

    for (const auto &edge : edges) {
        currentSolutionValue -= tspInstance->getEdgeParameter(currentSolution[edge.first],
                                                              currentSolution[edge.second]);
        currentSolutionValue += tspInstance->getEdgeParameter(nextSolution[edge.first],
                                                              nextSolution[edge.second]);
    }
    return currentSolutionValue;
}

double TSPLocalSearchAlgorithms::sigmoidFunction(double x) {
    return 1.0 / (1.0 + exp(-x));
}
