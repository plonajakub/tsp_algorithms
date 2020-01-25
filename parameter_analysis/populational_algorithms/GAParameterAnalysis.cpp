#include "GAParameterAnalysis.h"
#include "../../utilities/TSPUtils.h"
#include <chrono>
#include <cmath>

using GAParameters = GeneticAlgorithmParameters::GAParameters;

void GAParameterAnalysis::run() {
    GeneticAlgorithmParameters gap;
    gap.setDefaultParameters();

//    performGeneticAlgorithmParameterRangeTests<int>(
//            GAParameters::PopulationSize, 2, 10, 100, 3);
//    performGeneticAlgorithmParameterRangeTests<double>(
//            GAParameters::MutationProbability, 2, 0, 0.5, 10);

    gap.setDefaultParameters();
    gap.mutationCoreFunction = TSPPopulationAlgorithms::insertionCore;
    performTimeBenchmark("insertionCore", gap, 2);
}

template<class T>
void
GAParameterAnalysis::performGeneticAlgorithmParameterRangeTests(GeneticAlgorithmParameters::GAParameters parameterID,
                                                                int nRepetitions, T startParameter, T endParameter,
                                                                int nSteps) {
    std::string parameterName;
    switch (parameterID) {
        case GeneticAlgorithmParameters::GAParameters::PopulationSize:
            parameterName = "population_size";
            break;
        case GeneticAlgorithmParameters::GAParameters::NGenerations:
            parameterName = "generations";
            break;
        case GeneticAlgorithmParameters::GAParameters::CrossoverProbability:
            parameterName = "crossover_probability";
            break;
        case GeneticAlgorithmParameters::GAParameters::MutationProbability:
            parameterName = "mutation_probability";
            break;
        case GeneticAlgorithmParameters::GAParameters::NElites:
            parameterName = "elites";
            break;
        case GeneticAlgorithmParameters::GAParameters::TournamentSize:
            parameterName = "tournament_size";
            break;
    }
    std::cout << "GA: " << parameterName << " analysis START" << std::endl;
    std::vector<std::pair<IGraph *, int>> tspInstances = loadInstances(getInstancePaths());

    GeneticAlgorithmParameters parameters;
    std::vector<int> tmpSolution;
    int tmpSolutionValue, bestSolutionValue;

    std::vector<AnalysisPoint<T>> parameterAnalysisPoints;
    AnalysisPoint<T> parameterPoint;

    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed = std::chrono::duration<double, std::milli>();

    T parameterStep = static_cast<double>(endParameter - startParameter) / nSteps;
    int analysedInstances = 0;
    for (const auto &tspInstance : tspInstances) {
        ++analysedInstances;
        for (T currentParameterValue = startParameter;
             currentParameterValue < endParameter; currentParameterValue += parameterStep) {
            std::cout << "Instance " << analysedInstances << '/' << tspInstances.size() << ": "
                      << round((static_cast<double>(currentParameterValue) / endParameter) * 100) << " %" << std::endl;
            parameterPoint = AnalysisPoint<T>();
            parameters.setDefaultParameters();

            switch (parameterID) {

                case GeneticAlgorithmParameters::GAParameters::PopulationSize:
                    parameters.populationSize = currentParameterValue;
                    break;
                case GeneticAlgorithmParameters::GAParameters::NGenerations:
                    parameters.nGenerations = currentParameterValue;
                    break;
                case GeneticAlgorithmParameters::GAParameters::CrossoverProbability:
                    parameters.crossoverProbability = currentParameterValue;
                    break;
                case GeneticAlgorithmParameters::GAParameters::MutationProbability:
                    parameters.mutationProbability = currentParameterValue;
                    break;
                case GeneticAlgorithmParameters::GAParameters::NElites:
                    parameters.nElites = currentParameterValue;
                    break;
                case GeneticAlgorithmParameters::GAParameters::TournamentSize:
                    parameters.tournamentSize = currentParameterValue;
                    break;
            }

            bestSolutionValue = std::numeric_limits<int>::max();
            for (int repetition = 0; repetition < nRepetitions; ++repetition) {
                tmpSolution.clear();

                start = std::chrono::high_resolution_clock::now();
                tmpSolutionValue = TSPPopulationAlgorithms::geneticAlgorithm(tspInstance.first, parameters,
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
    writeResultsToFile("genetic_algorithm", parameterAnalysisPoints, nRepetitions);
    std::cout << "DONE" << std::endl;

    // Cleanup
    for (const auto &item : tspInstances) {
        delete item.first;
    }
    std::cout << "GA: " << parameterName << " analysis DONE" << std::endl;
}

void GAParameterAnalysis::performTimeBenchmark(const std::string &testName, GeneticAlgorithmParameters parameters,
                                               int nRepetitions) {
    std::string algorithmName = "genetic_algorithm";

    std::cout << algorithmName << '_' << testName << ": time benchmark START" << std::endl;
    std::vector<std::pair<IGraph *, int>> tspInstances = loadInstances(getInstancePathsTimeTests());

    std::vector<int> tmpSolution;
    int tmpSolutionValue, bestSolutionValue;

    std::vector<AnalysisPoint<std::string>> timeAnalysisPoints;
    AnalysisPoint<std::string> timePoint;

    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed = std::chrono::duration<double, std::milli>();

    int analysedInstances = 0;
    for (const auto &tspInstance : tspInstances) {
        ++analysedInstances;
        timePoint = AnalysisPoint<std::string>();
        bestSolutionValue = std::numeric_limits<int>::max();
        for (int repetition = 0; repetition < nRepetitions; ++repetition) {
            std::cout << "Instance " << analysedInstances << '/' << tspInstances.size() << ": repetition "
                      << repetition << "/" << nRepetitions << std::endl;
            tmpSolution.clear();

            start = std::chrono::high_resolution_clock::now();
            tmpSolutionValue = TSPPopulationAlgorithms::geneticAlgorithm(tspInstance.first, parameters, tmpSolution);
            finish = std::chrono::high_resolution_clock::now();
            elapsed = finish - start;
            timePoint.time += elapsed.count();

            timePoint.algorithmMeanSolution += tmpSolutionValue;
            if (tmpSolutionValue < bestSolutionValue) {
                bestSolutionValue = tmpSolutionValue;
            }

        }
        timePoint.instanceSize = tspInstance.first->getVertexCount();
        timePoint.fileSolution = tspInstance.second;
        timePoint.algorithmBeastSolution = bestSolutionValue;
        timePoint.algorithmMeanSolution /= nRepetitions;
        timePoint.parameterName = testName;
        timePoint.parameterValue = '-';
        timePoint.time /= nRepetitions;
        timeAnalysisPoints.emplace_back(timePoint);
    }

    std::cout << "Writing collected data to file...";
    writeResultsToFile(algorithmName, timeAnalysisPoints, nRepetitions);
    std::cout << "DONE" << std::endl;

    // Cleanup
    for (const auto &item : tspInstances) {
        delete item.first;
    }
    std::cout << algorithmName << '_' << testName << ": time benchmark DONE" << std::endl;
}

std::vector<std::pair<IGraph *, int>>
GAParameterAnalysis::loadInstances(const std::map<std::string, std::vector<std::string>> &instancePaths) {
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

std::map<std::string, std::vector<std::string>> GAParameterAnalysis::getInstancePaths() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("opt.txt");
    filePaths.emplace_back("data10.txt"); //+
//    filePaths.emplace_back("data11.txt");
//    filePaths.emplace_back("data12.txt");
//    filePaths.emplace_back("data13.txt");
//    filePaths.emplace_back("data14.txt");
//    filePaths.emplace_back("data15.txt");
//    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data18.txt"); //+
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
//    filePaths.emplace_back("data65.txt"); //+
//    filePaths.emplace_back("data70.txt");
//    filePaths.emplace_back("data71.txt");
//    filePaths.emplace_back("data100.txt"); //+
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
//    filePaths.emplace_back("data24.txt"); //+
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt"); //+
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"../input_data/TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}

std::map<std::string, std::vector<std::string>> GAParameterAnalysis::getInstancePathsTimeTests() const {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // SMALL
    filePaths.emplace_back("opt.txt");
    filePaths.emplace_back("data10.txt");
    filePaths.emplace_back("data11.txt");
    filePaths.emplace_back("data12.txt");
    filePaths.emplace_back("data13.txt");
    filePaths.emplace_back("data14.txt");
    filePaths.emplace_back("data15.txt");
    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data18.txt");
    fileGroups.insert({"../input_data/SMALL", filePaths});
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
//    filePaths.emplace_back("data171.txt");
//    filePaths.emplace_back("data323.txt");
//    filePaths.emplace_back("data358.txt");
//    filePaths.emplace_back("data403.txt");
//    filePaths.emplace_back("data443.txt");
    fileGroups.insert({"../input_data/ATSP", filePaths});
    filePaths.clear();

    // TSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
    filePaths.emplace_back("data26.txt");
    filePaths.emplace_back("data29.txt");
    filePaths.emplace_back("data42.txt");
    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");
    fileGroups.insert({"../input_data/TSP", filePaths});
    filePaths.clear();

    return fileGroups;
}
