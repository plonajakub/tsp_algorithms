#include "MiscellaneousTests.h"

void MiscellaneousTests::run() const {
//    randomNumberGenerationTest();
    neighbourhoodDesignationTest(TSPLocalSearchAlgorithms::swapNeighbourhood, "SMALL/data10.txt",
                                 "swapNeighbourhood");
    neighbourhoodDesignationTest(TSPLocalSearchAlgorithms::insertNeighbourhood, "SMALL/data10.txt",
                                 "insertNeighbourhood");
    neighbourhoodDesignationTest(TSPLocalSearchAlgorithms::invertNeighbourhood, "SMALL/data10.txt",
                                 "invertNeighbourhood");
//    createRandomPermutationTest();
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

void MiscellaneousTests::neighbourhoodDesignationTest(TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction,
                                                      const std::string &instanceFileToTest,
                                                      const std::string &testName) const {
    cout << "Test \"" << testName << "\" on instance \"" << instanceFileToTest << "\"...";
    IGraph *tspInstance = nullptr;
    TSPUtils::loadTSPInstance(&tspInstance, instanceFileToTest, TSPUtils::getTSPType(instanceFileToTest));
    int instanceSize = tspInstance->getVertexCount();
    TSPLocalSearchAlgorithms::fNeighbourhoodDiff nextNeighbourTFValue;
    if (nextNeighbourFunction == TSPLocalSearchAlgorithms::swapNeighbourhood) {
        nextNeighbourTFValue = TSPLocalSearchAlgorithms::swapNeighbourhoodTFValue;
    } else if (nextNeighbourFunction == TSPLocalSearchAlgorithms::insertNeighbourhood) {
        nextNeighbourTFValue = TSPLocalSearchAlgorithms::insertNeighbourhoodTFValue;
    } else {
        nextNeighbourTFValue = TSPLocalSearchAlgorithms::invertNeighbourhoodTFValue;
    }
    std::vector<int> currentSolution, nextSolution;
    int currentSolutionValue, nextSolutionValue;
    currentSolutionValue = TSPGreedyAlgorithms::greedy(tspInstance, currentSolution);

    for (int i = 0; i < instanceSize; ++i) {
        for (int j = 0; j < instanceSize; ++j) {
            if (i == j) {
                continue;
            }
            nextSolution = nextNeighbourFunction(i, j, currentSolution);
            nextSolutionValue = nextNeighbourTFValue(tspInstance, i, j, currentSolution, nextSolution,
                                                     currentSolutionValue);
            if (TSPUtils::areSolutionsEqual(currentSolution, nextSolution)) {
                throw std::exception();
            }
            if (!TSPUtils::isSolutionValid(tspInstance, nextSolution, nextSolutionValue)) {
                throw std::exception();
            }
        }
    }

    delete tspInstance;
    cout << "SUCCESS" << endl;
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
