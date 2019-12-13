#ifndef PEA_P1_LSPARAMETERANALYSIS_H
#define PEA_P1_LSPARAMETERANALYSIS_H

#include <string>
#include <vector>
#include <map>
#include "../../structures/graphs/IGraph.h"
#include "../../algorithms/TSPLocalSearchAlgorithms.h"
#include <algorithm>
#include <fstream>

using std::endl;

template<class T>
struct AnalysisPoint {
    int instanceSize;
    double time;
    int fileSolution;
    int algorithmBeastSolution;
    int algorithmMeanSolution;

    std::string parameterName;
    // T = numeric value
    T parameterValue;

    AnalysisPoint() : instanceSize(-1), time(0), fileSolution(-1), algorithmBeastSolution(-1), algorithmMeanSolution(0),
                      parameterName(""),
                      parameterValue(-1) {}
};

class LSParameterAnalysis {

public:

    void run();

private:

    template<class T>
    void performSimulatedAnnealingParameterRangeTests(LocalSearchParameters::SAParameters parameterID, int nRepetitions,
                                                      T startParameter, T endParameter, int nSteps);

    void
    performSimulatedAnnealingCoolingSchemeParameterTests(
            TSPLocalSearchAlgorithms::fCoolingScheme coolingSchemeFunction, int nRepetitions, double startParameter,
            double endParameter, int nSteps);

    void performSimulatedAnnealingInitialSolutionTests(int nRepetitions);

    void performSimulatedAnnealingNeighbourhoodTests(int nRepetitions);

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

        std::string filePath = "../parameter_analysis/local_search/collected_data/" + algorithm + "/" +
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
};


#endif //PEA_P1_LSPARAMETERANALYSIS_H
