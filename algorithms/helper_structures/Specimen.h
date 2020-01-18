#ifndef PEA_P1_SPECIMEN_H
#define PEA_P1_SPECIMEN_H

#include <utility>
#include <vector>

class Specimen {
public:
    std::vector<int> permutation;
    int targetFunctionValue;

    [[nodiscard]] double getFitness() const {
        return 1.0 / targetFunctionValue;
    }

    Specimen() : targetFunctionValue(std::numeric_limits<int>::max()) {}

    Specimen(std::vector<int> permutation, int targetFunctionValue) : permutation(std::move(permutation)),
                                                                      targetFunctionValue(targetFunctionValue) {}

    // For fitness comparisons
    bool operator<(const Specimen &rhs) const {
        return targetFunctionValue > rhs.targetFunctionValue; // getFitness() < rhs.getFitness()
    }

    bool operator>(const Specimen &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Specimen &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Specimen &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const Specimen &rhs) const {
        return targetFunctionValue == rhs.targetFunctionValue; // getFitness() == rhs.getFitness()
    }

    bool operator!=(const Specimen &rhs) const {
        return !(rhs == *this);
    }
};

#endif //PEA_P1_SPECIMEN_H
