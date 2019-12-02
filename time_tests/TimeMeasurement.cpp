#include "TimeMeasurement.h"

void TimeMeasurement::run() const {
    std::vector<MeasurementPoint> timeData;

    timeData = measureAlgorithm(getBruteForceSwapInstances(), TSPExactAlgorithms::bruteForce, "bruteForce");
    saveTimeDataToFile("brute_force_swap", "BF (swap)", timeData);

    timeData = measureAlgorithm(getBruteForceTreeInstances(), TSPExactAlgorithms::bruteForceTree, "bruteForceTree");
    saveTimeDataToFile("brute_force_tree", "BF (DFS)", timeData);

    timeData = measureAlgorithm(getDynamicProgrammingInstances(), TSPExactAlgorithms::dynamicProgrammingHeldKarp,
                                "dynamicProgrammingHeldKarp");
    saveTimeDataToFile("dynamic_programming", "DP (Held-Karp)", timeData);

    timeData = measureAlgorithm(getBranchAndBoundInstances(), TSPExactAlgorithms::branchAndBound0Heuristics,
                                "branchAndBound0Heuristics");
    saveTimeDataToFile("branch_and_bound_0h", "B&B (Little)", timeData);

    timeData = measureAlgorithm(getBranchAndBoundInstances(), TSPExactAlgorithms::branchAndBoundNNHeuristic,
                                "branchAndBoundNNHeuristic");
    saveTimeDataToFile("branch_and_bound_nn", "B&B (Little; NN)", timeData);

    timeData = measureAlgorithm(getBranchAndBoundInstances(), TSPExactAlgorithms::branchAndBoundGHeuristic,
                                "branchAndBoundGHeuristic");
    saveTimeDataToFile("branch_and_bound_g", "B&B (Little; G)", timeData);

    timeData = measureAlgorithm(getBranchAndBoundInstances(), TSPExactAlgorithms::branchAndBound2Heuristics,
                                "branchAndBound2Heuristics");
    saveTimeDataToFile("branch_and_bound_nn_g", "B&B (Little; NN; G)", timeData);
}

std::vector<MeasurementPoint>
TimeMeasurement::measureAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                                  int (*tspAlgorithm)(const IGraph *, std::vector<int> &),
                                  const std::string &algorithmName) const {
    cout << std::string(10, '-') << "Measurement of \"" + algorithmName + "\"" + " started" << std::string(10, '-')
         << endl;

    IGraph *tspInstance = nullptr;
    std::vector<int> algorithmSolution;
    std::vector<MeasurementPoint> measurementPoints;
    MeasurementPoint mp;
    if (instanceFiles.empty()) {
        throw std::invalid_argument("No instances provided for time tests of algorithm \"" + algorithmName + "\"");
    }
    for (const auto &pair : instanceFiles) {
        if (pair.second.empty()) {
            cout << "Warning: instance file group \"" + pair.first + "\"" + " of algorithm \"" + algorithmName + "\"" +
                    " is empty" << endl;
        }
        for (int i = 0; i != pair.second.size(); ++i) {
            std::cout << "Measuring instance " + pair.first + "/" + pair.second[i];
            delete tspInstance;
            TSPUtils::loadTSPInstance(&tspInstance, pair.first + "/" + pair.second[i]);
            mp.nVertex = tspInstance->getVertexCount();
            for (int nRepeats = 0; nRepeats < REPETITIONS_NUMBER; ++nRepeats) {
                algorithmSolution.clear();
                mp.time += countTime([&]() -> void {
                    tspAlgorithm(tspInstance, algorithmSolution);
                });
                cout << '.';
            }
            mp.time /= REPETITIONS_NUMBER;
            measurementPoints.emplace_back(mp);
            cout << endl;
        }
        cout << "Measurement of group \"" << pair.first << "\" completed!" << endl;
    }
    std::sort(measurementPoints.begin(), measurementPoints.end(),
              [](const MeasurementPoint &lhs, const MeasurementPoint &rhs) {
                  return lhs.nVertex < rhs.nVertex;
              });
    delete tspInstance;

    cout << std::string(10, '-') << "Measurement of \"" + algorithmName + "\"" + " finished" << std::string(10, '-')
         << endl;
    return measurementPoints;
}

