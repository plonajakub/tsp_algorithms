#ifndef PEA_P1_MISCELLANEOUSTESTS_H
#define PEA_P1_MISCELLANEOUSTESTS_H

#include <cassert>
#include <iostream>
#include <iomanip>


#include "../utilities/Random.h"

using std::cout;
using std::endl;


class MiscellaneousTests {

public:
    void run() const;

private:
    void randomNumberGenerationTest() const;
};


#endif //PEA_P1_MISCELLANEOUSTESTS_H
