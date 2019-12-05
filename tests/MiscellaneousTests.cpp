#include "MiscellaneousTests.h"

void MiscellaneousTests::run() const {
//    randomNumberGenerationTest();
//    neighbourhoodTFDifferenceDesignationTest();
    createRandomPermutationTest();
}

void MiscellaneousTests::randomNumberGenerationTest() const {
    const int RANDOM_NUMBERS_QUANTITY = 10;

    cout << "Random ints" << endl;
    cout << "[0, 100]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getInt(0, 100) << ", ";
    }
    cout << Random::getInt(0, 100) << ']' << endl;

    cout << "[0, 1]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getInt(0, 1) << ", ";
    }
    cout << Random::getInt(0, 1) << ']' << endl;

    cout << "[2, 5]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getInt(2, 5) << ", ";
    }
    cout << Random::getInt(2, 5) << ']' << endl;
    cout << endl;


    const int PRECISION = 5;
    cout << "Random doubles" << endl;
    cout << "[0.0, 100.0]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << std::setprecision(PRECISION) << Random::getRealClosed(0, 100) << ", ";
    }
    cout << std::setprecision(PRECISION) << Random::getRealClosed(0, 100) << ']' << endl;

    cout << "[0.0, 1.0]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << std::setprecision(PRECISION) << Random::getRealClosed(0, 1) << ", ";
    }
    cout << std::setprecision(PRECISION) << Random::getRealClosed(0, 1) << ']' << endl;

    cout << "[2.0, 5.5]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << std::setprecision(PRECISION) << Random::getRealClosed(2, 5.5) << ", ";
    }
    cout << std::setprecision(PRECISION) << Random::getRealClosed(2, 5.5) << ']' << endl;
    cout << endl;

    cout << "Random bools" << endl;
    cout << "(true, 0): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(true, 0) << ", ";
    }
    cout << Random::getBool(true, 0) << ']' << endl;

    cout << "(true, 1): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(true, 1) << ", ";
    }
    cout << Random::getBool(true, 1) << ']' << endl;

    cout << "(true, 0.9): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(true, 0.9) << ", ";
    }
    cout << Random::getBool(true, 0.9) << ']' << endl;

    cout << "(true, 0.1): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(true, 0.1) << ", ";
    }
    cout << Random::getBool(true, 0.1) << ']' << endl;
    cout << endl;

    cout << "(false, 0): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(false, 0) << ", ";
    }
    cout << Random::getBool(false, 0) << ']' << endl;

    cout << "(false, 1): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(false, 1) << ", ";
    }
    cout << Random::getBool(false, 1) << ']' << endl;

    cout << "(false, 0.9): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(false, 0.9) << ", ";
    }
    cout << Random::getBool(false, 0.9) << ']' << endl;

    cout << "(false, 0.1): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(false, 0.1) << ", ";
    }
    cout << Random::getBool(false, 0.1) << ']' << endl;
    cout << endl;
}

void MiscellaneousTests::neighbourhoodTFDifferenceDesignationTest() const {
    cout << "neighbourhoodTFDifferenceDesignationTest...";
    IGraph *tspInstance = nullptr;
    std::string instanceFilePath = "ATSP/data443.txt";
    TSPUtils::loadTSPInstance(&tspInstance, instanceFilePath, TSPUtils::getTSPType(instanceFilePath));
    int instanceSize = tspInstance->getVertexCount();
    std::vector<int> currentSolution, nextSolution;
    int currentSolutionValue, nextSolutionValue;
    currentSolutionValue = TSPGreedyAlgorithms::greedy(tspInstance, currentSolution);
    int i, j;
    for (int counter = 0; counter < 1000000; ++counter) {
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

        nextSolution = TSPLocalSearchAlgorithms::swapNeighbourhood(i, j, currentSolution);
        nextSolutionValue = TSPLocalSearchAlgorithms::swapNeighbourhoodTFDifference(tspInstance, i, j, currentSolution,
                                                                                    nextSolution, currentSolutionValue);
        assert(nextSolutionValue == TSPUtils::calculateTargetFunctionValue(tspInstance, nextSolution));
    }
    delete tspInstance;
    cout << "FINISHED" << endl;
}

void MiscellaneousTests::createRandomPermutationTest() const {
    cout << "createRandomPermutationTest...";
    IGraph *tspInstance = nullptr;
    std::string instanceFilePath = "ATSP/data443.txt";
    TSPUtils::loadTSPInstance(&tspInstance, instanceFilePath, TSPUtils::getTSPType(instanceFilePath));
    std::vector<int> randomPermutation;
    int randomPermutationValue;

    for (int i = 0; i < 1000; ++i) {
        randomPermutation.clear();
        randomPermutationValue = TSPGreedyAlgorithms::createRandomPermutation(tspInstance, randomPermutation);
        assert(TSPUtils::isSolutionValid(tspInstance, randomPermutation, randomPermutationValue));
    }
    delete tspInstance;
    cout << "FINISHED" << endl;
}