double TimeMeasurement::countTime(const std::function<void()> &function) const {
    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed;
    start = std::chrono::high_resolution_clock::now();
    function();
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    return elapsed.count();
}

void
TimeMeasurement::saveTimeDataToFile(const std::string &fileName, const std::string &algorithmName,
                                    const std::vector<MeasurementPoint> &measurementPoints) const {
    const char sep = ',';
    const std::string fileExtension = ".csv";
    std::ofstream file("../time_tests/collected_data/exact_algorithms/" + fileName + fileExtension);
    if (!file.is_open()) {
        throw std::invalid_argument(fileName + fileExtension + " was not opened!");
    }

    cout << "Writing file " + fileName + fileExtension + "...";

    file << "Repetitions number" << sep << REPETITIONS_NUMBER << endl;
    file << "Time unit" << sep << "millisecond" << endl;
    file << "Algorithm\\Instance size";
    for (const auto &mp : measurementPoints) {
        file << sep << mp.nVertex;
    }
    file << endl;
    file << algorithmName;
    for (const auto &mp : measurementPoints) {
        file << sep << mp.time;
    }
    file << endl;

    file.close();
    cout << "FILE WRITTEN SUCCESSFULLY" << endl;
}

std::map<std::string, std::vector<std::string>> TimeMeasurement::getBruteForceSwapInstances() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("data10.txt"); //+
    filePaths.emplace_back("data11.txt"); //+
    filePaths.emplace_back("data12.txt"); //+
    filePaths.emplace_back("data13.txt"); //+ ~104s
//    filePaths.emplace_back("data14.txt");
//    filePaths.emplace_back("data15.txt");
//    filePaths.emplace_back("data16.txt");
//    filePaths.emplace_back("data18.txt");
    fileGroups.insert({"SMALL", filePaths});
    filePaths.clear();

    // ATSP
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
//    fileGroups.insert({"ATSP", filePaths});
//    filePaths.clear();

    // TSP
//    filePaths.emplace_back("data21.txt");
//    filePaths.emplace_back("data24.txt");
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
//    fileGroups.insert({"TSP", filePaths});
//    filePaths.clear();

    return fileGroups;
}

std::map<std::string, std::vector<std::string>> TimeMeasurement::getBruteForceTreeInstances() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("data10.txt"); //+
    filePaths.emplace_back("data11.txt"); //+
    filePaths.emplace_back("data12.txt"); //+
//    filePaths.emplace_back("data13.txt"); // > 5m
//    filePaths.emplace_back("data14.txt");
//    filePaths.emplace_back("data15.txt");
//    filePaths.emplace_back("data16.txt");
//    filePaths.emplace_back("data18.txt");
    fileGroups.insert({"SMALL", filePaths});
    filePaths.clear();

    // ATSP
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
//    fileGroups.insert({"ATSP", filePaths});
//    filePaths.clear();

    // TSP
//    filePaths.emplace_back("data21.txt");
//    filePaths.emplace_back("data24.txt");
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
//    fileGroups.insert({"TSP", filePaths});
//    filePaths.clear();

    return fileGroups;
}

std::map<std::string, std::vector<std::string>> TimeMeasurement::getDynamicProgrammingInstances() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("data10.txt"); //+
    filePaths.emplace_back("data11.txt"); //+
    filePaths.emplace_back("data12.txt"); //+
    filePaths.emplace_back("data13.txt"); //+
    filePaths.emplace_back("data14.txt"); //+
    filePaths.emplace_back("data15.txt"); //+
    filePaths.emplace_back("data16.txt"); //+
    filePaths.emplace_back("data18.txt"); //+
    fileGroups.insert({"SMALL", filePaths});
    filePaths.clear();

    // ATSP
    filePaths.emplace_back("data17.txt");  //+
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

    // TSP
    filePaths.emplace_back("data21.txt"); //+
    filePaths.emplace_back("data24.txt"); //+
//    filePaths.emplace_back("data26.txt"); // > 4m
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}

