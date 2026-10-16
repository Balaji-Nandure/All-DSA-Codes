/**
 * Problem: Find the first circular tour that visits all Petrol Pumps (Gas Station)
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A naive simulation from each pump takes O(N^2) time.
 * - Here, circular traversal creates potential cyclic dependencies, but can be linearized into a single
 *   pass queue/greedy reset algorithm in strictly O(N) time and O(1) space.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Deficit Accumulation & Greedy Front Advance:
 *   - Key Mathematical Theorem:
 *     - If the vehicle starts at pump `A` and runs out of fuel before reaching pump `B + 1`,
 *       then NO petrol pump between `A` and `B` inclusive can reach `B + 1`!
 *       (Because arriving at any intermediate pump with surplus >= 0 is strictly better than starting there with 0 fuel).
 *     - Therefore, we can safely jump the starting point directly to `B + 1`!
 *   - Algorithm:
 *     - Maintain `start = 0`, `currPetrol = 0`, and `deficit = 0`.
 *     - For each pump `i`:
 *       - `currPetrol += petrol[i] - distance[i]`.
 *       - If `currPetrol < 0`:
 *         - Accumulate `deficit += currPetrol`.
 *         - Advance candidate start to `i + 1`.
 *         - Reset `currPetrol = 0`.
 *     - At loop end: If `currPetrol + deficit >= 0`, candidate `start` can complete the full circular tour!
 * 
 * TIME COMPLEXITY:
 * - O(N): Single pass through the petrol stations.
 * 
 * SPACE COMPLEXITY:
 * - O(1) auxiliary space.
 */

#include <iostream>
#include <vector>

struct PetrolPump {
    int petrol;
    int distance;
};

int tour(const std::vector<PetrolPump>& p, int n) {
    int start = 0;
    int currPetrol = 0;
    int deficit = 0;

    for (int i = 0; i < n; i++) {
        currPetrol += p[i].petrol - p[i].distance;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If fuel drops below 0, no pump between 'start' and 'i' can be valid; advance start to i + 1.
        if (currPetrol < 0) {
            deficit += currPetrol;
            start = i + 1;
            currPetrol = 0;
        }
    }

    // If total net fuel across the entire circuit is non-negative, candidate start is valid
    return (currPetrol + deficit >= 0) ? start : -1;
}

int main() {
    std::vector<PetrolPump> p = {
        {4, 6},
        {6, 5},
        {7, 3},
        {4, 5}
    };
    int n = p.size();

    int startStation = tour(p, n);
    if (startStation == -1) {
        std::cout << "No circular tour possible.\n";
    } else {
        std::cout << "Starting station index: " << startStation << "\n"; // Index 1
    }

    return 0;
}
