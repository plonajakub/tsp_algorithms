#ifndef PEA_P1_TSPRANDOM_H
#define PEA_P1_TSPRANDOM_H


#include <random>
#include <ctime>


class TSPRandom {

public:
    // Get instance
    static TSPRandom &getInstance();

    [[nodiscard]] int getInt(int min, int max);

    [[nodiscard]] double getReal(double min, double max);

private:
    TSPRandom() noexcept;

    ~TSPRandom();

    static TSPRandom *instance;

    std::random_device randomDevice;

    std::mt19937 defaultRandomEngine;

};


#endif //PEA_P1_TSPRANDOM_H
