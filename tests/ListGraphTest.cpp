#include "ListGraphTest.h"

#define pStartInfo(method) cout << "##### ListGraphTest::" << (method) << "() start #####" << endl
#define pEndInfo(method) cout << "%%%%% ListGraphTest::" << (method) << "() end %%%%%" << endl << endl
#define directed "--------Directed:\n"
#define undirected "--------Undirected:\n"

void ListGraphTest::run() {
    pStartInfo("testListGraph");
    testListGraph();
    pEndInfo("testListGraph");

    pStartInfo("testAddEdge");
    testAddEdge();
    pEndInfo("testAddEdge");

    pStartInfo("testRemoveEdge");
    testRemoveEdge();
    pEndInfo("testRemoveEdge");

    pStartInfo("testGetVertexSuccessors");
    testGetVertexSuccessors();
    pEndInfo("testGetVertexSuccessors");

    pStartInfo("testGetVertexPredecessors");
    testGetVertexPredecessors();
    pEndInfo("testGetVertexPredecessors");

    pStartInfo("testGetEdgeParameter");
    testGetEdgeParameter();
    pEndInfo("testGetEdgeParameter");

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

void ListGraphTest::testListGraph() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    assert(lgd.successorsLists.getSize() == 5);
    assert(lgd.parametersMatrix.getSize() == 5);
    assert(lgd.edgeCount == 0);
    cout << directed << endl;
    cout << lgd << endl;

    ListGraph lgud(ListGraph::GraphType::Undirected,
    5);
    assert(lgud.successorsLists.getSize() == 5);
    assert(lgud.parametersMatrix.getSize() == 5);
    assert(lgud.edgeCount == 0);
    cout << undirected << endl;
    cout << lgud << endl;
}

void ListGraphTest::testAddEdge() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    lgd.addEdge(0, 3, 5);
    lgd.addEdge(3, 0, 10);
    lgd.addEdge(0, 1, 15);
    lgd.addEdge(2, 4, 20);
    lgd.addEdge(0, 4, 25);
    assert(lgd.successorsLists[0].getSize() == 3);
    assert(lgd.successorsLists[1].getSize() == 0);
    assert(lgd.successorsLists[2].getSize() == 1);
    assert(lgd.successorsLists[3].getSize() == 1);
    assert(lgd.successorsLists[4].getSize() == 0);
    assert(lgd.edgeCount == 5);
    cout << directed << endl;
    cout << lgd << endl;

    ListGraph lgud(ListGraph::GraphType::Undirected,
    5);
    lgud.addEdge(0, 3, 5);
    lgud.addEdge(3, 2, 10);
    lgud.addEdge(0, 1, 15);
    lgud.addEdge(2, 4, 20);
    lgud.addEdge(0, 4, 25);
    assert(lgud.successorsLists[0].getSize() == 3);
    assert(lgud.successorsLists[1].getSize() == 1);
    assert(lgud.successorsLists[2].getSize() == 2);
    assert(lgud.successorsLists[3].getSize() == 2);
    assert(lgud.successorsLists[4].getSize() == 2);
    assert(lgud.edgeCount == 5);
    cout << undirected << endl;
    cout << lgud << endl;
}

void ListGraphTest::testRemoveEdge() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    lgd.addEdge(0, 3, 5);
    lgd.addEdge(3, 0, 10);
    lgd.addEdge(0, 1, 15);
    lgd.addEdge(2, 4, 20);
    lgd.addEdge(0, 4, 25);

    lgd.removeEdge(0, 3);
    assert(lgd.successorsLists[0].getSize() == 2);
    assert(lgd.successorsLists[1].getSize() == 0);
    assert(lgd.successorsLists[2].getSize() == 1);
    assert(lgd.successorsLists[3].getSize() == 1);
    assert(lgd.successorsLists[4].getSize() == 0);
    assert(lgd.edgeCount == 4);
    cout << directed << endl;
    cout << lgd << endl;

    lgd.removeEdge(0, 1);
    assert(lgd.successorsLists[0].getSize() == 1);
    assert(lgd.successorsLists[1].getSize() == 0);
    assert(lgd.successorsLists[2].getSize() == 1);
    assert(lgd.successorsLists[3].getSize() == 1);
    assert(lgd.successorsLists[4].getSize() == 0);
    assert(lgd.edgeCount == 3);
    cout << directed << endl;
    cout << lgd << endl;

    lgd.removeEdge(3, 0);
    lgd.removeEdge(2, 4);
    lgd.removeEdge(0, 4);
    assert(lgd.successorsLists[0].getSize() == 0);
    assert(lgd.successorsLists[1].getSize() == 0);
    assert(lgd.successorsLists[2].getSize() == 0);
    assert(lgd.successorsLists[3].getSize() == 0);
    assert(lgd.successorsLists[4].getSize() == 0);
    assert(lgd.edgeCount == 0);
    cout << directed << endl;
    cout << lgd << endl;

    ListGraph lgud(ListGraph::GraphType::Undirected,
    5);
    lgud.addEdge(0, 3, 5);
    lgud.addEdge(3, 2, 10);
    lgud.addEdge(0, 1, 15);
    lgud.addEdge(2, 4, 20);
    lgud.addEdge(0, 4, 25);

    lgud.removeEdge(0, 3);
    assert(lgud.successorsLists[0].getSize() == 2);
    assert(lgud.successorsLists[1].getSize() == 1);
    assert(lgud.successorsLists[2].getSize() == 2);
    assert(lgud.successorsLists[3].getSize() == 1);
    assert(lgud.successorsLists[4].getSize() == 2);
    assert(lgud.edgeCount == 4);
    cout << undirected << endl;
    cout << lgud << endl;

    lgud.removeEdge(2, 4);
    assert(lgud.successorsLists[0].getSize() == 2);
    assert(lgud.successorsLists[1].getSize() == 1);
    assert(lgud.successorsLists[2].getSize() == 1);
    assert(lgud.successorsLists[3].getSize() == 1);
    assert(lgud.successorsLists[4].getSize() == 1);
    assert(lgud.edgeCount == 3);
    cout << undirected << endl;
    cout << lgud << endl;

    lgud.removeEdge(3, 2);
    lgud.removeEdge(0, 1);
    lgud.removeEdge(0, 4);
    assert(lgud.successorsLists[0].getSize() == 0);
    assert(lgud.successorsLists[1].getSize() == 0);
    assert(lgud.successorsLists[2].getSize() == 0);
    assert(lgud.successorsLists[3].getSize() == 0);
    assert(lgud.successorsLists[4].getSize() == 0);
    assert(lgud.edgeCount == 0);
    cout << undirected << endl;
    cout << lgud << endl;
}

