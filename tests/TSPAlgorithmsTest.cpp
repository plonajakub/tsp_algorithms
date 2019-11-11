#include "TSPAlgorithmsTest.h"

void TSPAlgorithmsTest::run() const {
//    bruteForceTest();
//    dynamicProgrammingHeldKarpTest();
    branchAndBoundTest();
}

void TSPAlgorithmsTest::bruteForceTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // ATSP
//    filePaths.emplace_back("best.txt");
//    filePaths.emplace_back("data17.txt");
//    filePaths.emplace_back("data34.txt");
//    filePaths.emplace_back("data36.txt");
//    filePaths.emplace_back("data39.txt");
//    filePaths.emplace_back("data43.txt");
//    filePaths.emplace_back("data45.txt");
//    filePaths.emplace_back("data48.txt");
//    filePaths.emplace_back("data53.txt");
//    filePaths.emplace_back("data56.txt");
//    filePaths.emplace_back("data65txt");
//    filePaths.emplace_back("data70.txt");
//    filePaths.emplace_back("data71.txt");
//    filePaths.emplace_back("data100.txt");
//    filePaths.emplace_back("data171.txt");
//    filePaths.emplace_back("data323.txt");
//    filePaths.emplace_back("data358.txt");
//    filePaths.emplace_back("data403.txt");
//    filePaths.emplace_back("data443.txt");

    fileGroups.insert({"ATSP", filePaths});

    filePaths.clear();
    // SMALL
    filePaths.emplace_back("opt.txt");
    filePaths.emplace_back("data10.txt");
    filePaths.emplace_back("data11.txt");
    filePaths.emplace_back("data12.txt");
//    filePaths.emplace_back("data13.txt");
//    filePaths.emplace_back("data14.txt");
//    filePaths.emplace_back("data15.txt");
//    filePaths.emplace_back("data16.txt");
//    filePaths.emplace_back("data17.txt");
//    filePaths.emplace_back("data18.txt");

    fileGroups.insert({"SMALL", filePaths});

    filePaths.clear();
    //TSP
//    filePaths.emplace_back("best.txt");
//    filePaths.emplace_back("data17.txt");
//    filePaths.emplace_back("data21.txt");
//    filePaths.emplace_back("data24.txt");
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");

    fileGroups.insert({"TSP", filePaths});

    testAlgorithm(fileGroups, TSPAlgorithms::bruteForce, "bruteForce");
}

void TSPAlgorithmsTest::dynamicProgrammingHeldKarpTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // ATSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
//    filePaths.emplace_back("data34.txt");
//    filePaths.emplace_back("data36.txt");
//    filePaths.emplace_back("data39.txt");
//    filePaths.emplace_back("data43.txt");
//    filePaths.emplace_back("data45.txt");
//    filePaths.emplace_back("data48.txt");
//    filePaths.emplace_back("data53.txt");
//    filePaths.emplace_back("data56.txt");
//    filePaths.emplace_back("data65txt");
//    filePaths.emplace_back("data70.txt");
//    filePaths.emplace_back("data71.txt");
//    filePaths.emplace_back("data100.txt");
//    filePaths.emplace_back("data171.txt");
//    filePaths.emplace_back("data323.txt");
//    filePaths.emplace_back("data358.txt");
//    filePaths.emplace_back("data403.txt");
//    filePaths.emplace_back("data443.txt");

    fileGroups.insert({"ATSP", filePaths});

    filePaths.clear();
    // SMALL
    filePaths.emplace_back("opt.txt");
    filePaths.emplace_back("data10.txt");
//    filePaths.emplace_back("data11.txt");
    filePaths.emplace_back("data12.txt");
//    filePaths.emplace_back("data13.txt");
//    filePaths.emplace_back("data14.txt");
//    filePaths.emplace_back("data15.txt");
//    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data18.txt");

    fileGroups.insert({"SMALL", filePaths});

    filePaths.clear();
    //TSP
    filePaths.emplace_back("best.txt");
//    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");

    fileGroups.insert({"TSP", filePaths});

    testAlgorithm(fileGroups, TSPAlgorithms::dynamicProgrammingHeldKarp, "dynamicProgrammingHeldKarp");
}