std::map<std::string, std::vector<std::string>> TimeMeasurement::getBranchAndBoundInstances() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("data10.txt"); //+
    filePaths.emplace_back("data11.txt"); //+
    filePaths.emplace_back("data12.txt"); //+
    filePaths.emplace_back("data13.txt"); //+
    filePaths.emplace_back("data14.txt"); //+
    filePaths.emplace_back("data15.txt"); //+
    filePaths.emplace_back("data16.txt"); //+
    filePaths.emplace_back("data18.txt"); //+
    fileGroups.insert({"SMALL", filePaths});
    filePaths.clear();

    // ATSP
    filePaths.emplace_back("data17.txt"); //+
    filePaths.emplace_back("data34.txt"); //+
    filePaths.emplace_back("data36.txt"); //+
    filePaths.emplace_back("data39.txt"); //+
//    filePaths.emplace_back("data43.txt"); // > 3m
    filePaths.emplace_back("data45.txt"); //+
//    filePaths.emplace_back("data48.txt"); // > 3m
//    filePaths.emplace_back("data53.txt"); // > 3m
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

    // TSP
    filePaths.emplace_back("data21.txt"); //+
    filePaths.emplace_back("data24.txt"); //+
    filePaths.emplace_back("data26.txt"); //+
    filePaths.emplace_back("data29.txt"); //+
//    filePaths.emplace_back("data42.txt"); // > 4m
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}

std::map<std::string, std::vector<std::string>> TimeMeasurement::getBranchAndBound0HInstances() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("data10.txt"); //+
    filePaths.emplace_back("data11.txt"); //+
    filePaths.emplace_back("data12.txt"); //+
    filePaths.emplace_back("data13.txt"); //+
    filePaths.emplace_back("data14.txt"); //+
    filePaths.emplace_back("data15.txt"); //+
    filePaths.emplace_back("data16.txt"); //+
    filePaths.emplace_back("data18.txt"); //+
    fileGroups.insert({"SMALL", filePaths});
    filePaths.clear();

    // ATSP
    filePaths.emplace_back("data17.txt"); //+
    filePaths.emplace_back("data34.txt"); //+
    filePaths.emplace_back("data36.txt"); //+
    filePaths.emplace_back("data39.txt"); //+
//    filePaths.emplace_back("data43.txt"); // > 3m
    filePaths.emplace_back("data45.txt"); //+
//    filePaths.emplace_back("data48.txt"); // > 3m
//    filePaths.emplace_back("data53.txt"); // > 3m
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

    // TSP
    filePaths.emplace_back("data21.txt"); //+
    filePaths.emplace_back("data24.txt"); //+
    filePaths.emplace_back("data26.txt"); //+
    filePaths.emplace_back("data29.txt"); //+
//    filePaths.emplace_back("data42.txt"); // > 4m
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}

std::map<std::string, std::vector<std::string>> TimeMeasurement::getBranchAndBoundNNInstances() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("data10.txt");
    filePaths.emplace_back("data11.txt");
    filePaths.emplace_back("data12.txt");
    filePaths.emplace_back("data13.txt");
    filePaths.emplace_back("data14.txt");
    filePaths.emplace_back("data15.txt");
    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data18.txt");
    fileGroups.insert({"SMALL", filePaths});
    filePaths.clear();

    // ATSP
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

    // TSP
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
    filePaths.emplace_back("data26.txt");
    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}

std::map<std::string, std::vector<std::string>> TimeMeasurement::getBranchAndBoundGInstances() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("data10.txt");
    filePaths.emplace_back("data11.txt");
    filePaths.emplace_back("data12.txt");
    filePaths.emplace_back("data13.txt");
    filePaths.emplace_back("data14.txt");
    filePaths.emplace_back("data15.txt");
    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data18.txt");
    fileGroups.insert({"SMALL", filePaths});
    filePaths.clear();

    // ATSP
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

    // TSP
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
    filePaths.emplace_back("data26.txt");
    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}

std::map<std::string, std::vector<std::string>> TimeMeasurement::getBranchAndBound2HInstances() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("data10.txt");
    filePaths.emplace_back("data11.txt");
    filePaths.emplace_back("data12.txt");
    filePaths.emplace_back("data13.txt");
    filePaths.emplace_back("data14.txt");
    filePaths.emplace_back("data15.txt");
    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data18.txt");
    fileGroups.insert({"SMALL", filePaths});
    filePaths.clear();

    // ATSP
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

    // TSP
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
    filePaths.emplace_back("data26.txt");
    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}
