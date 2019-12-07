#ifndef PEA_P1_MISCELLANEOUSTESTS_H
#define PEA_P1_MISCELLANEOUSTESTS_H

#include <cassert>
#include <iostream>
#include <iomanip>


#include "../utilities/Random.h"
#include "../utilities/TSPUtils.h"
#include "../algorithms/TSPLocalSearchAlgorithms.h"

using std::cout;
using std::endl;


class MiscellaneousTests {

public:
    void run() const;

private:
    void randomNumberGenerationTest() const;
    void neighbourhoodDesignationTest(TSPLocalSearchAlgorithms::fNeighbourhood nextNeighbourFunction,
                                      const std::string &instanceFileToTest,
                                      const std::string &testName) const;
    void createRandomPermutationTest() const;
};


#endif //PEA_P1_MISCELLANEOUSTESTS_H
