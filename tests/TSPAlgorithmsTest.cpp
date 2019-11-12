#include "TSPAlgorithmsTest.h"

void TSPAlgorithmsTest::run() const {
    bruteForceTest();
    dynamicProgrammingHeldKarpTest();
    branchAndBoundTest();
    nearestNeighbourTest();
    greedyTest();
}

void TSPAlgorithmsTest::bruteForceTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // MY
    filePaths.emplace_back("my_opt.txt");
    filePaths.emplace_back("mdata2.txt");
    filePaths.emplace_back("mdata3.txt");
    filePaths.emplace_back("mdata4.txt");
    filePaths.emplace_back("mdata5.txt");
    fileGroups.insert({"MY", filePaths});
    filePaths.clear();

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

    // TSP
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
    filePaths.clear();

    // MIE
    filePaths.emplace_back("mie_opt.txt");
    filePaths.emplace_back("tsp_6_1.txt");
    filePaths.emplace_back("tsp_6_2.txt");
    filePaths.emplace_back("tsp_10.txt");
    filePaths.emplace_back("tsp_12.txt");
//    filePaths.emplace_back("tsp_13.txt");
//    filePaths.emplace_back("tsp_14.txt");
//    filePaths.emplace_back("tsp_15.txt");
//    filePaths.emplace_back("tsp_17.txt");
    fileGroups.insert({"MIE", filePaths});
    filePaths.clear();

    testAlgorithm(fileGroups, TSPAlgorithms::bruteForce, false, "bruteForce");
}

void TSPAlgorithmsTest::dynamicProgrammingHeldKarpTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // MY
    filePaths.emplace_back("my_opt.txt");
    filePaths.emplace_back("mdata2.txt");
    filePaths.emplace_back("mdata3.txt");
    filePaths.emplace_back("mdata4.txt");
    filePaths.emplace_back("mdata5.txt");
    fileGroups.insert({"MY", filePaths});
    filePaths.clear();

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

    // TSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data21.txt");
//    filePaths.emplace_back("data24.txt");
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    // MIE
    filePaths.emplace_back("mie_opt.txt");
    filePaths.emplace_back("tsp_6_1.txt");
    filePaths.emplace_back("tsp_6_2.txt");
    filePaths.emplace_back("tsp_10.txt");
    filePaths.emplace_back("tsp_12.txt");
    filePaths.emplace_back("tsp_13.txt");
    filePaths.emplace_back("tsp_14.txt");
    filePaths.emplace_back("tsp_15.txt");
    filePaths.emplace_back("tsp_17.txt");
    fileGroups.insert({"MIE", filePaths});
    filePaths.clear();

    testAlgorithm(fileGroups, TSPAlgorithms::dynamicProgrammingHeldKarp, false, "dynamicProgrammingHeldKarp");
}

void TSPAlgorithmsTest::branchAndBoundTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // MY
    filePaths.emplace_back("my_opt.txt");
    filePaths.emplace_back("mdata2.txt");
    filePaths.emplace_back("mdata3.txt");
    filePaths.emplace_back("mdata4.txt");
    filePaths.emplace_back("mdata5.txt");
    fileGroups.insert({"MY", filePaths});
    filePaths.clear();

    // ATSP
    filePaths.emplace_back("best.txt");
//    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data34.txt");
    filePaths.emplace_back("data36.txt");
//    filePaths.emplace_back("data39.txt");
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

    // TSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    // MIE
    filePaths.emplace_back("mie_opt.txt");
    filePaths.emplace_back("tsp_6_1.txt");
    filePaths.emplace_back("tsp_6_2.txt");
    filePaths.emplace_back("tsp_10.txt");
    filePaths.emplace_back("tsp_12.txt");
    filePaths.emplace_back("tsp_13.txt");
    filePaths.emplace_back("tsp_14.txt");
    filePaths.emplace_back("tsp_15.txt");
    filePaths.emplace_back("tsp_17.txt");
    fileGroups.insert({"MIE", filePaths});
    filePaths.clear();

    testAlgorithm(fileGroups, TSPAlgorithms::branchAndBound, false, "branchAndBound");
}

void TSPAlgorithmsTest::nearestNeighbourTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // MY
    filePaths.emplace_back("my_opt.txt");
    filePaths.emplace_back("mdata2.txt");
    filePaths.emplace_back("mdata3.txt");
    filePaths.emplace_back("mdata4.txt");
    filePaths.emplace_back("mdata5.txt");
    fileGroups.insert({"MY", filePaths});
    filePaths.clear();

    // ATSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data34.txt");
    filePaths.emplace_back("data36.txt");
    filePaths.emplace_back("data39.txt");
    filePaths.emplace_back("data43.txt");
    filePaths.emplace_back("data45.txt");
    filePaths.emplace_back("data48.txt");
    filePaths.emplace_back("data53.txt");
    filePaths.emplace_back("data56.txt");
    filePaths.emplace_back("data65.txt");
    filePaths.emplace_back("data70.txt");
    filePaths.emplace_back("data71.txt");
    filePaths.emplace_back("data100.txt");
    filePaths.emplace_back("data171.txt");
    filePaths.emplace_back("data323.txt");
    filePaths.emplace_back("data358.txt");
    filePaths.emplace_back("data403.txt");
    filePaths.emplace_back("data443.txt");
    fileGroups.insert({"ATSP", filePaths});
    filePaths.clear();

    // SMALL
    filePaths.emplace_back("opt.txt");
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

    // TSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
    filePaths.emplace_back("data26.txt");
    filePaths.emplace_back("data29.txt");
    filePaths.emplace_back("data42.txt");
    filePaths.emplace_back("data58.txt");
    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    // MIE
    filePaths.emplace_back("mie_opt.txt");
    filePaths.emplace_back("tsp_6_1.txt");
    filePaths.emplace_back("tsp_6_2.txt");
    filePaths.emplace_back("tsp_10.txt");
    filePaths.emplace_back("tsp_12.txt");
    filePaths.emplace_back("tsp_13.txt");
    filePaths.emplace_back("tsp_14.txt");
    filePaths.emplace_back("tsp_15.txt");
    filePaths.emplace_back("tsp_17.txt");
    fileGroups.insert({"MIE", filePaths});
    filePaths.clear();

    testAlgorithm(fileGroups, TSPAlgorithms::nearestNeighbour, true, "nearestNeighbour");
}

