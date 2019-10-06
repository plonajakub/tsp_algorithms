#include "MatrixGraphTest.h"

#define pStartInfo(method) cout << "##### MatrixGraphTest::" << (method) << "() start #####" << endl
#define pEndInfo(method) cout << "%%%%% MatrixGraphTest::" << (method) << "() end %%%%%" << endl << endl
#define directed "--------Directed:\n"
#define undirected "--------Undirected:\n"

void MatrixGraphTest::run() {
    pStartInfo("testMatrixGraph");
    testMatrixGraph();
    pEndInfo("testMatrixGraph");

    pStartInfo("testAddEdge");
    testAddEdge();
    pEndInfo("testAddEdge");

    pStartInfo("testRemoveEdge");
    testRemoveEdge();
    pEndInfo("testRemoveEdge");

    pStartInfo("testRemoveEdge");
    testRemoveEdge_vertexID();
    pEndInfo("testRemoveEdge");

    pStartInfo("testGetVertexSuccessors");
    testGetVertexSuccessors();
    pEndInfo("testGetVertexSuccessors");

    pStartInfo("testGetVertexPredecessors");
    testGetVertexPredecessors();
    pEndInfo("testGetVertexPredecessors");

    pStartInfo("testGetEdgeIdFromVertexes");
    testGetEdgeIdFromVertexes();
    pEndInfo("testGetEdgeIdFromVertexes");

    pStartInfo("testGetEdgeParameter");
    testGetEdgeParameter_vertexID();
    pEndInfo("testGetEdgeParameter");

    pStartInfo("testGetEdgeParameter");
    testGetEdgeParameter();
    pEndInfo("testGetEdgeParameter");

    pStartInfo("testGetVertexIdsFromEdge");
    testGetVertexIdsFromEdge();
    pEndInfo("testGetVertexIdsFromEdge");

    pStartInfo("testIsVertexPartOfEdge");
    testIsVertexPartOfEdge();
    pEndInfo("testIsVertexPartOfEdge");

    pStartInfo("testGetVertexCount");
    testGetVertexCount();
    pEndInfo("testGetVertexCount");

    pStartInfo("testGetEdgeCount");
    testGetEdgeCount();
    pEndInfo("testGetEdgeCount");

    pStartInfo("testGetDensity");
    testGetDensity();
    pEndInfo("testGetDensity");

    pStartInfo("testToString");
    testToString();
    pEndInfo("testToString");
}

void MatrixGraphTest::testMatrixGraph() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    assert(mgd.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i)
        assert(mgd.incidenceMatrix[i].getSize() == 0);
    assert(mgd.edgeParameters.getSize() == 0);
    cout << directed << mgd << endl;

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 10);
    assert(mgud.incidenceMatrix.getSize() == 10);
    for (int i = 0; i < 10; ++i)
        assert(mgud.incidenceMatrix[i].getSize() == 0);
    assert(mgud.edgeParameters.getSize() == 0);
    cout << undirected << mgud << endl;
}

void MatrixGraphTest::testAddEdge() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(0, 1, 10);
    assert(mgd.incidenceMatrix[0][0] == 1);
    assert(mgd.incidenceMatrix[1][0] == -1);
    mgd.addEdge(2, 1, 11);
    assert(mgd.incidenceMatrix[2][1] == 1);
    assert(mgd.incidenceMatrix[1][1] == -1);
    mgd.addEdge(2, 3, 12);
    mgd.addEdge(3, 4, 13);

    assert(mgd.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgd.incidenceMatrix[i].getSize() == 4);
    }
    assert(mgd.edgeParameters.getSize() == 4);
    cout << directed << mgd << endl;

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(0, 1, 10);
    assert(mgud.incidenceMatrix[0][0] == 1);
    assert(mgud.incidenceMatrix[1][0] == 1);
    mgud.addEdge(2, 1, 11);
    assert(mgud.incidenceMatrix[2][1] == 1);
    assert(mgud.incidenceMatrix[1][1] == 1);
    mgud.addEdge(2, 3, 12);
    mgud.addEdge(3, 4, 13);

    assert(mgud.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgud.incidenceMatrix[i].getSize() == 4);
    }
    assert(mgud.edgeParameters.getSize() == 4);
    cout << undirected << mgud << endl;
}

