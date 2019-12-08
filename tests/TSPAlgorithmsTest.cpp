#include "TSPAlgorithmsTest.h"

void TSPAlgorithmsTest::run() const {
//    bruteForceTest();
//    bruteForceTreeTest();
//    dynamicProgrammingHeldKarpTest();
//    branchAndBoundTest();
//
//    nearestNeighbourTest();
//    greedyTest();

    simulatedAnnealingTest();
//    tabuSearchTest();
}

//region Exact algorithms

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

    testExactOrGreedyAlgorithm(fileGroups, TSPExactAlgorithms::bruteForce, false, "bruteForce");
}

void TSPAlgorithmsTest::bruteForceTreeTest() const {
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

    testExactOrGreedyAlgorithm(fileGroups, TSPExactAlgorithms::bruteForceTree, false, "bruteForceTree");
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
    filePaths.emplace_back("tsp_13.txt");
    filePaths.emplace_back("tsp_14.txt");
    filePaths.emplace_back("tsp_15.txt");
    filePaths.emplace_back("tsp_17.txt");
    fileGroups.insert({"MIE", filePaths});
    filePaths.clear();

    testExactOrGreedyAlgorithm(fileGroups, TSPExactAlgorithms::dynamicProgrammingHeldKarp, false,
                               "dynamicProgrammingHeldKarp");
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
//    filePaths.emplace_back("tsp_17.txt");
    fileGroups.insert({"MIE", filePaths});
    filePaths.clear();

    testExactOrGreedyAlgorithm(fileGroups, TSPExactAlgorithms::branchAndBound, false, "branchAndBound");
//    testExactOrGreedyAlgorithm(fileGroups, TSPExactAlgorithms::branchAndBound0Heuristics, false, "branchAndBound0Heuristics");
//    testExactOrGreedyAlgorithm(fileGroups, TSPExactAlgorithms::branchAndBoundNNHeuristic, false, "branchAndBoundNNHeuristic");
//    testExactOrGreedyAlgorithm(fileGroups, TSPExactAlgorithms::branchAndBoundGHeuristic, false, "branchAndBoundGHeuristic");
//    testExactOrGreedyAlgorithm(fileGroups, TSPExactAlgorithms::branchAndBound2Heuristics, false, "branchAndBound2Heuristics");
}

//endregion

//region Greedy algorithms

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

    testExactOrGreedyAlgorithm(fileGroups, TSPGreedyAlgorithms::nearestNeighbour, true, "nearestNeighbour");
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

    testExactOrGreedyAlgorithm(fileGroups, TSPGreedyAlgorithms::greedy, true, "greedy");
}

//endregion

void TSPAlgorithmsTest::simulatedAnnealingTest() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // MY
//    filePaths.emplace_back("my_opt.txt");
//    filePaths.emplace_back("mdata2.txt");
//    filePaths.emplace_back("mdata3.txt");
//    filePaths.emplace_back("mdata4.txt");
//    filePaths.emplace_back("mdata5.txt");
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
//    filePaths.emplace_back("mie_opt.txt");
//    filePaths.emplace_back("tsp_6_1.txt");
//    filePaths.emplace_back("tsp_6_2.txt");
//    filePaths.emplace_back("tsp_10.txt");
//    filePaths.emplace_back("tsp_12.txt");
//    filePaths.emplace_back("tsp_13.txt");
//    filePaths.emplace_back("tsp_14.txt");
//    filePaths.emplace_back("tsp_15.txt");
//    filePaths.emplace_back("tsp_17.txt");
    fileGroups.insert({"MIE", filePaths});
    filePaths.clear();

    LocalSearchParameters parameters;
    parameters.initialTemperature = 1000;
    parameters.coolingSchemeParameter = 0.95;
    parameters.epochIterationsNumber = 500;
    parameters.iterationsNumber = 1000;
//    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::linearCoolingScheme;
//    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
//    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;

//    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;
//    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::linearCoolingScheme;
//    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
//    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::simulatedAnnealing, parameters,
//                             "Simulated annealing, greedy, linearCoolingScheme, swapNeighbourhood");
//
//    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;
//    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::geometricCoolingScheme;
//    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
//    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::simulatedAnnealing, parameters,
//                             "Simulated annealing, greedy, geometricCoolingScheme, swapNeighbourhood");

    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;
    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::logarithmicCoolingScheme;
    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::simulatedAnnealing, parameters,
                             "Simulated annealing, greedy, logarithmicCoolingScheme, swapNeighbourhood");

