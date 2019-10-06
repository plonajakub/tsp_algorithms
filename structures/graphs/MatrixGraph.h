#ifndef PEA_P1_MATRIXGRAPH_H
#define PEA_P1_MATRIXGRAPH_H

#include <limits>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "IGraph.h"
#include "ListGraph.h"
#include "../Table.h"
#include "../DoublyLinkedList.h"
#include "misc/Edge.h"

class ListGraph;

class MatrixGraph : public IGraph {
public:

    explicit MatrixGraph(const ListGraph *lGraph);

    MatrixGraph(GraphType graphType, int nVertex);

    void addEdge(int startVertexID, int endVertexID, int edgeParameter) override;

    void removeEdge(int edgeID);

    void removeEdge(int startVertexID, int endVertexID) override;

    [[nodiscard]] DoublyLinkedList<int> getVertices() const override;

    [[nodiscard]] DoublyLinkedList<int> getVertexSuccessors(int vertexID) const override;

    [[nodiscard]] DoublyLinkedList<int> getVertexPredecessors(int vertexID) const override;

    [[nodiscard]] int getEdgeParameter(int startVertexID, int endVertexID) const override;

    void setEdgeParameter(int startVertexID, int endVertexID, int parameter) override;

    [[nodiscard]] int getEdgeParameter(int edgeID) const;

    // Table[0]: startVertexID
    // Table[1]: endVertexID
    [[nodiscard]] Table<int> getVertexIdsFromEdge(int edgeID) const;

    // Returned list is sorted
    [[nodiscard]] int getEdgeIdFromVertexes(int startVertexID, int endVertexID) const;

    [[nodiscard]] bool isVertexPartOfEdge(int vertexID, int edgeID) const;

    [[nodiscard]] int getVertexCount() const override;

    [[nodiscard]] int getEdgeCount() const override;

    [[nodiscard]] double getDensity() const override;

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] GraphType getGraphType() const override;

    [[nodiscard]] GraphStructure getGraphStructure() const override;

    static const int EDGE_NOT_PRESENT = -2;

    static const int VERTEX_NOT_PRESENT = -1;

private:

    void addVertex() override;

    const GraphType TYPE;

    Table<Table<int>> incidenceMatrix;

    // Weight or flow
    Table<int> edgeParameters;

    friend class MatrixGraphTest;
};


#endif //PEA_P1_MATRIXGRAPH_H
