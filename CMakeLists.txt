cmake_minimum_required(VERSION 3.15)
project(PEA_p1)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_p1 main.cpp

        structures/Table.h structures/DoublyLinkedList.h structures/Stack.h
        structures/graphs/IGraph.h structures/graphs/IGraph.cpp
        structures/graphs/misc/Edge.h
        structures/graphs/MatrixGraph.h structures/graphs/MatrixGraph.cpp
        structures/graphs/ListGraph.h structures/graphs/ListGraph.cpp

        tests/MatrixGraphTest.h tests/MatrixGraphTest.cpp
        tests/ListGraphTest.h tests/ListGraphTest.cpp
        )