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

        menu/MenuItem.h menu/MenuItem.cpp
        menu/ConsoleMenu.h menu/ConsoleMenu.cpp

        utilities/Random.cpp utilities/Random.h
        utilities/TSPUtils.h utilities/TSPUtils.cpp

        algorithms/helper_structures/TSPHelperStructures.h
        algorithms/TSPExactAlgorithms.h algorithms/TSPExactAlgorithms.cpp

        algorithms/TSPGreedyAlgorithms.h algorithms/TSPGreedyAlgorithms.cpp
        algorithms/TSPLocalSearchAlgorithms.h algorithms/TSPLocalSearchAlgorithms.cpp
        algorithms/helper_structures/LocalSearchParameters.h

        tests/TSPAlgorithmsTest.h tests/TSPAlgorithmsTest.cpp
        tests/MiscellaneousTests.h tests/MiscellaneousTests.cpp
        time_tests/TimeMeasurement.h time_tests/TimeMeasurement.cpp
)