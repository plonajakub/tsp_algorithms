#ifndef PEA_P1_MISCELLANEOUSTESTS_H
#define PEA_P1_MISCELLANEOUSTESTS_H

#include <cassert>
#include <iostream>


#include "../utilities/TSPRandom.h"

using std::cout;
using std::endl;


class MiscellaneousTests {

public:
    void run() const;

private:
    void randomNumberGenerationTest() const;
};


#endif //PEA_P1_MISCELLANEOUSTESTS_H
