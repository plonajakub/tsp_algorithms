#include "TSPAlgorithms.h"

std::vector<int> TSPAlgorithms::bruteForce(const IGraph *tspInstance) {
    // Get size of the ATSP instance
    const int permutationSize = tspInstance->getVertexCount();

    // Initialize natural permutation
    std::vector<int> permutation(permutationSize);
    for (int position = 0; position < permutationSize; ++position) {
        permutation[position] = position;
    }

    // Holds currently processed (sub)permutation last element's index
    int stackSlotIndex = 1;
    // Holds number of swap operation to be performed on (sub)permutations
    std::vector<int> stackCounters(permutationSize, 1);
    // Holds index of permutation's element to swap with last element in the permutation
    int swapIndex;
    // Current permutation's target function value
    int currentPathTargetFunctionValue;

    // Check target function value for natural permutation and take as best for now
    std::vector<int> bestPath = permutation;
    int bestPathTargetFunctionValue = TSPUtils::calculateTargetFunctionValue(tspInstance, permutation);
    do {
        // Test if there are still available swaps in (sub)permutation to be performed
        // (stackSlotIndex + 1) is a position (not index) of stack's slot
        if (stackCounters[stackSlotIndex] <= stackSlotIndex) {
            // Choose swap position with Heap's rule
            if ((stackSlotIndex + 1) % 2 == 1) {
                swapIndex = 0;
            } else {
                swapIndex = stackCounters[stackSlotIndex] - 1;
            }
            // Do the swap to generate next permutation
            std::swap(permutation[stackSlotIndex], permutation[swapIndex]);
            // Update number of swap of the permutation to be performed
            ++stackCounters[stackSlotIndex];
            // Generate sub-permutations
            stackSlotIndex = 1;

            // Compare with current best permutation and update if better solution was found
            currentPathTargetFunctionValue = TSPUtils::calculateTargetFunctionValue(tspInstance, permutation);
            if (currentPathTargetFunctionValue < bestPathTargetFunctionValue) {
                bestPath = permutation;
                bestPathTargetFunctionValue = currentPathTargetFunctionValue;
            }
        } else {
            // Process permutations with bigger size
            stackCounters[stackSlotIndex] = 1;
            ++stackSlotIndex;
        }

        // Repeat until all permutations are processed
    } while ((stackSlotIndex + 1) <= permutationSize);

    return bestPath;
}
