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

void TSPUtils::testAlgorithm(const std::map<std::string, std::vector<std::string>> &instanceFiles,
                             int (*tspAlgorithm)(const IGraph *), const std::string &testName) {
    std::cout << std::string(10, '-') << "Test \"" + testName + "\"" + " started" << std::string(10, '-') << std::endl;
    IGraph *tspInstance = nullptr;
    std::map<std::string, int> solutions;
    int solution;
    for (const auto &pair : instanceFiles) {
        if (pair.second.empty()) {
            continue;
        }
        solutions = TSPUtils::loadTSPSolutionValues(pair.first + "/" + pair.second[0]);
        for (int i = 1; i != pair.second.size(); ++i) {
            std::cout << "Testing instance " + pair.first + "/" + pair.second[i] + "...";
            delete tspInstance;
            TSPUtils::loadTSPInstance(&tspInstance, pair.first + "/" + pair.second[i]);
            solution = tspAlgorithm(tspInstance);
            if (solution == solutions.at(pair.second[i].substr(0, pair.second[i].find('.')))) {
                std::cout << "SUCCESS";
            } else {
                std::cout << "FAIL" << " [AR: " << solution << "]";
            }
            std::cout  << std::endl;
        }
    }
    delete tspInstance;
    std::cout << std::string(10, '-') << "Test \"" + testName + "\"" + " finished" << std::string(10, '-') << std::endl;
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

void TSPUtils::performTests() {
    std::map<std::string, std::vector<std::string>> fileGroups;
    std::vector<std::string> filePaths;

    // ATSP
    filePaths.emplace_back("best.txt");
    filePaths.emplace_back("data17.txt");
//    filePaths.emplace_back("data34.txt");
//    filePaths.emplace_back("data36.txt");
//    filePaths.emplace_back("data39.txt");
//    filePaths.emplace_back("data43.txt");
//    filePaths.emplace_back("data45.txt");
//    filePaths.emplace_back("data48.txt");
//    filePaths.emplace_back("data53.txt");
//    filePaths.emplace_back("data56.txt");
//    filePaths.emplace_back("data65txt");
//    filePaths.emplace_back("data70.txt");
//    filePaths.emplace_back("data71.txt");
//    filePaths.emplace_back("data100.txt");
//    filePaths.emplace_back("data171.txt");
//    filePaths.emplace_back("data323.txt");
//    filePaths.emplace_back("data358.txt");
//    filePaths.emplace_back("data403.txt");
//    filePaths.emplace_back("data443.txt");

    fileGroups.insert({"ATSP", filePaths});

    filePaths.clear();
    // SMALL
    filePaths.emplace_back("opt.txt");
    filePaths.emplace_back("data10.txt");
//    filePaths.emplace_back("data11.txt");
    filePaths.emplace_back("data12.txt");
//    filePaths.emplace_back("data13.txt");
//    filePaths.emplace_back("data14.txt");
//    filePaths.emplace_back("data15.txt");
//    filePaths.emplace_back("data16.txt");
    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data18.txt");

    fileGroups.insert({"SMALL", filePaths});

    filePaths.clear();
    //TSP
    filePaths.emplace_back("best.txt");
//    filePaths.emplace_back("data17.txt");
    filePaths.emplace_back("data21.txt");
    filePaths.emplace_back("data24.txt");
//    filePaths.emplace_back("data26.txt");
//    filePaths.emplace_back("data29.txt");
//    filePaths.emplace_back("data42.txt");
//    filePaths.emplace_back("data58.txt");
//    filePaths.emplace_back("data120.txt");

    fileGroups.insert({"TSP", filePaths});

//    TSPUtils::testAlgorithm(fileGroups, TSPAlgorithms::bruteForce, "bruteForce");
    TSPUtils::testAlgorithm(fileGroups, TSPAlgorithms::dynamicProgrammingHeldKarp, "dynamicProgrammingHeldKarp");
}
