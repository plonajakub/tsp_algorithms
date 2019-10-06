#ifndef PEA_P1_LISTGRAPH_H
#define PEA_P1_LISTGRAPH_H

#include <limits>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "IGraph.h"
#include "MatrixGraph.h"
#include "../Table.h"
#include "../DoublyLinkedList.h"

class MatrixGraph;

// Loops and multiple edges disallowed
class ListGraph : public IGraph {
public:

    explicit ListGraph(const MatrixGraph *mGraph);

    ListGraph(GraphType graphType, int nVertex);

    void addEdge(int startVertexID, int endVertexID, int edgeParameter) override;

    void removeEdge(int startVertexID, int endVertexID) override;

    [[nodiscard]] DoublyLinkedList<int> getVertexSuccessors(int vertexID) const override;

    [[nodiscard]] DoublyLinkedList<int> getVertexPredecessors(int vertexID) const override;

    [[nodiscard]] DoublyLinkedList<int> getVertices() const override;

    [[nodiscard]] int getEdgeParameter(int startVertexID, int endVertexID) const override;

    void setEdgeParameter(int startVertexID, int endVertexID, int parameter) override;

    [[nodiscard]] int getVertexCount() const override;

    [[nodiscard]] int getEdgeCount() const override;

    [[nodiscard]] double getDensity() const override;

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] GraphType getGraphType() const override;

    [[nodiscard]] GraphStructure getGraphStructure() const override;

private:

    void addVertex() override;

    const GraphType TYPE;

    Table<DoublyLinkedList<int>> successorsLists;

    // Weight or flow
    Table<Table<int>> parametersMatrix;

    int edgeCount;

    friend class ListGraphTest;
};

#endif //PEA_P1_LISTGRAPH_H
