
#include "MiscellaneousTests.h"

void MiscellaneousTests::run() const {
    randomNumberGenerationTest();
}

void MiscellaneousTests::randomNumberGenerationTest() const {
    const int RANDOM_NUMBERS_QUANTITY = 10;

    cout << "Random ints" << endl;
    cout << "[0, 100]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getInt(0, 100) << ", ";
    }
    cout << Random::getInt(0, 100) << ']' << endl;

    cout << "[0, 1]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getInt(0, 1) << ", ";
    }
    cout << Random::getInt(0, 1) << ']' << endl;

    cout << "[2, 5]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getInt(2, 5) << ", ";
    }
    cout << Random::getInt(2, 5) << ']' << endl;
    cout << endl;


    const int PRECISION = 5;
    cout << "Random doubles" << endl;
    cout << "[0.0, 100.0]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << std::setprecision(PRECISION) << Random::getRealClosed(0, 100) << ", ";
    }
    cout << std::setprecision(PRECISION) << Random::getRealClosed(0, 100) << ']' << endl;

    cout << "[0.0, 1.0]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << std::setprecision(PRECISION) << Random::getRealClosed(0, 1) << ", ";
    }
    cout << std::setprecision(PRECISION) << Random::getRealClosed(0, 1) << ']' << endl;

    cout << "[2.0, 5.5]: [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << std::setprecision(PRECISION) << Random::getRealClosed(2, 5.5) << ", ";
    }
    cout << std::setprecision(PRECISION) << Random::getRealClosed(2, 5.5) << ']' << endl;
    cout << endl;

    cout << "Random bools" << endl;
    cout << "(true, 0): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(true, 0) << ", ";
    }
    cout << Random::getBool(true, 0) << ']' << endl;

    cout << "(true, 1): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(true, 1) << ", ";
    }
    cout << Random::getBool(true, 1) << ']' << endl;

    cout << "(true, 0.9): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(true, 0.9) << ", ";
    }
    cout << Random::getBool(true, 0.9) << ']' << endl;

    cout << "(true, 0.1): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(true, 0.1) << ", ";
    }
    cout << Random::getBool(true, 0.1) << ']' << endl;
    cout << endl;

    cout << "(false, 0): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(false, 0) << ", ";
    }
    cout << Random::getBool(false, 0) << ']' << endl;

    cout << "(false, 1): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(false, 1) << ", ";
    }
    cout << Random::getBool(false, 1) << ']' << endl;

    cout << "(false, 0.9): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(false, 0.9) << ", ";
    }
    cout << Random::getBool(false, 0.9) << ']' << endl;

    cout << "(false, 0.1): [";
    for (int i = 0; i != RANDOM_NUMBERS_QUANTITY - 1; ++i) {
        cout << Random::getBool(false, 0.1) << ", ";
    }
    cout << Random::getBool(false, 0.1) << ']' << endl;
    cout << endl;
}
