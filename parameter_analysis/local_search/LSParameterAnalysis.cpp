#include "LSParameterAnalysis.h"
#include "../../structures/graphs/IGraph.h"
#include "../../utilities/TSPUtils.h"
#include "../../algorithms/helper_structures/LocalSearchParameters.h"
#include <chrono>
#include <vector>
#include <map>

template<>
AnalysisPoint<std::string>::AnalysisPoint() : instanceSize(-1), time(0), fileSolution(-1), algorithmBeastSolution(-1),
                                              algorithmMeanSolution(0),
                                              parameterName(""),
                                              parameterValue("") {}

void LSParameterAnalysis::run() {
//    performSimulatedAnnealingParameterRangeTests<double>(LocalSearchParameters::SAParameters::INITIAL_TEMPERATURE,
//                                                         2, 1, 10001, 2);
//    performSimulatedAnnealingParameterRangeTests<int>(LocalSearchParameters::SAParameters::ITERATIONS_NUMBER,
//                                                      2, 1, 1000, 2);
//    performSimulatedAnnealingParameterRangeTests<int>(LocalSearchParameters::SAParameters::EPOCH_ITERATIONS_NUMBER,
//                                                      2, 1, 500, 2);
//    performSimulatedAnnealingCoolingSchemeParameterTests(TSPLocalSearchAlgorithms::linearCoolingScheme, 2,
//                                                         1, 100, 2);
//    performSimulatedAnnealingCoolingSchemeParameterTests(TSPLocalSearchAlgorithms::geometricCoolingScheme, 2,
//                                                         0.01, 0.99, 2);
//    performSimulatedAnnealingCoolingSchemeParameterTests(TSPLocalSearchAlgorithms::logarithmicCoolingScheme, 2,
//                                                         1, 100, 2);
//    performSimulatedAnnealingInitialSolutionTests(2);
//    performSimulatedAnnealingNeighbourhoodTests(2);
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

template<class T>
void
LSParameterAnalysis::performSimulatedAnnealingParameterRangeTests(LocalSearchParameters::SAParameters parameterID,
                                                                  int nRepetitions,
                                                                  T startParameter, T endParameter, int nSteps) {
    std::string parameterName;
    switch (parameterID) {

        case LocalSearchParameters::SAParameters::INITIAL_TEMPERATURE:
            parameterName = "initial_temperature";
            break;
        case LocalSearchParameters::SAParameters::COOLING_SCHEME_PARAMETER:
            throw std::invalid_argument("This test isn't appropriate for cooling scheme parameter analysis");
        case LocalSearchParameters::SAParameters::EPOCH_ITERATIONS_NUMBER:
            parameterName = "epoch_iterations_number";
            break;
        case LocalSearchParameters::SAParameters::ITERATIONS_NUMBER:
            parameterName = "iterations_number";
            break;
    }
    std::cout << "SA: " << parameterName << " analysis START" << std::endl;
    std::vector<std::pair<IGraph *, int>> tspInstances = loadInstances(getInstancePaths());

    LocalSearchParameters parameters;
    std::vector<int> tmpSolution;
    int tmpSolutionValue, bestSolutionValue;

    std::vector<AnalysisPoint<T>> parameterAnalysisPoints;
    AnalysisPoint<T> parameterPoint;

    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed = std::chrono::duration<double, std::milli>();

    T parameterStep = ceil(static_cast<double>(endParameter - startParameter) / nSteps);
    int analysedInstances = 0;
    for (const auto &tspInstance : tspInstances) {
        ++analysedInstances;
        for (T currentParameterValue = startParameter;
             currentParameterValue < endParameter; currentParameterValue += parameterStep) {
            std::cout << "Instance " << analysedInstances << '/' << tspInstances.size() << ": "
                      << round((static_cast<double>(currentParameterValue) / endParameter) * 100) << " %" << std::endl;
            parameterPoint = AnalysisPoint<T>();
            parameters.setSimulatedAnnealingDefaultParameters();

            switch (parameterID) {

                case LocalSearchParameters::SAParameters::INITIAL_TEMPERATURE:
                    parameters.initialTemperature = currentParameterValue;
                    break;
                case LocalSearchParameters::SAParameters::EPOCH_ITERATIONS_NUMBER:
                    parameters.epochIterationsNumber = currentParameterValue;
                    break;
                case LocalSearchParameters::SAParameters::ITERATIONS_NUMBER:
                    parameters.iterationsNumber = currentParameterValue;
                    break;
            }

            bestSolutionValue = std::numeric_limits<int>::max();
            for (int repetition = 0; repetition < nRepetitions; ++repetition) {
                tmpSolution.clear();

                start = std::chrono::high_resolution_clock::now();
                tmpSolutionValue = TSPLocalSearchAlgorithms::simulatedAnnealing(tspInstance.first, parameters,
                                                                                tmpSolution);
                finish = std::chrono::high_resolution_clock::now();
                elapsed = finish - start;
                parameterPoint.time += elapsed.count();

                parameterPoint.algorithmMeanSolution += tmpSolutionValue;
                if (tmpSolutionValue < bestSolutionValue) {
                    bestSolutionValue = tmpSolutionValue;
                }

            }
            parameterPoint.instanceSize = tspInstance.first->getVertexCount();
            parameterPoint.fileSolution = tspInstance.second;
            parameterPoint.algorithmBeastSolution = bestSolutionValue;
            parameterPoint.algorithmMeanSolution /= nRepetitions;
            parameterPoint.parameterName = parameterName;
            parameterPoint.parameterValue = currentParameterValue;
            parameterPoint.time /= nRepetitions;
            parameterAnalysisPoints.emplace_back(parameterPoint);
        }
    }

    std::cout << "Writing collected data to file...";
    writeResultsToFile("simulated_annealing", parameterAnalysisPoints, nRepetitions);
    std::cout << "DONE" << std::endl;

    // Cleanup
    for (const auto &item : tspInstances) {
        delete item.first;
    }
    std::cout << "SA: " << parameterName << " analysis DONE" << std::endl;
}

void LSParameterAnalysis::performSimulatedAnnealingCoolingSchemeParameterTests(
        TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction, int nRepetitions, double startParameter,
        double endParameter, int nSteps) {
    std::string coolingSchemeName;
    if (coolingSchemeFunction == TSPLocalSearchAlgorithms::linearCoolingScheme) {
        coolingSchemeName = "linear_cooling_scheme";
    } else if (coolingSchemeFunction == TSPLocalSearchAlgorithms::geometricCoolingScheme) {
        coolingSchemeName = "geometric_cooling_scheme";
    } else {
        coolingSchemeName = "logarithmic_cooling_scheme";
    }

    std::cout << "SA: " << coolingSchemeName << " parameter analysis START" << std::endl;
    std::vector<std::pair<IGraph *, int>> tspInstances = loadInstances(getInstancePaths());

    LocalSearchParameters parameters;
    std::vector<int> tmpSolution;
    int tmpSolutionValue, bestSolutionValue;

    std::vector<AnalysisPoint<double>> coolingParameterAnalysisPoints;
    AnalysisPoint<double> coolingParameterPoint;

    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed = std::chrono::duration<double, std::milli>();

    double parameterStep = (endParameter - startParameter) / nSteps;
    int analysedInstances = 0;
    for (const auto &tspInstance : tspInstances) {
        ++analysedInstances;
        for (double currentParameter = startParameter;
             currentParameter < endParameter; currentParameter += parameterStep) {
            std::cout << "Instance " << analysedInstances << '/' << tspInstances.size() << ": "
                      << round((currentParameter / endParameter) * 100) << " %" << std::endl;
            coolingParameterPoint = AnalysisPoint<double>();
            parameters.setSimulatedAnnealingDefaultParameters();
            parameters.coolingSchemeFunction = coolingSchemeFunction;
            parameters.coolingSchemeParameter = currentParameter;
            bestSolutionValue = std::numeric_limits<int>::max();
            for (int repetition = 0; repetition < nRepetitions; ++repetition) {
                tmpSolution.clear();

                start = std::chrono::high_resolution_clock::now();
                tmpSolutionValue = TSPLocalSearchAlgorithms::simulatedAnnealing(tspInstance.first, parameters,
                                                                                tmpSolution);
                finish = std::chrono::high_resolution_clock::now();
                elapsed = finish - start;
                coolingParameterPoint.time += elapsed.count();

                coolingParameterPoint.algorithmMeanSolution += tmpSolutionValue;
                if (tmpSolutionValue < bestSolutionValue) {
                    bestSolutionValue = tmpSolutionValue;
                }

            }
            coolingParameterPoint.instanceSize = tspInstance.first->getVertexCount();
            coolingParameterPoint.fileSolution = tspInstance.second;
            coolingParameterPoint.algorithmBeastSolution = bestSolutionValue;
            coolingParameterPoint.algorithmMeanSolution /= nRepetitions;
            coolingParameterPoint.parameterName = coolingSchemeName;
            coolingParameterPoint.parameterValue = currentParameter;
            coolingParameterPoint.time /= nRepetitions;
            coolingParameterAnalysisPoints.emplace_back(coolingParameterPoint);
        }
    }

    std::cout << "Writing collected data to file...";
    writeResultsToFile("simulated_annealing", coolingParameterAnalysisPoints, nRepetitions);
    std::cout << "DONE" << std::endl;

    // Cleanup
    for (const auto &item : tspInstances) {
        delete item.first;
    }
    std::cout << "SA: " << coolingSchemeName << " parameter analysis DONE" << std::endl;
}

void LSParameterAnalysis::performSimulatedAnnealingInitialSolutionTests(int nRepetitions) {
    std::map<std::string, TSPGreedyAlgorithms::fTSPAlgorithm> initialSolutionAlgorithms = {
            {"natural_permutation", TSPGreedyAlgorithms::createNaturalPermutation},
            {"random_permutation",  TSPGreedyAlgorithms::createRandomPermutation},
            {"nearest_neighbour",   TSPGreedyAlgorithms::nearestNeighbour},
            {"greedy",              TSPGreedyAlgorithms::greedy}
    };

    std::cout << "SA: initial solution algorithm analysis START" << std::endl;
    std::vector<std::pair<IGraph *, int>> tspInstances = loadInstances(getInstancePaths());

    LocalSearchParameters parameters;
    std::vector<int> tmpSolution;
    int tmpSolutionValue, bestSolutionValue;

    std::vector<AnalysisPoint<std::string>> initialSolutionAnalysisPoints;
    AnalysisPoint<std::string> initialSolutionParameterPoint;

    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed = std::chrono::duration<double, std::milli>();

    int analysedInstances = 0;
    for (const auto &tspInstance : tspInstances) {
        ++analysedInstances;
        for (const auto &initialSolutionAlgorithm : initialSolutionAlgorithms) {
            std::cout << "Instance " << analysedInstances << '/' << tspInstances.size() << ": algorithm \""
                      << initialSolutionAlgorithm.first << "\"" << std::endl;
            initialSolutionParameterPoint = AnalysisPoint<std::string>();
            parameters.setSimulatedAnnealingDefaultParameters();
            parameters.initialSolutionFunction = initialSolutionAlgorithm.second;
            bestSolutionValue = std::numeric_limits<int>::max();
            for (int repetition = 0; repetition < nRepetitions; ++repetition) {
                tmpSolution.clear();

                start = std::chrono::high_resolution_clock::now();
                tmpSolutionValue = TSPLocalSearchAlgorithms::simulatedAnnealing(tspInstance.first, parameters,
                                                                                tmpSolution);
                finish = std::chrono::high_resolution_clock::now();
                elapsed = finish - start;
                initialSolutionParameterPoint.time += elapsed.count();

                initialSolutionParameterPoint.algorithmMeanSolution += tmpSolutionValue;
                if (tmpSolutionValue < bestSolutionValue) {
                    bestSolutionValue = tmpSolutionValue;
                }

            }
            initialSolutionParameterPoint.instanceSize = tspInstance.first->getVertexCount();
            initialSolutionParameterPoint.fileSolution = tspInstance.second;
            initialSolutionParameterPoint.algorithmBeastSolution = bestSolutionValue;
            initialSolutionParameterPoint.algorithmMeanSolution /= nRepetitions;
            initialSolutionParameterPoint.parameterName = "initial_solution_algorithm";
            initialSolutionParameterPoint.parameterValue = initialSolutionAlgorithm.first;
            initialSolutionParameterPoint.time /= nRepetitions;
            initialSolutionAnalysisPoints.emplace_back(initialSolutionParameterPoint);
        }
    }

    std::cout << "Writing collected data to file...";
    writeResultsToFile("simulated_annealing", initialSolutionAnalysisPoints, nRepetitions);
    std::cout << "DONE" << std::endl;

    // Cleanup
    for (const auto &item : tspInstances) {
        delete item.first;
    }
    std::cout << "SA: initial solution algorithm analysis DONE" << std::endl;
}

void LSParameterAnalysis::performSimulatedAnnealingNeighbourhoodTests(int nRepetitions) {
    std::map<std::string, TSPLocalSearchAlgorithms::fNeighbourhood> neighbourhoodAlgorithms = {
            {"swap",   TSPLocalSearchAlgorithms::swapNeighbourhood},
            {"insert", TSPLocalSearchAlgorithms::insertNeighbourhood},
            {"invert", TSPLocalSearchAlgorithms::invertNeighbourhood}
    };

    std::cout << "SA: neighbourhood algorithm analysis START" << std::endl;
    std::vector<std::pair<IGraph *, int>> tspInstances = loadInstances(getInstancePaths());

    LocalSearchParameters parameters;
    std::vector<int> tmpSolution;
    int tmpSolutionValue, bestSolutionValue;

    std::vector<AnalysisPoint<std::string>> neighbourhoodAnalysisPoints;
    AnalysisPoint<std::string> neighbourhoodParameterPoint;

    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed = std::chrono::duration<double, std::milli>();

    int analysedInstances = 0;
    for (const auto &tspInstance : tspInstances) {
        ++analysedInstances;
        for (const auto &neighbourhoodAlgorithm : neighbourhoodAlgorithms) {
            std::cout << "Instance " << analysedInstances << '/' << tspInstances.size() << ": algorithm \""
                      << neighbourhoodAlgorithm.first << "\"" << std::endl;
            neighbourhoodParameterPoint = AnalysisPoint<std::string>();
            parameters.setSimulatedAnnealingDefaultParameters();
            parameters.nextNeighbourFunction = neighbourhoodAlgorithm.second;
            bestSolutionValue = std::numeric_limits<int>::max();
            for (int repetition = 0; repetition < nRepetitions; ++repetition) {
                tmpSolution.clear();

                start = std::chrono::high_resolution_clock::now();
                tmpSolutionValue = TSPLocalSearchAlgorithms::simulatedAnnealing(tspInstance.first, parameters,
                                                                                tmpSolution);
                finish = std::chrono::high_resolution_clock::now();
                elapsed = finish - start;
                neighbourhoodParameterPoint.time += elapsed.count();

                neighbourhoodParameterPoint.algorithmMeanSolution += tmpSolutionValue;
                if (tmpSolutionValue < bestSolutionValue) {
                    bestSolutionValue = tmpSolutionValue;
                }

            }
            neighbourhoodParameterPoint.instanceSize = tspInstance.first->getVertexCount();
            neighbourhoodParameterPoint.fileSolution = tspInstance.second;
            neighbourhoodParameterPoint.algorithmBeastSolution = bestSolutionValue;
            neighbourhoodParameterPoint.algorithmMeanSolution /= nRepetitions;
            neighbourhoodParameterPoint.parameterName = "neighbourhood_algorithm";
            neighbourhoodParameterPoint.parameterValue = neighbourhoodAlgorithm.first;
            neighbourhoodParameterPoint.time /= nRepetitions;
            neighbourhoodAnalysisPoints.emplace_back(neighbourhoodParameterPoint);
        }
    }

    std::cout << "Writing collected data to file...";
    writeResultsToFile("simulated_annealing", neighbourhoodAnalysisPoints, nRepetitions);
    std::cout << "DONE" << std::endl;

    // Cleanup
    for (const auto &item : tspInstances) {
        delete item.first;
    }
    std::cout << "SA: neighbourhood algorithm analysis DONE" << std::endl;
}

template<class T>
void
LSParameterAnalysis::performTabuSearchParameterRangeTests(LocalSearchParameters::TSParameter parameterID,
                                                          int nRepetitions, T startParameter, T endParameter,
                                                          int nSteps) {
    std::string parameterName;
    switch (parameterID) {

        case LocalSearchParameters::TSParameter::ITERATIONS_NUMBER:
            parameterName = "iterations_number";
            break;
        case LocalSearchParameters::TSParameter::TABU_LIST_SIZE:
            parameterName = "tabu_list_size";
            break;
        case LocalSearchParameters::TSParameter::CADENZA_LENGTH_PARAMETER:
            parameterName = "cadenza_length_parameter";
            break;
        case LocalSearchParameters::TSParameter::ITERATIONS_WITHOUT_IMPROVEMENT_TO_RESTART:
            parameterName = "iterations_without_improvement_to_restart";
            break;
        case LocalSearchParameters::TSParameter::PATTERNS_NUMBER_TO_CACHE:
            parameterName = "patterns_number_to_cache";
            break;
    }
    std::cout << "TS: " << parameterName << " analysis START" << std::endl;
    std::vector<std::pair<IGraph *, int>> tspInstances = loadInstances(getInstancePaths());

    LocalSearchParameters parameters;
    std::vector<int> tmpSolution;
    int tmpSolutionValue, bestSolutionValue;

    std::vector<AnalysisPoint<T>> parameterAnalysisPoints;
    AnalysisPoint<T> parameterPoint;

    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed = std::chrono::duration<double, std::milli>();

    T parameterStep = ceil(static_cast<double>(endParameter - startParameter) / nSteps);
    int analysedInstances = 0;
    for (const auto &tspInstance : tspInstances) {
        ++analysedInstances;
        for (T currentParameterValue = startParameter;
             currentParameterValue < endParameter; currentParameterValue += parameterStep) {
            std::cout << "Instance " << analysedInstances << '/' << tspInstances.size() << ": "
                      << round((static_cast<double>(currentParameterValue) / endParameter) * 100) << " %" << std::endl;
            parameterPoint = AnalysisPoint<T>();
            parameters.setTabuSearchDefaultParameters();

            switch (parameterID) {

                case LocalSearchParameters::TSParameter::ITERATIONS_NUMBER:
                    parameters.iterationsNumber = currentParameterValue;
                    break;
                case LocalSearchParameters::TSParameter::TABU_LIST_SIZE:
                    parameters.tabuListSize = currentParameterValue;
                    break;
                case LocalSearchParameters::TSParameter::CADENZA_LENGTH_PARAMETER:
                    parameters.cadenzaLengthParameter = currentParameterValue;
                    break;
                case LocalSearchParameters::TSParameter::ITERATIONS_WITHOUT_IMPROVEMENT_TO_RESTART:
                    parameters.iterationsWithoutImprovementToRestart = currentParameterValue;
                    break;
                case LocalSearchParameters::TSParameter::PATTERNS_NUMBER_TO_CACHE:
                    parameters.patternsNumberToCache = currentParameterValue;
                    break;
            }

            bestSolutionValue = std::numeric_limits<int>::max();
            for (int repetition = 0; repetition < nRepetitions; ++repetition) {
                tmpSolution.clear();

                start = std::chrono::high_resolution_clock::now();
                tmpSolutionValue = TSPLocalSearchAlgorithms::tabuSearchList(tspInstance.first, parameters,
                                                                            tmpSolution);
                finish = std::chrono::high_resolution_clock::now();
                elapsed = finish - start;
                parameterPoint.time += elapsed.count();

                parameterPoint.algorithmMeanSolution += tmpSolutionValue;
                if (tmpSolutionValue < bestSolutionValue) {
                    bestSolutionValue = tmpSolutionValue;
                }

            }
            parameterPoint.instanceSize = tspInstance.first->getVertexCount();
            parameterPoint.fileSolution = tspInstance.second;
            parameterPoint.algorithmBeastSolution = bestSolutionValue;
            parameterPoint.algorithmMeanSolution /= nRepetitions;
            parameterPoint.parameterName = parameterName;
            parameterPoint.parameterValue = currentParameterValue;
            parameterPoint.time /= nRepetitions;
            parameterAnalysisPoints.emplace_back(parameterPoint);
        }
    }

    std::cout << "Writing collected data to file...";
    writeResultsToFile("tabu_search_list", parameterAnalysisPoints, nRepetitions);
    std::cout << "DONE" << std::endl;

    // Cleanup
    for (const auto &item : tspInstances) {
        delete item.first;
    }
    std::cout << "TS: " << parameterName << " analysis DONE" << std::endl;
}