void MatrixGraphTest::testRemoveEdge() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(0, 1, 10);
    mgd.addEdge(2, 1, 11);
    mgd.addEdge(2, 3, 12);
    mgd.addEdge(3, 4, 13);
    cout << directed << mgd << endl;

    mgd.removeEdge(0);
    assert(mgd.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgd.incidenceMatrix[i].getSize() == 3);
    }
    assert(mgd.edgeParameters.getSize() == 3);
    cout << directed << mgd << endl;

    mgd.removeEdge(2);
    assert(mgd.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgd.incidenceMatrix[i].getSize() == 2);
    }
    assert(mgd.edgeParameters.getSize() == 2);
    cout << directed << mgd << endl;

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(0, 1, 10);
    mgud.addEdge(2, 1, 11);
    mgud.addEdge(2, 3, 12);
    mgud.addEdge(3, 4, 13);
    cout << undirected << mgud << endl;

    mgud.removeEdge(0);
    assert(mgud.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgud.incidenceMatrix[i].getSize() == 3);
    }
    assert(mgud.edgeParameters.getSize() == 3);
    cout << undirected << mgud << endl;

    mgud.removeEdge(2);
    assert(mgud.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgud.incidenceMatrix[i].getSize() == 2);
    }
    assert(mgud.edgeParameters.getSize() == 2);
    cout << undirected << mgud << endl;
}

void MatrixGraphTest::testRemoveEdge_vertexID() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(0, 1, 10);
    mgd.addEdge(0, 2, 11);
    mgd.addEdge(1, 0, 12);
    mgd.addEdge(1, 2, 13);
    mgd.addEdge(1, 4, 14);
    cout << directed << mgd << endl;

    mgd.removeEdge(0, 1);
    assert(mgd.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgd.incidenceMatrix[i].getSize() == 4);
    }
    assert(mgd.edgeParameters.getSize() == 4);
    cout << directed << mgd << endl;

    mgd.removeEdge(1, 0);
    assert(mgd.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgd.incidenceMatrix[i].getSize() == 3);
    }
    assert(mgd.edgeParameters.getSize() == 3);
    cout << directed << mgd << endl;

    mgd.removeEdge(1, 4);
    assert(mgd.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgd.incidenceMatrix[i].getSize() == 2);
    }
    assert(mgd.edgeParameters.getSize() == 2);
    cout << directed << mgd << endl;


    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(0, 1, 10);
    mgud.addEdge(0, 2, 12);
    mgud.addEdge(1, 2, 11);
    mgud.addEdge(1, 3, 14);
    mgud.addEdge(3, 0, 13);
    cout << undirected << mgud << endl;

    mgud.removeEdge(0, 1);
    assert(mgud.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgud.incidenceMatrix[i].getSize() == 4);
    }
    assert(mgud.edgeParameters.getSize() == 4);
    cout << undirected << mgud << endl;

    mgud.removeEdge(1, 3);
    assert(mgud.incidenceMatrix.getSize() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(mgud.incidenceMatrix[i].getSize() == 3);
    }
    assert(mgud.edgeParameters.getSize() == 3);
    cout << undirected << mgud << endl;
}

void MatrixGraphTest::testGetVertexSuccessors() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(0, 1, 10);
    mgd.addEdge(0, 3, 11);
    mgd.addEdge(0, 4, 12);
    mgd.addEdge(1, 3, 15);
    mgd.addEdge(2, 4, 16);
    mgd.addEdge(3, 4, 17);
    cout << directed << mgd << endl;

    DoublyLinkedList<int> successors = mgd.getVertexSuccessors(0);
    DoublyLinkedList<int>::Iterator it = successors.getIterator();
    assert(it.getData() == 1);
    ++it;
    assert(it.getData() == 3);
    ++it;
    assert(it.getData() == 4);
    ++it;
    assert(it == successors.getEndIt());

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(0, 1, 10);
    mgud.addEdge(0, 2, 15);
    mgud.addEdge(2, 3, 16);
    mgud.addEdge(3, 4, 17);
    cout << undirected << mgud << endl;

    DoublyLinkedList<int> usuccessors = mgud.getVertexSuccessors(0);
    DoublyLinkedList<int>::Iterator uit = usuccessors.getIterator();
    assert(uit.getData() == 1);
    ++uit;
    assert(uit.getData() == 2);
    ++uit;
    assert(uit == usuccessors.getEndIt());
}