void TSPAlgorithmsTest::branchAndBoundTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // ATSP
    filePaths.emplace_back("best.txt");
//    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data34.txt");
    filePaths.emplace_back("data36.txt");
    filePaths.emplace_back("data39.txt");
//    filePaths.emplace_back("data43.txt");
//    filePaths.emplace_back("data45.txt");
//    filePaths.emplace_back("data48.txt");
//    filePaths.emplace_back("data53.txt");
//    filePaths.emplace_back("data56.txt");
//    filePaths.emplace_back("data65.txt");
//    filePaths.emplace_back("data70.txt");
//    filePaths.emplace_back("data71.txt");
//    filePaths.emplace_back("data100.txt");
//    filePaths.emplace_back("data171.txt");
//    filePaths.emplace_back("data323.txt");
//    filePaths.emplace_back("data358.txt");
//    filePaths.emplace_back("data403.txt");
//    filePaths.emplace_back("data443.txt");

    fileGroups.insert({"ATSP", filePaths});

    filePaths.clear();
    // SMALL
    filePaths.emplace_back("opt.txt");
    filePaths.emplace_back("mdata3.txt");
    filePaths.emplace_back("mdata4.txt");
    filePaths.emplace_back("mdata5.txt");
    filePaths.emplace_back("data10.txt");
    filePaths.emplace_back("data11.txt");
    filePaths.emplace_back("data12.txt");
    filePaths.emplace_back("data13.txt");
    filePaths.emplace_back("data14.txt");
    filePaths.emplace_back("data15.txt");
    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data18.txt");

    fileGroups.insert({"SMALL", filePaths});

    filePaths.clear();
    //TSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
    filePaths.emplace_back("data26.txt");
    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");

    fileGroups.insert({"TSP", filePaths});

    testAlgorithm(fileGroups, TSPAlgorithms::branchAndBound, "branchAndBound");
}

void TSPAlgorithmsTest::testAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                                      int (*tspAlgorithm)(const IGraph *, std::vector<int> &outSolution),
                                      const std::string &testName) const {
    std::cout << std::string(10, '-') << "Test \"" + testName + "\"" + " started" << std::string(10, '-') << std::endl;
    std::map<std::string, int> solutions;
    IGraph *tspInstance = nullptr;
    std::vector<int> solutionVector;
    int solutionPathCost;
    for (const auto &pair : instanceFiles) {
        if (pair.second.empty()) {
            continue;
        }
        solutions = TSPUtils::loadTSPSolutionValues(pair.first + "/" + pair.second[0]);
        for (int i = 1; i != pair.second.size(); ++i) {
            std::cout << "Testing instance " + pair.first + "/" + pair.second[i] + "...";
            delete tspInstance;
            TSPUtils::loadTSPInstance(&tspInstance, pair.first + "/" + pair.second[i]);
            solutionVector.clear();
            solutionPathCost = tspAlgorithm(tspInstance, solutionVector);
            if (solutionPathCost == solutions.at(pair.second[i].substr(0, pair.second[i].find('.'))) &&
                isSolutionValid(tspInstance, solutionVector, solutionPathCost)) {
                std::cout << "SUCCESS";
            } else {
                std::cout << "FAIL" << " [Returned solution: " << solutionPathCost << "]";
            }
            std::cout
//                    << std::endl << "Found path: " << solutionVector
                    << std::endl;
        }
    }
    delete tspInstance;
    std::cout << std::string(10, '-') << "Test \"" + testName + "\"" + " finished" << std::string(10, '-') << std::endl;
}

bool TSPAlgorithmsTest::isSolutionValid(IGraph *tspInstance, const std::vector<int> &solutionPermutation,
                                        int solutionPathCost) const {
    const int instanceSize = tspInstance->getVertexCount();

    if (solutionPermutation.size() != instanceSize) {
        return false;
    }

    std::vector<int> cityInSolutionCount(instanceSize, 0);
    for (const auto &city : solutionPermutation) {
        ++cityInSolutionCount[city];
    }
    for (const auto &cityOccurrences : cityInSolutionCount) {
        if (cityOccurrences != 1) {
            return false;
        }
    }

    return solutionPathCost == TSPUtils::calculateTargetFunctionValue(tspInstance, solutionPermutation);
}

