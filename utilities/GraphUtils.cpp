#include "GraphUtils.h"


std::string GraphUtils::loadTSPInstance(IGraph **pGraph, GraphUtils::TSPType tspType, const std::string &path) {
    std::fstream file("../input_data/" + path);
    std::string instanceName;
    if (!file.is_open()) {
        throw std::invalid_argument("File with path /input_data/" + path + " does not exist.");
    }

    int nVertex, edgeParameter;
    file >> instanceName >> nVertex;

    if (tspType == GraphUtils::TSPType::Asymmetric) {
        *pGraph = new ListGraph(IGraph::GraphType::Directed, nVertex);
        for (int i = 0; i < nVertex; ++i) {
            for (int j = 0; j < nVertex; ++j) {
                file >> edgeParameter;
                if (i == j) {
                    continue;
                }
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
                if (i >= j) {
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
    return instanceName;
}

GraphUtils::TSPType GraphUtils::getTSPType(const std::string &path) {
    std::fstream file("../input_data/" + path);
    if (!file.is_open()) {
        throw std::invalid_argument("File with path /input_data/" + path + " does not exist.");
    }

    std::string instanceName;
    int nVertex;
    file >> instanceName >> nVertex;

    Table<Table<int>> instance;
    int edgeValue;
    for (int i = 0; i < nVertex; ++i) {
        instance.insertAtEnd(Table<int>());
        for (int j = 0; j < nVertex; ++j) {
            file >> edgeValue;
            instance[i].insertAtEnd(edgeValue);
        }
    }
    file.close();

    if (instance.getSize() != nVertex) {
        throw std::logic_error("Error: provided data does not represent an instance of TSP");
    }
    for (int i = 0; i < instance.getSize(); ++i) {
        if (instance[i].getSize() != nVertex) {
            throw std::logic_error("Error: provided data does not represent an instance of TSP");
        }
    }
    for (int i = 0; i < instance.getSize(); ++i) {
        if (instance[i][i] != -1) {
            throw std::logic_error("Error: provided data does not represent an instance of TSP");
        }
    }

    for (int i = 0; i < nVertex; ++i) {
        for (int j = i + 1; j < nVertex; ++j) {
            if (instance[i][j] != instance[j][i]) {
                return TSPType::Asymmetric;
            }
        }
    }
    return TSPType::Symmetric;
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

int GraphUtils::getRand(int leftLimit, int rightLimit) {
    return leftLimit + rand() % (rightLimit - leftLimit);
}
