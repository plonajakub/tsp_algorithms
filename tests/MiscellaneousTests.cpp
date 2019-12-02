#include "MiscellaneousTests.h"

void MiscellaneousTests::run() const {
    randomNumberGenerationTest();
}

void MiscellaneousTests::randomNumberGenerationTest() const {
    const int randomNumbersQuantity = 10;
    cout << "Random ints: [";
    for (int i = 0; i != randomNumbersQuantity - 1; ++i) {
        cout << TSPRandom::getInstance().getInt(0, 100) << ", ";
    }
    cout << TSPRandom::getInstance().getInt(0, 100) << ']' << endl;
}
