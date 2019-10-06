#ifndef PEA_P1_IGRAPH_H
#define PEA_P1_IGRAPH_H

#include <iostream>

#include "../DoublyLinkedList.h"
#include "misc/Edge.h"

class IGraph {
public:

    enum GraphType {
        Directed, Undirected
    };

    enum GraphStructure {
        IncidenceMatrix, AdjacencyList
    };

    virtual ~IGraph() = default;

    virtual void addEdge(int startVertexID, int endVertexID, int edgeParameter) = 0;

    virtual void removeEdge(int startVertexID, int endVertexID) = 0;

    [[nodiscard]] virtual DoublyLinkedList<int> getVertexSuccessors(int vertexID) const = 0;

    [[nodiscard]] virtual DoublyLinkedList<int> getVertexPredecessors(int vertexID) const = 0;

    [[nodiscard]] virtual DoublyLinkedList<int> getVertices() const = 0;

    [[nodiscard]] virtual int getEdgeParameter(int startVertexID, int endVertexID) const = 0;

    virtual void setEdgeParameter(int startVertexID, int endVertexID, int parameter) = 0;

    [[nodiscard]] virtual int getVertexCount() const = 0;

    [[nodiscard]] virtual int getEdgeCount() const = 0;

    [[nodiscard]] virtual double getDensity() const = 0;

    [[nodiscard]] virtual std::string toString() const = 0;

    [[nodiscard]] virtual GraphType getGraphType() const = 0;

    [[nodiscard]] virtual GraphStructure getGraphStructure() const = 0;

private:

    virtual void addVertex() = 0;
};

std::ostream &operator<<(std::ostream &ostr, const IGraph &graph);

#endif //PEA_P1_IGRAPH_H
