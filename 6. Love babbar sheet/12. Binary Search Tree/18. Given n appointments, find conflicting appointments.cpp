/**
 * Problem: Given "n" appointments, find conflicting appointments
 * Category: Binary Search Tree / Interval Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Standard BSTs store scalar point keys (`int val`).
 * - Here, each key is an INTERVAL `[low, high]`. We construct an INTERVAL TREE (an augmented BST)
 *   where each node maintains the maximum upper endpoint in its subtree, allowing O(log N) overlap detection.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Interval Tree (Augmented BST):
 *   - Each node contains:
 *     - `low, high`: The interval itself.
 *     - `max`: The maximum `high` value in the entire subtree rooted at this node.
 *   - Overlap Condition:
 *     - Two intervals `[l1, h1]` and `[l2, h2]` overlap IF AND ONLY IF `l1 < h2 && l2 < h1`.
 *   - Search & Insert Algorithm:
 *     - For each appointment:
 *       1. Query the Interval Tree:
 *          - If current node overlaps with appointment, report conflict!
 *          - If `curr->left != nullptr && curr->left->max >= app.low`:
 *            Search left subtree (a conflicting interval is guaranteed to potentially exist on left).
 *          - Otherwise, search right subtree.
 *       2. Insert the appointment into the Interval Tree (keyed on `low`), updating `max` upwards.
 * 
 * TIME COMPLEXITY:
 * - O(N log N): Each appointment queries and inserts in O(log N) average time.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for Interval Tree nodes.
 */

#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    int low, high;
};

struct ITNode {
    Interval i;
    int max;
    ITNode* left;
    ITNode* right;
    ITNode(Interval interval) : i(interval), max(interval.high), left(nullptr), right(nullptr) {}
};

bool doOverlap(Interval i1, Interval i2) {
    return (i1.low < i2.high && i2.low < i1.high);
}

ITNode* insertInterval(ITNode* root, Interval i) {
    if (!root) return new ITNode(i);

    int l = root->i.low;
    if (i.low < l) {
        root->left = insertInterval(root->left, i);
    } else {
        root->right = insertInterval(root->right, i);
    }

    // Update max value of this ancestor
    root->max = std::max(root->max, i.high);

    return root;
}

ITNode* overlapSearch(ITNode* root, Interval i) {
    if (!root) return nullptr;

    // Check if current node overlaps
    if (doOverlap(root->i, i)) {
        return root;
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // If left child exists and its max endpoint is >= current interval's start, overlap must be sought on left!
    if (root->left && root->left->max >= i.low) {
        return overlapSearch(root->left, i);
    }

    return overlapSearch(root->right, i);
}

void printConflictingAppointments(const std::vector<Interval>& appt) {
    ITNode* root = nullptr;

    for (const auto& app : appt) {
        ITNode* conflict = overlapSearch(root, app);
        if (conflict) {
            std::cout << "[" << app.low << ", " << app.high << "] Conflicts with [" 
                      << conflict->i.low << ", " << conflict->i.high << "]\n";
        }
        root = insertInterval(root, app);
    }
}

int main() {
    std::vector<Interval> appt = {
        {1, 5}, {3, 7}, {2, 6}, {10, 15}, {5, 6}, {4, 100}
    };

    std::cout << "Conflicting appointments:\n";
    printConflictingAppointments(appt);

    return 0;
}
