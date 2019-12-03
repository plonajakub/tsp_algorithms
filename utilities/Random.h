#ifndef PEA_P1_RANDOM_H
#define PEA_P1_RANDOM_H


#include <random>
#include <chrono>
#include <limits>
#include <cmath>

class Random {

public:

    // [min, max]
    [[nodiscard]] static int getInt(int min, int max);

    // [min, max)
    [[nodiscard]] static double getReal(double min, double max);

    // [min, max]
    [[nodiscard]] static double getRealClosed(double min, double max);

    // Get value with given probability
    [[nodiscard]] static bool getBool(bool value, double probability);

private:
    Random() = default;

    static std::mt19937 randomEngine;

};


#endif //PEA_P1_RANDOM_H
