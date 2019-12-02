#include "TSPGreedyAlgorithms.h"

int TSPGreedyAlgorithms::nearestNeighbour(const IGraph *tspInstance, std::vector<int> &outSolution) {
    const int instanceSize = tspInstance->getVertexCount();
    std::vector<bool> isVertexVisited(instanceSize, false);

    outSolution.emplace_back(0);
    isVertexVisited[0] = true;

    int currentRowValue, rowMinimum;
    int rowMinimumIndex;
    while (outSolution.size() != instanceSize) {
        rowMinimum = std::numeric_limits<int>::max();
        for (int j = 0; j < instanceSize; ++j) {
            if (isVertexVisited[j]) {
                continue;
            }
            currentRowValue = tspInstance->getEdgeParameter(outSolution.back(), j);
            if (currentRowValue < rowMinimum) {
                rowMinimum = currentRowValue;
                rowMinimumIndex = j;
            }
        }
        outSolution.emplace_back(rowMinimumIndex);
        isVertexVisited[rowMinimumIndex] = true;
    }
    return TSPUtils::calculateTargetFunctionValue(tspInstance, outSolution);
}

int TSPGreedyAlgorithms::greedy(const IGraph *tspInstance, std::vector<int> &outSolution) {
    const int instanceSize = tspInstance->getVertexCount();

    std::__cxx11::list<TSPEdge> edgesList;
    for (int i = 0; i < instanceSize; ++i) {
        for (int j = 0; j < instanceSize; ++j) {
            if (i == j) {
                continue;
            }
            edgesList.emplace_back(i, j, tspInstance->getEdgeParameter(i, j));
        }
    }
    edgesList.sort([](const TSPEdge &lhs, const TSPEdge &rhs) -> bool {
        return lhs.cost < rhs.cost;
    });

    int iCityPathIdx, jCityPathIdx;
    std::vector<std::list<int>> partialPaths;
    // [i][0] -> true if the city was exited, [i][1] -> true if the city was entered
    std::vector<std::vector<bool>> cityOnPath(instanceSize, std::vector<bool>(2, false));
    while (!edgesList.empty()) {
        if (cityOnPath[edgesList.front().i][0] || cityOnPath[edgesList.front().j][1]) {
            edgesList.pop_front();
            continue;
        }
        iCityPathIdx = -1;
        jCityPathIdx = -1;
        for (int k = 0; k != partialPaths.size(); ++k) {
            if (partialPaths[k].back() == edgesList.front().i) {
                iCityPathIdx = k;
            }
            if (partialPaths[k].front() == edgesList.front().j) {
                jCityPathIdx = k;
            }
            if (iCityPathIdx != -1 && jCityPathIdx != -1) {
                break;
            }
        }

        if (iCityPathIdx == -1 && jCityPathIdx == -1) {
            partialPaths.emplace_back();
            auto newPathIt = partialPaths.end();
            --newPathIt;
            newPathIt->emplace_back(edgesList.front().i);
            newPathIt->emplace_back(edgesList.front().j);
        } else if (iCityPathIdx != -1 && jCityPathIdx == -1) {
            partialPaths[iCityPathIdx].emplace_back(edgesList.front().j);
        } else if (iCityPathIdx == -1 /*&& jCityPathIdx != -1*/) {
            partialPaths[jCityPathIdx].emplace_front(edgesList.front().i);
        } else if (iCityPathIdx != jCityPathIdx) {
            partialPaths[iCityPathIdx].splice(partialPaths[iCityPathIdx].end(),
                                              partialPaths[jCityPathIdx]);
            partialPaths.erase(partialPaths.begin() + jCityPathIdx);
        } else { // iCityPathIdx == jCityPathIdx
            edgesList.pop_front();
            continue;
        }

        cityOnPath[edgesList.front().i][0] = true;
        cityOnPath[edgesList.front().j][1] = true;
        edgesList.pop_front();
    }
    for (const auto &vertex : partialPaths.front()) {
        outSolution.emplace_back(vertex);
    }
    return TSPUtils::calculateTargetFunctionValue(tspInstance, outSolution);
}

int TSPGreedyAlgorithms::createNaturalPermutation(const IGraph *tspInstance, std::vector<int> &outSolution) {
    for (int i = 0; i != tspInstance->getVertexCount(); ++i) {
        outSolution.emplace_back(i);
    }
    return TSPUtils::calculateTargetFunctionValue(tspInstance, outSolution);
}