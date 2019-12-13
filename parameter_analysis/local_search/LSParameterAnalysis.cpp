#include "LSParameterAnalysis.h"
#include "../../structures/graphs/IGraph.h"
#include "../../utilities/TSPUtils.h"
#include "../../algorithms/helper_structures/LocalSearchParameters.h"
#include <chrono>
#include <vector>
#include <map>

void LSParameterAnalysis::run() {
    performSimulatedAnnealingTemperatureTests(10, 1, 10001, 10);
}

std::map<std::string, std::vector<std::string>> LSParameterAnalysis::getInstancePaths() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("opt.txt");
    filePaths.emplace_back("data10.txt");
//    filePaths.emplace_back("data11.txt");
//    filePaths.emplace_back("data12.txt");
//    filePaths.emplace_back("data13.txt");
//    filePaths.emplace_back("data14.txt");
//    filePaths.emplace_back("data15.txt");
//    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data18.txt");
    fileGroups.insert({"../input_data/SMALL", filePaths});
    filePaths.clear();

    // ATSP
    filePaths.emplace_back("best.txt");
//    filePaths.emplace_back("data17.txt");
//    filePaths.emplace_back("data34.txt");
//    filePaths.emplace_back("data36.txt");
//    filePaths.emplace_back("data39.txt");
//    filePaths.emplace_back("data43.txt");
//    filePaths.emplace_back("data45.txt");
//    filePaths.emplace_back("data48.txt");
//    filePaths.emplace_back("data53.txt");
//    filePaths.emplace_back("data56.txt");
    filePaths.emplace_back("data65.txt");
//    filePaths.emplace_back("data70.txt");
//    filePaths.emplace_back("data71.txt");
    filePaths.emplace_back("data100.txt");
//    filePaths.emplace_back("data171.txt");
//    filePaths.emplace_back("data323.txt");
//    filePaths.emplace_back("data358.txt");
//    filePaths.emplace_back("data403.txt");
//    filePaths.emplace_back("data443.txt");
    fileGroups.insert({"../input_data/ATSP", filePaths});
    filePaths.clear();

    // TSP
    filePaths.emplace_back("best.txt");
//    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"../input_data/TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}

std::vector<std::pair<IGraph *, int>>
LSParameterAnalysis::loadInstances(const std::map<std::string, std::vector<std::string>> &instancePaths) {
    std::vector<std::pair<IGraph *, int>> tspInstances;
    IGraph *instance = nullptr;
    std::map<std::string, int> optimalSolutions;
    std::string instancePath;
    for (const auto &fileGroup : instancePaths) {
        optimalSolutions = TSPUtils::loadTSPSolutionValuesAbsolutePath(fileGroup.first + '/' + fileGroup.second[0]);
        for (int i = 1; i < fileGroup.second.size(); ++i) {
            instancePath = fileGroup.first + '/' + fileGroup.second[i];
            TSPUtils::loadTSPInstanceAbsolutePath(&instance, instancePath,
                                                  TSPUtils::getTSPTypeAbsolutePath(instancePath));
            tspInstances.emplace_back(instance,
                                      optimalSolutions.at(
                                              fileGroup.second[i].substr(0, fileGroup.second[i].find('.'))));
        }
    }
    return tspInstances;
}

void LSParameterAnalysis::performSimulatedAnnealingTemperatureTests(int nRepetitions, double startTemperature,
                                                                    double endTemperature, int nSteps) {
    std::cout << "SA: temperature analysis START" << std::endl;
    std::vector<std::pair<IGraph *, int>> tspInstances = loadInstances(getInstancePaths());

    LocalSearchParameters parameters;
    std::vector<int> tmpSolution;
    int tmpSolutionValue, bestSolutionValue;

    std::vector<AnalysisPoint<double>> temperatureAnalysisPoints;
    AnalysisPoint<double> temperaturePoint;

    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed = std::chrono::duration<double, std::milli>();

    double temperatureStep = (endTemperature - startTemperature) / nSteps;
    int analysedInstances = 0;
    for (const auto &tspInstance : tspInstances) {
        ++analysedInstances;
        for (double currentTemperature = startTemperature;
             currentTemperature < endTemperature; currentTemperature += temperatureStep) {
            std::cout << "Instance "  << analysedInstances << '/' << tspInstances.size() << ": " << round((currentTemperature / endTemperature) * 100) << " %" << std::endl;
            temperaturePoint = AnalysisPoint<double>();
            parameters.setSimulatedAnnealingDefaultParameters();
            parameters.initialTemperature = currentTemperature;
            bestSolutionValue = std::numeric_limits<int>::max();
            for (int repetition = 0; repetition < nRepetitions; ++repetition) {
                tmpSolution.clear();

                start = std::chrono::high_resolution_clock::now();
                tmpSolutionValue = TSPLocalSearchAlgorithms::simulatedAnnealing(tspInstance.first, parameters,
                                                                                tmpSolution);
                finish = std::chrono::high_resolution_clock::now();
                elapsed = finish - start;
                temperaturePoint.time += elapsed.count();

                temperaturePoint.algorithmMeanSolution += tmpSolutionValue;
                if (tmpSolutionValue < bestSolutionValue) {
                    bestSolutionValue = tmpSolutionValue;
                }

            }
            temperaturePoint.instanceSize = tspInstance.first->getVertexCount();
            temperaturePoint.fileSolution = tspInstance.second;
            temperaturePoint.algorithmBeastSolution = bestSolutionValue;
            temperaturePoint.algorithmMeanSolution /= nRepetitions;
            temperaturePoint.parameterName = "initial_temperature";
            temperaturePoint.parameterValue = currentTemperature;
            temperaturePoint.time /= nRepetitions;
            temperatureAnalysisPoints.emplace_back(temperaturePoint);
        }
    }

    std::cout << "Writing collected data to file...";
    writeResultsToFile("simulated_annealing", temperatureAnalysisPoints, nRepetitions);
    std::cout << "DONE" << std::endl;

    // Cleanup
    for (const auto &item : tspInstances) {
        delete item.first;
    }
    std::cout << "SA: temperature analysis DONE" << std::endl;
}


