#include "ListGraph.h"

ListGraph::ListGraph(ListGraph::GraphType graphType, int nVertex) : TYPE(graphType), edgeCount(0) {
    if (nVertex < 1) {
        throw std::invalid_argument("ListGraph() error: graph must have at least one vertex");
    }
    for (int i = 0; i < nVertex; ++i) {
        this->addVertex();
    }
}

ListGraph::ListGraph(const MatrixGraph *mGraph) : TYPE(mGraph->getGraphType()), edgeCount(0) {
    auto vertices = mGraph->getVertices();
    for (int i = 0; i < vertices.getSize(); ++i) {
        this->addVertex();
    }
    DoublyLinkedList<int> successors;
    for (auto vIt = vertices.getIterator(); vIt != vertices.getEndIt(); ++vIt) {
        successors = mGraph->getVertexSuccessors(vIt.getData());
        for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
            try {
                this->addEdge(vIt.getData(), sIt.getData(), mGraph->getEdgeParameter(vIt.getData(), sIt.getData()));
            } catch (const std::invalid_argument &e) {
                // Skip already added edge
            }
        }
    }
}

void ListGraph::addVertex() {
    successorsLists.insertAtEnd(DoublyLinkedList<int>());

    parametersMatrix.insertAtEnd(Table<int>());
    int vertexCount = this->getVertexCount();
    int lastVertexIdx = vertexCount - 1;
    for (int i = 0; i < vertexCount - 1; ++i) {
        parametersMatrix[lastVertexIdx].insertAtEnd(std::numeric_limits<int>::max());
    }
    for (int i = 0; i < vertexCount; ++i) {
        parametersMatrix[i].insertAtEnd(std::numeric_limits<int>::max());
    }
}

void ListGraph::addEdge(int startVertexID, int endVertexID, int edgeParameter) {
    if (startVertexID < 0 || startVertexID >= this->getVertexCount() || endVertexID < 0 ||
        endVertexID >= this->getVertexCount()) {
        throw std::invalid_argument("addEdge() error: invalid vertex's index");
    }
    if (startVertexID == endVertexID) {
        throw std::invalid_argument("addEdge() error: loops are disallowed");
    }
    // Multiple edges are not represented in this graph's structure
    if (this->getEdgeParameter(startVertexID, endVertexID) != std::numeric_limits<int>::max()) {
        throw std::invalid_argument("addEdge() error: multiple edges are disallowed");
    }

    successorsLists[startVertexID].insertAtEnd(endVertexID);
    parametersMatrix[startVertexID][endVertexID] = edgeParameter;
    if (this->TYPE == GraphType::Undirected) {
        successorsLists[endVertexID].insertAtEnd(startVertexID);
        parametersMatrix[endVertexID][startVertexID] = edgeParameter;
    }
    ++edgeCount;
}

void ListGraph::removeEdge(int startVertexID, int endVertexID) {
    if (startVertexID < 0 || startVertexID >= this->getVertexCount() || endVertexID < 0 ||
        endVertexID >= this->getVertexCount()) {
        throw std::invalid_argument("removeEdge() error: wrong vertex's index");
    }
    if (this->getEdgeParameter(startVertexID, endVertexID) == std::numeric_limits<int>::max()) {
        throw std::invalid_argument("addEdge() error: described edge does not exist");
    }

    successorsLists[startVertexID].removeByValue(endVertexID);
    parametersMatrix[startVertexID][endVertexID] = std::numeric_limits<int>::max();
    if (this->TYPE == GraphType::Undirected) {
        successorsLists[endVertexID].removeByValue(startVertexID);
        parametersMatrix[endVertexID][startVertexID] = std::numeric_limits<int>::max();
    }
    --edgeCount;
}

DoublyLinkedList<int> ListGraph::getVertices() const {
    DoublyLinkedList<int> vertexes;
    int vertexCount = this->getVertexCount();
    for (int i = 0; i < vertexCount; ++i) {
        vertexes.insertAtEnd(i);
    }
    return vertexes;
}

DoublyLinkedList<int> ListGraph::getVertexSuccessors(int vertexID) const {
    return successorsLists[vertexID];
}

DoublyLinkedList<int> ListGraph::getVertexPredecessors(int vertexID) const {
    if (this->TYPE == GraphType::Directed) {
        DoublyLinkedList<int> predecessors;
        int vertexCount = this->getVertexCount();
        for (int i = 0; i < vertexCount; ++i) {
            if (successorsLists[i].contains(vertexID)) {
                predecessors.insertAtEnd(i);
            }
        }
        return predecessors;
    } else {
        return successorsLists[vertexID];
    }
}

int ListGraph::getEdgeParameter(int startVertexID, int endVertexID) const {
    return parametersMatrix[startVertexID][endVertexID];
}

void ListGraph::setEdgeParameter(int startVertexID, int endVertexID, int parameter) {
    parametersMatrix[startVertexID][endVertexID] = parameter;
}


int ListGraph::getVertexCount() const {
    return successorsLists.getSize();
}

int ListGraph::getEdgeCount() const {
    return edgeCount;
}

double ListGraph::getDensity() const {
    int vertexCount = this->getVertexCount();
    if (this->TYPE == GraphType::Directed) {
        return static_cast<double>(edgeCount) / (vertexCount * (vertexCount - 1));
    } else {
        return static_cast<double>(edgeCount) / ((vertexCount * (vertexCount - 1)) / 2);
    }
}

std::string ListGraph::toString() const {
    const int numberFieldLen = 3;
    std::stringstream graphString;
    int vertexCount = this->getVertexCount();
    graphString << std::endl << "Successors lists:" << std::endl;
    graphString << std::setw(2) << "V" << std::endl;
    for (int i = 0; i < vertexCount; ++i) {
        graphString << std::setw(2) << i << ": ";
        graphString << successorsLists[i] << std::endl;
    }
    graphString << std::endl;

    graphString << "Parameter matrix:" << std::endl;
    graphString << "V\\V";
    for (int j = 0; j < vertexCount; ++j) {
        graphString << std::setw(numberFieldLen) << j << ',';
    }
    graphString << std::endl;
    for (int i = 0; i < vertexCount; ++i) {
        graphString << std::setw(2) << std::to_string(i) << "[";
        for (int j = 0; j < vertexCount - 1; ++j) {
            graphString << std::setw(numberFieldLen) <<
                        ((parametersMatrix[i][j] == std::numeric_limits<int>::max()) ? "*" : std::to_string(
                                parametersMatrix[i][j]))
                        << ',';
        }
        graphString << std::setw(numberFieldLen) <<
                    ((parametersMatrix[i][vertexCount - 1] == std::numeric_limits<int>::max()) ? "*" : std::to_string(
                            parametersMatrix[i][vertexCount - 1]));
        graphString << ']' << std::endl;
    }
    return graphString.str();
}

IGraph::GraphType ListGraph::getGraphType() const {
    return TYPE;
}

IGraph::GraphStructure ListGraph::getGraphStructure() const {
    return AdjacencyList;
}