void MatrixGraphTest::testGetVertexPredecessors() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(0, 1, 15);
    mgd.addEdge(0, 2, 16);
    mgd.addEdge(1, 0, 10);
    mgd.addEdge(3, 0, 11);
    mgd.addEdge(3, 2, 18);
    mgd.addEdge(4, 0, 12);
    mgd.addEdge(4, 3, 17);
    cout << directed << mgd << endl;

    DoublyLinkedList<int> predecessors = mgd.getVertexPredecessors(0);
    DoublyLinkedList<int>::Iterator it = predecessors.getIterator();
    assert(it.getData() == 1);
    ++it;
    assert(it.getData() == 3);
    ++it;
    assert(it.getData() == 4);
    ++it;
    assert(it == predecessors.getEndIt());

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(0, 1, 15);
    mgud.addEdge(0, 2, 16);
    mgud.addEdge(1, 3, 10);
    mgud.addEdge(4, 3, 17);
    cout << undirected << mgud << endl;

    DoublyLinkedList<int> upredecessors = mgud.getVertexPredecessors(0);
    DoublyLinkedList<int>::Iterator uit = upredecessors.getIterator();
    assert(uit.getData() == 1);
    ++uit;
    assert(uit.getData() == 2);
    ++uit;
    assert(uit == upredecessors.getEndIt());
}

void MatrixGraphTest::testGetEdgeIdFromVertexes() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(0, 1, 15);
    mgd.addEdge(1, 0, 10);
    mgd.addEdge(3, 0, 11);
    mgd.addEdge(3, 2, 18);
    mgd.addEdge(4, 0, 12);
    cout << directed << mgd << endl;

    int deID = mgd.getEdgeIdFromVertexes(3, 0);
    assert(deID == 2);

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(0, 1, 15);
    mgud.addEdge(0, 2, 18);
    mgud.addEdge(1, 4, 10);
    mgud.addEdge(1, 2, 16);
    mgud.addEdge(4, 3, 17);
    cout << undirected << mgud << endl;

    int ueID = mgud.getEdgeIdFromVertexes(4, 3);
    assert(ueID == 4);
}

void MatrixGraphTest::testGetEdgeParameter_vertexID() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(0, 1, 15);
    mgd.addEdge(1, 0, 10);
    mgd.addEdge(3, 0, 11);
    mgd.addEdge(3, 2, 18);
    mgd.addEdge(4, 0, 12);
    cout << directed << mgd << endl;

    int deParam = mgd.getEdgeParameter(0, 1);
    assert(deParam == 15);

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(0, 1, 15);
    mgud.addEdge(0, 2, 18);
    mgud.addEdge(0, 3, 16);
    mgud.addEdge(1, 2, 10);
    mgud.addEdge(4, 3, 17);
    cout << undirected << mgud << endl;

    int ueParam = mgud.getEdgeParameter(0, 2);
    assert(ueParam == 18);
}

void MatrixGraphTest::testGetEdgeParameter() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(1, 0, 10);
    mgd.addEdge(3, 0, 11);
    mgd.addEdge(3, 2, 18);
    mgd.addEdge(4, 3, 12);
    mgd.addEdge(0, 1, 15);
    cout << directed << mgd << endl;

    assert(mgd.getEdgeParameter(3) == 12);

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(1, 2, 10);
    mgud.addEdge(0, 1, 15);
    mgud.addEdge(0, 3, 18);
    mgud.addEdge(0, 2, 16);
    mgud.addEdge(4, 3, 17);
    cout << undirected << mgud << endl;

    assert(mgud.getEdgeParameter(3) == 16);
}

