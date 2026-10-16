// Problem: Optimum Location of Point to Minimize Total Distance
// Link (GFG): https://www.geeksforgeeks.org/problems/optimum-location-of-point-to-minimize-total-distance/0
// Article: https://www.geeksforgeeks.org/dsa/optimum-location-point-minimize-total-distance/
// Difficulty: Hard
// Topic: Searching, Ternary Search, Computational Geometry, Unimodal Convex Optimization

/*
Problem Statement:
Given a set of N points in a 2D plane and a line defined by equation:
    a*x + b*y + c = 0
Find a point on the line such that the sum of Euclidean distances from this point 
to all the N points is MINIMIZED. Return the minimum total distance.

Example 1:
Input:
Line: 1*x - 1*y - 3 = 0 (i.e. a = 1, b = -1, c = -3)
Points: [(-3, -2), (-1, 0), (-1, 2), (1, 2), (3, 4)]
Output: 20.77 (approx)

Constraints:
- 1 <= N <= 10^4
- -1000 <= x_i, y_i <= 1000
- a, b, c are integers where not both a and b are zero.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Binary Search:
//   * The predicate function was MONOTONIC (e.g. false, false, ..., true, true).
// - In Optimum Location (Ternary Search on Unimodal Functions):
//   * The distance function `D(x)` is NOT monotonic; it first decreases to a global minimum, 
//     and then increases (a bowl-shaped CONVEX function).
//   * Binary search cannot decide which half to prune because comparing `f(mid)` with target 
//     is meaningless without a known target value.
//   * Instead, we use TERNARY SEARCH: Evaluating two test points `m1` and `m2` inside the interval 
//     reveals the slope of the bowl and allows us to discard 1/3 of the search space in each step!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Ternary Search on Continuous Real Line (Optimal & Chosen):
//   - A point on the line with x-coordinate `x` has y-coordinate:
//       `y = (-c - a * x) / (double)b` (assuming b != 0; if b == 0, x is fixed).
//   - Define `computeTotalDistance(x)`:
//       Sums `sqrt((x - p.x)^2 + (y - p.y)^2)` across all N points.
//   - Unimodal Property: `computeTotalDistance(x)` is convex with a single global minimum.
//   - Search space: `low = -1e6`, `high = 1e6`.
//   - In each of ~80 iterations:
//       `m1 = low + (high - low) / 3.0`
//       `m2 = high - (high - low) / 3.0`
//       If `computeTotalDistance(m1) < computeTotalDistance(m2)`:
//           Minimum must lie left of `m2` -> `high = m2`.
//       Else:
//           Minimum must lie right of `m1` -> `low = m1`.
//   - Complexity: O(N * log_{1.5}(range / eps)) = ~80 * N operations.
//   - Space Complexity: O(1) auxiliary space.

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

struct Line {
    int a, b, c;
};

class Solution {
private:
    // Computes total Euclidean distance from point (x, y) on the line to all points
    double totalDistance(const Line& line, const vector<Point>& points, double x) {
        // If line is vertical (b == 0), y is the variable; otherwise solve for y
        double y;
        if (line.b != 0) {
            y = (-line.c - line.a * x) / (double)line.b;
        } else {
            // If b == 0, x is fixed: x = -c / a
            y = x; // When vertical, parameter x actually represents y
            x = -line.c / (double)line.a;
        }

        double sumDist = 0.0;
        for (const auto& p : points) {
            double dx = x - p.x;
            double dy = y - p.y;
            sumDist += sqrt(dx * dx + dy * dy);
        }
        return sumDist;
    }

public:
    double findOptimumCost(Line line, vector<Point> points, int n) {
        double low = -1e6;
        double high = 1e6;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Ternary search: Run for fixed 80 iterations to guarantee precision of ~1e-9 without floating point looping bugs.
        // Each iteration shrinks the search space to 2/3 of its previous size.
        for (int iter = 0; iter < 80; ++iter) {
            double m1 = low + (high - low) / 3.0;
            double m2 = high - (high - low) / 3.0;

            double dist1 = totalDistance(line, points, m1);
            double dist2 = totalDistance(line, points, m2);

            // If m1 is lower, the minimum cannot be in [m2, high]
            if (dist1 < dist2) {
                high = m2;
            } else {
                low = m1;
            }
        }

        return totalDistance(line, points, (low + high) / 2.0);
    }
};

int main() {
    Solution sol;
    Line line = {1, -1, -3}; // x - y - 3 = 0
    vector<Point> points = {{-3, -2}, {-1, 0}, {-1, 2}, {1, 2}, {3, 4}};

    double minCost = sol.findOptimumCost(line, points, points.size());
    cout << fixed << setprecision(4);
    cout << "Optimum Minimum Total Distance: " << minCost << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * 80) = O(N).
  * 80 iterations reduces the search range from 2 * 10^6 down to (2/3)^80 ≈ 10^(-14).
  * In each iteration, distance to all N points is computed in O(N).
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Ternary Search is the universal algorithmic tool when optimizing unimodal / convex 
  cost functions on continuous domains.
*/
