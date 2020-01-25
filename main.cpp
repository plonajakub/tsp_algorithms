#include "tests/ListGraphTest.h"
#include "tests/TSPAlgorithmsTest.h"
#include "tests/MiscellaneousTests.h"
#include "menu/ConsoleMenu.h"
#include "time_tests/TimeMeasurement.h"
#include "parameter_analysis/local_search/LSParameterAnalysis.h"
#include "parameter_analysis/populational_algorithms/GAParameterAnalysis.h"


int main() {

//    ListGraphTest lgt;
//    lgt.run();

//    TSPAlgorithmsTest tspAlgorithmsTest;
//    tspAlgorithmsTest.run();

//    MiscellaneousTests mt;
//    mt.run();

//    ConsoleMenu cm;
//    cm.start();

//    LSParameterAnalysis lsParameterAnalysis;
//    lsParameterAnalysis.run();

//    TimeMeasurement tm;
//    tm.run();

    GAParameterAnalysis gaParameterAnalysis;
    gaParameterAnalysis.run();

    return 0;
}