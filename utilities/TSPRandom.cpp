#include "TSPRandom.h"

TSPRandom* TSPRandom::instance = nullptr;

TSPRandom::TSPRandom() noexcept : defaultRandomEngine(static_cast<long unsigned int>(time(0))) {

}

TSPRandom &TSPRandom::getInstance() {
    if (instance == nullptr) {
        instance = new TSPRandom;
    }
    return *instance;
}

TSPRandom::~TSPRandom() {
    delete instance;
}

int TSPRandom::getInt(int min, int max) {
    std::uniform_int_distribution<int> uniform_dist(min, max);
    return uniform_dist(defaultRandomEngine);
}

double TSPRandom::getReal(double min, double max) {
    std::uniform_real_distribution<double> uniform_dist(min, max);
    return uniform_dist(defaultRandomEngine);
}
