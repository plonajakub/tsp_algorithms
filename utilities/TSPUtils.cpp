#include "TSPUtils.h"


std::string TSPUtils::loadTSPInstance(IGraph **pGraph, const std::string &path, TSPUtils::TSPType tspType) {
    std::fstream file("../input_data/" + path);
    std::string instanceName;
    if (!file.is_open()) {
        throw std::invalid_argument("File with path /input_data/" + path + " does not exist.");
    }

    int nVertex, edgeParameter;
    file >> instanceName >> nVertex;

    if (tspType == TSPUtils::TSPType::Asymmetric) {
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

TSPUtils::TSPType TSPUtils::getTSPType(const std::string &path) {
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

int TSPUtils::calculateTargetFunctionValue(const IGraph *tspInstance, const std::vector<int> &vertexPermutation) {
    int sum = 0;
    int permutationSize = vertexPermutation.size();
    if (permutationSize == 0 || permutationSize == 1) {
        return sum;
    }

    auto it = vertexPermutation.begin();
    int vStart = *it;
    int v1 = vStart;
    ++it;
    int v2 = -1;
    for (; it != vertexPermutation.end(); ++it) {
        v2 = *it;
        sum += tspInstance->getEdgeParameter(v1, v2);
        v1 = v2;
    }
    sum += tspInstance->getEdgeParameter(v2, vStart);
    return sum;
}

int TSPUtils::calculateTargetFunctionValue(const IGraph *tspInstance, int fixedStartVertex,
                                           const std::vector<int> &vertexPermutation) {
    int sum = 0;
    int permutationSize = vertexPermutation.size();
    if (permutationSize == 0) {
        return sum;
    }

    int v1 = fixedStartVertex;
    int v2 = -1;
    for (int i = 0; i != permutationSize; ++i) {
        v2 = vertexPermutation[i];
        sum += tspInstance->getEdgeParameter(v1, v2);
        v1 = v2;
    }
    sum += tspInstance->getEdgeParameter(v2, fixedStartVertex);
    return sum;
}

int TSPUtils::calculateTargetFunctionValue(const IGraph *tspInstance, const DoublyLinkedList<int> &vertexPermutation) {
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

int TSPUtils::getRand(int leftLimit, int rightLimit) {
    return leftLimit + rand() % (rightLimit - leftLimit);
}

std::map<std::string, int> TSPUtils::loadTSPSolutionValues(const std::string &file) {
    std::map<std::string, int> solutions;

    std::ifstream solutionFile("../input_data/" + file);
    if (!solutionFile.is_open()) {
        throw std::invalid_argument("File " + file + "cannot be opened");
    }

    std::string fileName, instanceName;
    int solutionValue;
    while (!solutionFile.eof()) {
        solutionFile >> fileName >> instanceName;
        solutionFile >> solutionValue;
        solutions.insert({fileName, solutionValue});
    }
    solutionFile.close();
    return solutions;
}

