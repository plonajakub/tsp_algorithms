#ifndef PEA_P1_TIMEMEASUREMENT_H
#define PEA_P1_TIMEMEASUREMENT_H

#include <iostream>
#include <fstream>
#include <exception>
#include <climits>
#include <functional>
#include <chrono>
#include <algorithm>

#include "../structures/graphs/IGraph.h"
#include "../algorithms/TSPExactAlgorithms.h"
#include "../utilities/TSPUtils.h"

using std::cout;
using std::endl;

struct MeasurementPoint {
    int nVertex;
    double time;

    MeasurementPoint() : nVertex(-1), time(0) {}

    MeasurementPoint(int nVertex, double time) : nVertex(nVertex), time(time) {}
};

class TimeMeasurement {
public:

    // Start time measurement
    void run() const;

private:

    // Number of repeated operations of the same type with the same size
    static const int REPETITIONS_NUMBER = 15;

    std::vector<MeasurementPoint> measureAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                                                   int (*tspAlgorithm)(const IGraph *, std::vector<int> &),
                                                   const std::string &algorithmName) const;

    double countTime(const std::function<void()> &function) const;


    void saveTimeDataToFile(const std::string &fileName, const std::string &algorithmName,
                            const std::vector<MeasurementPoint> &measurementPoints) const;

    [[nodiscard]] std::map<std::string, std::vector<std::string>> getBruteForceSwapInstances() const;
    [[nodiscard]] std::map<std::string, std::vector<std::string>> getBruteForceTreeInstances() const;
    [[nodiscard]] std::map<std::string, std::vector<std::string>> getDynamicProgrammingInstances() const;
    [[nodiscard]] std::map<std::string, std::vector<std::string>> getBranchAndBoundInstances() const;
    [[nodiscard]] std::map<std::string, std::vector<std::string>> getBranchAndBound0HInstances() const;
    [[nodiscard]] std::map<std::string, std::vector<std::string>> getBranchAndBoundNNInstances() const;
    [[nodiscard]] std::map<std::string, std::vector<std::string>> getBranchAndBoundGInstances() const;
    [[nodiscard]] std::map<std::string, std::vector<std::string>> getBranchAndBound2HInstances() const;

};


#endif //PEA_P1_TIMEMEASUREMENT_H
