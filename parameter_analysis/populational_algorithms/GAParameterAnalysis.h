#ifndef PEA_P1_GAPARAMETERANALYSIS_H
#define PEA_P1_GAPARAMETERANALYSIS_H

#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "../../algorithms/helper_structures/GeneticAlgorithmParameters.h"
#include "../AnalysisPoint.h"

using std::cout;
using std::endl;


class GAParameterAnalysis {

public:
    void run();

private:
    template<class T>
    void
    performGeneticAlgorithmParameterRangeTests(GeneticAlgorithmParameters::GAParameters parameterID, int nRepetitions,
                                                 T startParameter, T endParameter, int nSteps);

    [[nodiscard]] std::map<std::string, std::vector<std::string>> getInstancePaths() const;

    // <instance, optimal solution>
    std::vector<std::pair<IGraph *, int>>
    loadInstances(const std::map<std::string, std::vector<std::string>> &instancePaths);

    template<class T>
    void
    writeResultsToFile(const std::string &algorithm, std::vector<AnalysisPoint<T>> &analysisPoints, int nRepetitions) {
        if (analysisPoints.empty()) {
            throw std::invalid_argument("analysisPoints is empty");
        }
        for (const auto &item : analysisPoints) {
            if (item.parameterName != analysisPoints[0].parameterName) {
                throw std::invalid_argument("analysisPoints is incoherent");
            }
        }

        std::string filePath = "../parameter_analysis/populational_algorithms/collected_data/" + algorithm + "/" +
                               analysisPoints[0].parameterName + ".csv";
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw std::logic_error("File at " + filePath + " could not be opened");
        }

        std::sort(analysisPoints.begin(), analysisPoints.end(),
                  [](const AnalysisPoint<T> &lhs, const AnalysisPoint<T> &rhs) {
                      if (lhs.instanceSize != rhs.instanceSize) {
                          return lhs.instanceSize < rhs.instanceSize;
                      }
                      return lhs.parameterValue < rhs.parameterValue;
                  });

        const char sep = ',';
        file << "Parameter name" << sep << "Repetitions" << sep << "Time unit" << endl;
        file << analysisPoints[0].parameterName << sep << nRepetitions << sep << "millisecond" << endl;

        file << "Instance size" << sep << "Parameter" << sep << "Time" << sep << "Optimal solution" << sep
             << "Best algorithm solution" << sep << "Mean algorithm solution" << endl;
        for (const auto &analysisPoint : analysisPoints) {
            file << analysisPoint.instanceSize << sep << analysisPoint.parameterValue << sep << analysisPoint.time
                 << sep << analysisPoint.fileSolution << sep << analysisPoint.algorithmBeastSolution << sep
                 << analysisPoint.algorithmMeanSolution << endl;
        }
        file.close();
    }

    [[nodiscard]] std::map<std::string, std::vector<std::string>> getInstancePathsTimeTests() const;

    void
    performTimeBenchmark(GeneticAlgorithmParameters parameters, int nRepetitions);
};




#endif //PEA_P1_GAPARAMETERANALYSIS_H