void MatrixGraphTest::testGetVertexIdsFromEdge() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(1, 0, 10);
    mgd.addEdge(3, 0, 11);
    mgd.addEdge(3, 2, 18);
    mgd.addEdge(4, 0, 12);
    mgd.addEdge(3, 4, 19);
    mgd.addEdge(0, 1, 15);
    cout << directed << mgd << endl;

    Table<int> dIds = mgd.getVertexIdsFromEdge(2);
    assert(dIds[0] == 3 && dIds[1] == 2);
    assert(dIds.getSize() == 2);

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(1, 2, 10);
    mgud.addEdge(0, 1, 15);
    mgud.addEdge(0, 2, 18);
    mgud.addEdge(0, 3, 16);
    mgud.addEdge(4, 3, 17);
    cout << undirected << mgud << endl;

    Table<int> uIds = mgud.getVertexIdsFromEdge(2);
    assert(uIds[0] == 0 && uIds[1] == 2);
    assert(uIds.getSize() == 2);
}

void MatrixGraphTest::testIsVertexPartOfEdge() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(1, 0, 10);
    mgd.addEdge(3, 0, 11);
    mgd.addEdge(3, 2, 18);
    mgd.addEdge(4, 0, 12);
    mgd.addEdge(3, 4, 19);
    mgd.addEdge(0, 1, 15);
    cout << directed << mgd << endl;

    assert(!mgd.isVertexPartOfEdge(3, 0));
    assert(mgd.isVertexPartOfEdge(3, 1));

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(1, 2, 10);
    mgud.addEdge(0, 1, 15);
    mgud.addEdge(0, 2, 18);
    mgud.addEdge(0, 3, 16);
    mgud.addEdge(4, 3, 17);
    cout << undirected << mgud << endl;

    assert(!mgud.isVertexPartOfEdge(2, 1));
    assert(mgud.isVertexPartOfEdge(3, 4));
}

void MatrixGraphTest::testGetVertexCount() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    assert(mgd.getVertexCount() == 5);

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    assert(mgud.getVertexCount() == 5);
}

void MatrixGraphTest::testGetEdgeCount() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(1, 0, 10);
    mgd.addEdge(3, 0, 11);
    mgd.addEdge(3, 2, 18);
    mgd.addEdge(4, 0, 12);
    mgd.addEdge(3, 4, 19);
    mgd.addEdge(0, 1, 15);
    cout << directed << mgd << endl;

    assert(mgd.getEdgeCount() == 6);

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(1, 2, 10);
    mgud.addEdge(0, 1, 15);
    mgud.addEdge(0, 2, 18);
    mgud.addEdge(0, 3, 16);
    mgud.addEdge(4, 3, 17);
    cout << undirected << mgud << endl;

    assert(mgud.getEdgeCount() == 5);
}

void MatrixGraphTest::testGetDensity() {
    MatrixGraph mgd(MatrixGraph::GraphType::Directed, 5);
    mgd.addEdge(1, 0, 10);
    mgd.addEdge(3, 0, 11);
    mgd.addEdge(3, 2, 18);
    mgd.addEdge(4, 0, 12);
    mgd.addEdge(3, 4, 19);
    mgd.addEdge(0, 1, 15);
    cout << directed << mgd << endl;

    assert(mgd.getDensity() - static_cast<double>(6) / (5 * 4) < 0.000001);

    MatrixGraph mgud(MatrixGraph::GraphType::Undirected, 5);
    mgud.addEdge(1, 2, 10);
    mgud.addEdge(0, 1, 15);
    mgud.addEdge(0, 2, 18);
    mgud.addEdge(0, 3, 16);
    mgud.addEdge(4, 3, 17);
    cout << undirected << mgud << endl;

    assert(mgud.getDensity() - static_cast<double>(5)/((5 * 4) / 2) < 0.000001);
}

void MatrixGraphTest::testToString() {
    MatrixGraph mg(MatrixGraph::GraphType::Directed, 4);
    mg.addEdge(0, 1, 5);
    mg.addEdge(0, 2, 10);
    mg.addEdge(1, 2, 15);
    mg.addEdge(3, 2, 20);
    mg.addEdge(2, 3, 25);
    cout << mg.toString() << endl;
}


