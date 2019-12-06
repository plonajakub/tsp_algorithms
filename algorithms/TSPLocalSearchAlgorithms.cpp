#include "TSPLocalSearchAlgorithms.h"


int TSPLocalSearchAlgorithms::simulatedAnnealing(const IGraph *tspInstance,
                                                 const LocalSearchParameters &parameters,
                                                 std::vector<int> &outSolution) {
    const int instanceSize = tspInstance->getVertexCount();

    if (instanceSize <= 2) {
        return TSPGreedyAlgorithms::createNaturalPermutation(tspInstance, outSolution);
    }

    double currentTemperature = parameters.initialTemperature;
    int currentEpochIterationIdx = 0;
    int currentIterationIdx = 0;

    fCoolingScheme getNextTemperature = parameters.coolingSchemeFunction;
    TSPGreedyAlgorithms::fTSPAlgorithm designateInitialSolution = parameters.initialSolutionFunction;
    fNeighbourhood getNextNeighbour = parameters.nextNeighbourFunction;
    fNeighbourhoodDiff calculateNextSolutionTargetFunctionValue = nullptr;
    if (getNextNeighbour == swapNeighbourhood) {
        calculateNextSolutionTargetFunctionValue = swapNeighbourhoodTFValue;
    } // 2 more to come

    std::vector<int> currentSolution, nextSolution, bestSolution;
    int currentSolutionValue, nextSolutionValue, bestSolutionValue;
    currentSolutionValue = designateInitialSolution(tspInstance, currentSolution);

    bestSolution = currentSolution;
    bestSolutionValue = currentSolutionValue;

    int i, j;
    while (currentIterationIdx < parameters.iterationsNumber) {
        while (currentEpochIterationIdx < parameters.epochIterationsNumber) {
            i = Random::getInt(0, instanceSize - 1);
            j = Random::getInt(0, instanceSize - 1);
            if (i == j) {
                if (Random::getBool(true, 0.5)) {
                    // Go upward if true
                    if (j != instanceSize - 1) {
                        ++j;
                    } else {
                        j = 0;
                    }
                } else {
                    // Go downward if false
                    if (j != 0) {
                        --j;
                    } else {
                        j = instanceSize - 1;
                    }
                }
            }

            nextSolution = getNextNeighbour(i, j, currentSolution);
            nextSolutionValue = calculateNextSolutionTargetFunctionValue(tspInstance, i, j, currentSolution,
                                                                         nextSolution,
                                                                         currentSolutionValue);
            // Core of the algorithm
            if (Random::getRealClosed(0.0, 1.0) <=
                sigmoidFunction(currentSolutionValue - nextSolutionValue) / currentTemperature) {
                currentSolution = nextSolution;
                currentSolutionValue = nextSolutionValue;
            }
            if (nextSolutionValue < bestSolutionValue) {
                bestSolutionValue = nextSolutionValue;
                bestSolution = nextSolution;
            }
            ++currentEpochIterationIdx;
        }
        currentTemperature = getNextTemperature(currentTemperature, parameters.initialTemperature,
                                                parameters.coolingSchemeParameter, currentIterationIdx);
        ++currentIterationIdx;
    }
    outSolution = bestSolution;
    return bestSolutionValue;
}


double
TSPLocalSearchAlgorithms::linearCoolingScheme(double currentTemperature, double initialTemperature, double parameter,
                                              int currentIterationOrTime) {
    double nextTemperature = currentTemperature - parameter;
    return ((nextTemperature > 0) ? nextTemperature : std::nextafter(0, std::numeric_limits<double>::max()));
}


double TSPLocalSearchAlgorithms::geometricCoolingScheme(double currentTemperature, double initialTemperature,
                                                        double parameter, int currentIterationOrTime) {
    double nextTemperature = currentTemperature * parameter;
    return ((nextTemperature > 0) ? nextTemperature : std::nextafter(0, std::numeric_limits<double>::max()));
}


double TSPLocalSearchAlgorithms::logarithmicCoolingScheme(double currentTemperature, double initialTemperature,
                                                          double parameter, int currentIterationOrTime) {
    double nextTemperature = initialTemperature / (1 + parameter * log((currentIterationOrTime + 1) + 1));
    return ((nextTemperature > 0) ? nextTemperature : std::nextafter(0, std::numeric_limits<double>::max()));
}

std::vector<int> TSPLocalSearchAlgorithms::swapNeighbourhood(int i, int j, std::vector<int> currentSolution) {
    std::swap(currentSolution[i], currentSolution[j]);
    return currentSolution;
}

int TSPLocalSearchAlgorithms::swapNeighbourhoodTFValue(const IGraph *tspInstance, int i, int j,
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

    if (i == 0 && j == lastVertexIdx) {
        currentSolutionValue -= tspInstance->getEdgeParameter(currentSolution[jLeft], currentSolution[j]);
        currentSolutionValue += tspInstance->getEdgeParameter(nextSolution[jLeft], nextSolution[j]);

        currentSolutionValue -= tspInstance->getEdgeParameter(currentSolution[j], currentSolution[i]);
        currentSolutionValue += tspInstance->getEdgeParameter(nextSolution[j], nextSolution[i]);

        currentSolutionValue -= tspInstance->getEdgeParameter(currentSolution[i], currentSolution[iRight]);
        currentSolutionValue += tspInstance->getEdgeParameter(nextSolution[i], nextSolution[iRight]);
        return currentSolutionValue;
    }

    currentSolutionValue -= tspInstance->getEdgeParameter(currentSolution[iLeft], currentSolution[i]);
    currentSolutionValue += tspInstance->getEdgeParameter(nextSolution[iLeft], nextSolution[i]);

    currentSolutionValue -= tspInstance->getEdgeParameter(currentSolution[j], currentSolution[jRight]);
    currentSolutionValue += tspInstance->getEdgeParameter(nextSolution[j], nextSolution[jRight]);

    currentSolutionValue -= tspInstance->getEdgeParameter(currentSolution[i], currentSolution[iRight]);
    currentSolutionValue += tspInstance->getEdgeParameter(nextSolution[i], nextSolution[iRight]);

    if (j - i != 1) {
        currentSolutionValue -= tspInstance->getEdgeParameter(currentSolution[jLeft], currentSolution[j]);
        currentSolutionValue += tspInstance->getEdgeParameter(nextSolution[jLeft], nextSolution[j]);
    }
    return currentSolutionValue;
}

double TSPLocalSearchAlgorithms::sigmoidFunction(double x) {
    return 1.0 / (1.0 + exp(-x));
}
