#include "Random.h"

std::mt19937 Random::randomEngine(std::chrono::high_resolution_clock::now().time_since_epoch().count());

int Random::getInt(int min, int max) {
    return std::uniform_int_distribution<int>{min, max}(randomEngine);
}

double Random::getReal(double min, double max) {
    return std::uniform_real_distribution<double>{min, max}(randomEngine);
}

double Random::getRealClosed(double min, double max) {
    return std::uniform_real_distribution<double>{min, std::nextafter(max, std::numeric_limits<double>::max())}(
            randomEngine);
}

bool Random::getBool(bool value, double probability) {
    if (probability == 0) {
        return !value;
    }
    if (value) {
        return getRealClosed(0, 1) <= probability;
    } else {
        return getRealClosed(0, 1) >= probability;
    }
}

