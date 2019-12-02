cmake_minimum_required(VERSION 3.15)
project(PEA_p1)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        PEA_p1

        main.cpp

        structures/Table.h
        structures/DoublyLinkedList.h structures/DoublyLinkedList.cpp
        structures/Stack.h
        structures/graphs/IGraph.h structures/graphs/IGraph.cpp
        structures/graphs/misc/Edge.h
        structures/graphs/MatrixGraph.h structures/graphs/MatrixGraph.cpp
        structures/graphs/ListGraph.h structures/graphs/ListGraph.cpp

        tests/MatrixGraphTest.h tests/MatrixGraphTest.cpp
        tests/ListGraphTest.h tests/ListGraphTest.cpp
        tests/TSPAlgorithmsTest.cpp tests/TSPAlgorithmsTest.h

        menu/MenuItem.h menu/MenuItem.cpp
        menu/ConsoleMenu.h menu/ConsoleMenu.cpp

        utilities/TSPUtils.h utilities/TSPUtils.cpp

        algorithms/TSPExactAlgorithms.h algorithms/TSPExactAlgorithms.cpp
        algorithms/TSPHelperStructures.h

        time_tests/TimeMeasurement.h time_tests/TimeMeasurement.cpp
        algorithms/TSPGreedyAlgorithms.cpp algorithms/TSPGreedyAlgorithms.h algorithms/TSPLocalSearchAlgorithms.cpp algorithms/TSPLocalSearchAlgorithms.h utilities/TSPRandom.cpp utilities/TSPRandom.h tests/MiscellaneousTests.cpp tests/MiscellaneousTests.h)