void TSPAlgorithmsTest::greedyTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // MY
    filePaths.emplace_back("my_opt.txt");
    filePaths.emplace_back("mdata2.txt");
    filePaths.emplace_back("mdata3.txt");
    filePaths.emplace_back("mdata4.txt");
    filePaths.emplace_back("mdata5.txt");
    fileGroups.insert({"MY", filePaths});
    filePaths.clear();

    // ATSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data34.txt");
    filePaths.emplace_back("data36.txt");
    filePaths.emplace_back("data39.txt");
    filePaths.emplace_back("data43.txt");
    filePaths.emplace_back("data45.txt");
    filePaths.emplace_back("data48.txt");
    filePaths.emplace_back("data53.txt");
    filePaths.emplace_back("data56.txt");
    filePaths.emplace_back("data65.txt");
    filePaths.emplace_back("data70.txt");
    filePaths.emplace_back("data71.txt");
    filePaths.emplace_back("data100.txt");
    filePaths.emplace_back("data171.txt");
    filePaths.emplace_back("data323.txt");
    filePaths.emplace_back("data358.txt");
    filePaths.emplace_back("data403.txt");
    filePaths.emplace_back("data443.txt");
    fileGroups.insert({"ATSP", filePaths});
    filePaths.clear();

    // SMALL
    filePaths.emplace_back("opt.txt");
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

    // TSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
    filePaths.emplace_back("data26.txt");
    filePaths.emplace_back("data29.txt");
    filePaths.emplace_back("data42.txt");
    filePaths.emplace_back("data58.txt");
    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    // MIE
    filePaths.emplace_back("mie_opt.txt");
    filePaths.emplace_back("tsp_6_1.txt");
    filePaths.emplace_back("tsp_6_2.txt");
    filePaths.emplace_back("tsp_10.txt");
    filePaths.emplace_back("tsp_12.txt");
    filePaths.emplace_back("tsp_13.txt");
    filePaths.emplace_back("tsp_14.txt");
    filePaths.emplace_back("tsp_15.txt");
    filePaths.emplace_back("tsp_17.txt");
    fileGroups.insert({"MIE", filePaths});
    filePaths.clear();

    testAlgorithm(fileGroups, TSPAlgorithms::greedy, true, "greedy");
}

void TSPAlgorithmsTest::testAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                                      int (*tspAlgorithm)(const IGraph *, std::vector<int> &),
                                      bool isSolutionApproximated, const std::string &testName) const {
    std::cout << std::string(10, '-') << "Test \"" + testName + "\"" + " started" << std::string(10, '-') << std::endl;
    std::map<std::string, int> solutions;
    IGraph *tspInstance = nullptr;
    std::vector<int> algorithmSolution;
    int algorithmSolutionValue, fileSolutionValue;
    for (const auto &pair : instanceFiles) {
        if (pair.second.empty()) {
            continue;
        }
        solutions = TSPUtils::loadTSPSolutionValues(pair.first + "/" + pair.second[0]);
        for (int i = 1; i != pair.second.size(); ++i) {
            std::cout << "Testing instance " + pair.first + "/" + pair.second[i] + "...";
            delete tspInstance;
            TSPUtils::loadTSPInstance(&tspInstance, pair.first + "/" + pair.second[i]);
            algorithmSolution.clear();
            algorithmSolutionValue = tspAlgorithm(tspInstance, algorithmSolution);
            fileSolutionValue = solutions.at(pair.second[i].substr(0, pair.second[i].find('.')));
            if ((isSolutionApproximated || algorithmSolutionValue == fileSolutionValue) &&
                isSolutionValid(tspInstance, algorithmSolution, algorithmSolutionValue)) {
                std::cout << "SUCCESS";
            } else {
                std::cout << "FAIL" << " [Returned solution cost: " << algorithmSolutionValue << "]";
            }
            std::cout
//                    << std::endl << "Found path: " << algorithmSolution
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
        if (city < 0 || city >= instanceSize) {
            return false;
        }
        ++cityInSolutionCount[city];
    }
    for (const auto &cityOccurrences : cityInSolutionCount) {
        if (cityOccurrences != 1) {
            return false;
        }
    }
    return solutionPathCost == TSPUtils::calculateTargetFunctionValue(tspInstance, solutionPermutation);
}

