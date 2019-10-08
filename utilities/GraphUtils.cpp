#include "GraphUtils.h"


std::string GraphUtils::loadTSPInstance(IGraph **pGraph, GraphUtils::TSPType tspType, const std::string &path) {
    std::fstream file("../input_data/" + path);
    std::string instanceName;
    if (!file.is_open()) {
        std::cout << "Error during opening the file: " << path << std::endl;
        return instanceName;
    }

    int nVertex, edgeParameter;
    file >> instanceName >> nVertex;

    if (tspType == GraphUtils::TSPType::Asymetric) {
        *pGraph = new ListGraph(IGraph::GraphType::Directed, nVertex);
        for (int i = 0; i < nVertex; ++i) {
            for (int j = 0; j < nVertex; ++j) {
                file >> edgeParameter;
                try {
                    (*pGraph)->addEdge(i, j, edgeParameter);
                } catch (const std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    } else {
        *pGraph = new ListGraph(IGraph::GraphType::Undirected, nVertex);
        for (int i = 0; i < nVertex; ++i) {
            for (int j = 0; j < nVertex; ++j) {
                file >> edgeParameter;
                if (i > j) {
                    continue;
                }
                try {
                    (*pGraph)->addEdge(i, j, edgeParameter);
                } catch (const std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
    file.close();
    return  instanceName;
}

int GraphUtils::getRand(int leftLimit, int rightLimit) {
    return leftLimit + rand() % (rightLimit - leftLimit);
}

int GraphUtils::getTargetFunctionValue(const IGraph *tspInstance, const DoublyLinkedList<int> &vertexPermutation) {
    int sum = 0;
    int permutationSize = vertexPermutation.getSize();
    if (permutationSize == 0 || permutationSize == 1) {
        return sum;
    }

    auto it = vertexPermutation.getIterator();
    int vStart = it.getData();
    int v1 = vStart;
    ++it;
    int v2 = -1;
    for (; it != vertexPermutation.getEndIt(); ++it) {
        v2 = it.getData();
        sum += tspInstance->getEdgeParameter(v1, v2);
        v1 = v2;
    }
    sum += tspInstance->getEdgeParameter(v2, vStart);
    return sum;
}