//    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;
//    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::geometricCoolingScheme;
//    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::insertNeighbourhood;
//    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::simulatedAnnealing, parameters,
//                             "Simulated annealing, greedy, geometricCoolingScheme, insertNeighbourhood");
//
//    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;
//    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::geometricCoolingScheme;
//    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::invertNeighbourhood;
//    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::simulatedAnnealing, parameters,
//                             "Simulated annealing, greedy, geometricCoolingScheme, invertNeighbourhood");
//
//    parameters.initialSolutionFunction = TSPGreedyAlgorithms::nearestNeighbour;
//    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::geometricCoolingScheme;
//    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::invertNeighbourhood;
//    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::simulatedAnnealing, parameters,
//                             "Simulated annealing, nearestNeighbour, geometricCoolingScheme, invertNeighbourhood");

    parameters.initialSolutionFunction = TSPGreedyAlgorithms::createNaturalPermutation;
    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::geometricCoolingScheme;
    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::invertNeighbourhood;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::simulatedAnnealing, parameters,
                             "Simulated annealing, createNaturalPermutation, geometricCoolingScheme, invertNeighbourhood");

//    parameters.initialSolutionFunction = TSPGreedyAlgorithms::createRandomPermutation;
//    parameters.coolingSchemeFunction = TSPLocalSearchAlgorithms::geometricCoolingScheme;
//    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::invertNeighbourhood;
//    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::simulatedAnnealing, parameters,
//                             "Simulated annealing, createRandomPermutation, geometricCoolingScheme, invertNeighbourhood");
}

void TSPAlgorithmsTest::tabuSearchTest() const {
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
    filePaths.emplace_back("data26.txt");
    filePaths.emplace_back("data29.txt");
    filePaths.emplace_back("data42.txt");
    filePaths.emplace_back("data58.txt");
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

    LocalSearchParameters parameters;
    parameters.iterationsNumber = 1000;
    parameters.tabuListSize = 100;
    parameters.cadenzaLengthParameter = 1.0/8;
    parameters.iterationsWithoutImprovementToRestart = 50;
    parameters.patternsNumberToCache = 2;
//    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
//    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;

    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::tabuSearchList, parameters,
                             "Tabu search, list, swap, greedy");

    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::insertNeighbourhood;
    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::tabuSearchList, parameters,
                             "Tabu search, list, insert, greedy");

    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::invertNeighbourhood;
    parameters.initialSolutionFunction = TSPGreedyAlgorithms::greedy;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::tabuSearchList, parameters,
                             "Tabu search, list, invert, greedy");

    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::swapNeighbourhood;
    parameters.initialSolutionFunction = TSPGreedyAlgorithms::createNaturalPermutation;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::tabuSearchMatrix, parameters,
                             "Tabu search, matrix, swap, natural");

    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::invertNeighbourhood;
    parameters.initialSolutionFunction = TSPGreedyAlgorithms::createNaturalPermutation;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::tabuSearchMatrix, parameters,
                             "Tabu search, matrix, invert, natural");

    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::invertNeighbourhood;
    parameters.initialSolutionFunction = TSPGreedyAlgorithms::createRandomPermutation;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::tabuSearchMatrix, parameters,
                             "Tabu search, matrix, invert, random");

    parameters.nextNeighbourFunction = TSPLocalSearchAlgorithms::invertNeighbourhood;
    parameters.initialSolutionFunction = TSPGreedyAlgorithms::nearestNeighbour;
    testLocalSearchAlgorithm(fileGroups, TSPLocalSearchAlgorithms::tabuSearchMatrix, parameters,
                             "Tabu search, matrix, invert, nearestNeighbour");
}

void TSPAlgorithmsTest::testExactOrGreedyAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
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
                TSPUtils::isSolutionValid(tspInstance, algorithmSolution, algorithmSolutionValue)) {
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

void TSPAlgorithmsTest::testLocalSearchAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                                                 TSPLocalSearchAlgorithms::fLocalSearchAlgorithm fLocalSearchAlgorithm,
                                                 const LocalSearchParameters &parameters,
                                                 const std::string &testName) const {
    std::cout << std::string(10, '-') << "Test \"" + testName + "\"" + " started" << std::string(10, '-') << std::endl;
    std::map<std::string, int> solutions;
    IGraph *tspInstance = nullptr;
    std::vector<int> algorithmSolution;
    int algorithmSolutionValue, fileSolutionValue;
    double algorithmErrorToFileSolutionValuePercentage;
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
            algorithmSolutionValue = fLocalSearchAlgorithm(tspInstance, parameters, algorithmSolution);
            fileSolutionValue = solutions.at(pair.second[i].substr(0, pair.second[i].find('.')));
            algorithmErrorToFileSolutionValuePercentage =
                    100 * (algorithmSolutionValue - fileSolutionValue) / static_cast<double>(fileSolutionValue);
            if (TSPUtils::isSolutionValid(tspInstance, algorithmSolution, algorithmSolutionValue)) {
                std::cout << "SUCCESS";
            } else {
                std::cout << "FAIL";
            }
            std::cout << " [ERR: " << std::setprecision(3) << algorithmErrorToFileSolutionValuePercentage << " %]";
            std::cout
//                    << std::endl << "Found path: " << algorithmSolution
                    << std::endl;
        }
    }
    delete tspInstance;
    std::cout << std::string(10, '-') << "Test \"" + testName + "\"" + " finished" << std::string(10, '-') << std::endl;
}



