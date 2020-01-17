#ifndef PEA_P1_SPECIMEN_H
#define PEA_P1_SPECIMEN_H

#include <vector>

class Specimen {
public:
    std::vector<int> permutation;
    int targetFunctionValue;

    [[nodiscard]] double getFitness() const {
        return 1.0 / targetFunctionValue;
    }

    Specimen(const std::vector<int> &permutation, int targetFunctionValue) : permutation(permutation),
                                                                             targetFunctionValue(targetFunctionValue) {}
};

#endif //PEA_P1_SPECIMEN_H