void ListGraphTest::testGetVertexSuccessors() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    lgd.addEdge(0, 3, 5);
    lgd.addEdge(3, 0, 10);
    lgd.addEdge(0, 1, 15);
    lgd.addEdge(2, 4, 20);
    lgd.addEdge(0, 4, 25);
    assert(lgd.getVertexSuccessors(0).getSize() == 3);
    assert(lgd.getVertexSuccessors(4).getSize() == 0);
    cout << directed << endl;
    cout << lgd << endl;

    ListGraph lgud(ListGraph::GraphType::Undirected,
    5);
    lgud.addEdge(0, 3, 5);
    lgud.addEdge(3, 2, 10);
    lgud.addEdge(0, 1, 15);
    lgud.addEdge(2, 4, 20);
    lgud.addEdge(0, 4, 25);
    assert(lgud.getVertexSuccessors(0).getSize() == 3);
    assert(lgud.getVertexSuccessors(3).getSize() == 2);
    cout << undirected << endl;
    cout << lgud << endl;
}

void ListGraphTest::testGetVertexPredecessors() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    lgd.addEdge(0, 3, 5);
    lgd.addEdge(3, 0, 10);
    lgd.addEdge(0, 1, 15);
    lgd.addEdge(2, 4, 20);
    lgd.addEdge(0, 4, 25);
    assert(lgd.getVertexPredecessors(0).getSize() == 1);
    assert(lgd.getVertexPredecessors(4).getSize() == 2);
    cout << directed << endl;
    cout << lgd << endl;

    ListGraph lgud(ListGraph::GraphType::Undirected,
    5);
    lgud.addEdge(0, 3, 5);
    lgud.addEdge(3, 2, 10);
    lgud.addEdge(0, 1, 15);
    lgud.addEdge(2, 4, 20);
    lgud.addEdge(0, 4, 25);
    assert(lgud.getVertexPredecessors(0).getSize() == 3);
    assert(lgud.getVertexPredecessors(3).getSize() == 2);
    cout << undirected << endl;
    cout << lgud << endl;
}

void ListGraphTest::testGetEdgeParameter() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    lgd.addEdge(0, 3, 5);
    lgd.addEdge(3, 0, 10);
    lgd.addEdge(0, 1, 15);
    lgd.addEdge(2, 4, 20);
    lgd.addEdge(0, 4, 25);
    assert(lgd.getEdgeParameter(0, 3) == 5);
    cout << directed << endl;
    cout << lgd << endl;

    ListGraph lgud(ListGraph::GraphType::Undirected,
    5);
    lgud.addEdge(0, 3, 5);
    lgud.addEdge(3, 2, 10);
    lgud.addEdge(0, 1, 15);
    lgud.addEdge(2, 4, 20);
    lgud.addEdge(0, 4, 25);
    assert(lgud.getEdgeParameter(2, 3) == 10);
    cout << undirected << endl;
    cout << lgud << endl;
}

void ListGraphTest::testGetVertexCount() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    lgd.addEdge(0, 3, 5);
    lgd.addEdge(3, 0, 10);
    lgd.addEdge(0, 1, 15);
    assert(lgd.getVertexCount() == 5);

    ListGraph lgud(ListGraph::GraphType::Undirected,
    6);
    lgud.addEdge(0, 3, 5);
    lgud.addEdge(3, 2, 10);
    lgud.addEdge(0, 1, 15);
    lgud.addEdge(2, 4, 20);
    assert(lgud.getVertexCount() == 6);
}

void ListGraphTest::testGetEdgeCount() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    lgd.addEdge(0, 3, 5);
    lgd.addEdge(3, 0, 10);
    lgd.addEdge(0, 1, 15);
    assert(lgd.getEdgeCount() == 3);

    ListGraph lgud(ListGraph::GraphType::Undirected,
    6);
    lgud.addEdge(0, 3, 5);
    lgud.addEdge(3, 2, 10);
    lgud.addEdge(0, 1, 15);
    lgud.addEdge(2, 4, 20);
    assert(lgud.getEdgeCount() == 4);
}

void ListGraphTest::testGetDensity() {
    ListGraph lgd(ListGraph::GraphType::Directed,
    5);
    lgd.addEdge(0, 3, 5);
    lgd.addEdge(3, 0, 10);
    lgd.addEdge(0, 1, 15);
    assert(lgd.getDensity() - 3.0 / (5 * 4) < 0.000001);

    ListGraph lgud(ListGraph::GraphType::Undirected,
    6);
    lgud.addEdge(0, 3, 5);
    lgud.addEdge(3, 2, 10);
    lgud.addEdge(0, 1, 15);
    lgud.addEdge(2, 4, 20);
    assert(lgud.getDensity() - 4.0 / ((6 * 5) / 2) < 0.000001);
}

void ListGraphTest::testToString() {

}
