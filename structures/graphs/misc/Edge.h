#ifndef PEA_P1_EDGE_H
#define PEA_P1_EDGE_H


class Edge {

public:
    Edge() = default;

    Edge(int edgeID, int parameter) : edgeID(edgeID), parameter(parameter) {
        startVertexID = -1;
        endVertexID = -1;
    }

    Edge(int startVertexID, int endVertexID, int parameter) : startVertexID(startVertexID), endVertexID(endVertexID),
                                                              parameter(parameter) {
        edgeID = -1;
    }

    bool operator==(const Edge &other) const {
        return edgeID == other.edgeID && parameter == other.parameter && startVertexID == other.startVertexID &&
               endVertexID == other.endVertexID;
    }

    bool operator!=(const Edge &other) const {
        return edgeID != other.edgeID || parameter != other.parameter || startVertexID != other.startVertexID ||
               endVertexID != other.endVertexID;
    }

    int startVertexID;
    int endVertexID;
    int edgeID;
    int parameter;
};


#endif //PEA_P1_EDGE_H
