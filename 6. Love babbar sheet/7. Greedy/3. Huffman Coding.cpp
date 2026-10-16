/**
 * ============================================================================
 * Problem: Huffman Coding (Optimal Prefix Codes)
 * Category: Greedy / Min-Heap / Binary Trees
 * 
 * Problem Statement:
 * Given a string S of N distinct characters and their corresponding frequencies
 * f[0...N-1].
 * 
 * Build the Huffman Tree and return the Huffman codes of all characters in 
 * PREORDER traversal of the Huffman Tree.
 * In a Huffman tree:
 *   - Left edge represents bit '0'.
 *   - Right edge represents bit '1'.
 *   - Characters reside strictly at leaf nodes (satisfying the prefix-free property).
 * 
 * Example:
 * Input:
 *   S = "abcdef"
 *   f = {5, 9, 12, 13, 16, 45}
 * Output (Preorder Codes):
 *   ["0", "100", "101", "1100", "1101", "111"]
 * 
 * Constraints:
 * 1 <= N <= 26
 * 1 <= f[i] <= 10^4
 * Must run in O(N log N) time and O(N) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Lossless Data Compression via Variable-Length Prefix Codes:
 *    - Fixed-length encoding uses ceil(log2(N)) bits per character (e.g., 3 bits for 6 chars).
 *    - Huffman Coding assigns SHORTER binary bitstrings to frequently occurring
 *      characters, and LONGER bitstrings to rarer characters, minimizing total bitlength.
 * 2. Prefix-Free Property:
 *    - No character's binary code is a prefix of another character's code,
 *      allowing unambiguous real-time streaming decode without delimiters.
 * 3. Bottom-Up Tree Synthesis via Min-Heap:
 *    - The two least frequent characters are continually merged together first,
 *      ensuring they end up deepest in the tree (longest code length).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Greedy Min-Heap Bottom-Up Tree Construction:
 *   - Step 1: Create a leaf node for each character with its frequency.
 *       Push all N nodes into a Min-Heap.
 *   - Step 2: While min-heap contains more than 1 node:
 *       - Extract `left = minHeap.top(); minHeap.pop();`
 *       - Extract `right = minHeap.top(); minHeap.pop();`
 *       - Create internal node `parent = new Node('$', left->freq + right->freq)`
 *       - `parent->left = left; parent->right = right;`
 *       - Push `parent` back into the min-heap.
 *   - Step 3: The sole remaining node in the heap is the root of the Huffman Tree!
 *   - Step 4: Perform Preorder Traversal on the Huffman Tree:
 *       - Recurse left with `code + "0"`.
 *       - Recurse right with `code + "1"`.
 *       - If leaf node is reached, store the generated code.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator for Min-Heap based on frequency
struct CompareHuffman {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

class Solution {
private:
    /**
     * Preorder traversal to collect all prefix codes.
     */
    void preorderTraverse(HuffmanNode* root, string code, vector<string>& result) {
        if (root == nullptr) return;

        // Leaf node reached: character found!
        if (root->left == nullptr && root->right == nullptr) {
            result.push_back(code.empty() ? "0" : code); // Guard against single-character trees
            return;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Branching binary decisions: Following the left branch appends '0',
        // while following the right branch appends '1'.
        preorderTraverse(root->left, code + "0", result);
        preorderTraverse(root->right, code + "1", result);
    }

public:
    /**
     * Builds Huffman Tree and returns prefix codes in preorder traversal order.
     * @param S String containing distinct characters.
     * @param f Array containing character frequencies.
     * @param N Number of characters.
     * @return Vector of Huffman prefix codes in preorder.
     */
    vector<string> huffmanCodes(string S, vector<int> f, int N) {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareHuffman> minHeap;

        // Step 1: Create leaf nodes and insert into Min-Heap
        for (int i = 0; i < N; ++i) {
            minHeap.push(new HuffmanNode(S[i], f[i]));
        }

        // Step 2: Combine two minimum frequency nodes until only 1 tree remains
        while (minHeap.size() > 1) {
            HuffmanNode* left = minHeap.top();
            minHeap.pop();

            HuffmanNode* right = minHeap.top();
            minHeap.pop();

            // Internal nodes use special dummy character '$'
            HuffmanNode* parent = new HuffmanNode('$', left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            minHeap.push(parent);
        }

        HuffmanNode* root = minHeap.top();
        vector<string> result;

        // Step 3: Traverse in preorder to collect prefix codes
        preorderTraverse(root, "", result);

        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case:
    // S = "abcdef", f = {5, 9, 12, 13, 16, 45}
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    int N = S.length();

    vector<string> codes = solver.huffmanCodes(S, f, N);

    cout << "Huffman Codes (Preorder Traversal):\n";
    for (const string& code : codes) {
        cout << code << " ";
    }
    cout << "\n";
    // Expected: ["0", "100", "101", "1100", "1101", "111"]

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Initial heap construction of N elements: O(N log N).
 *   - While loop runs (N - 1) times, each doing 2 pops and 1 push: O(N log N).
 *   - Preorder traversal visits 2N - 1 nodes: O(N).
 *   - Total Time: O(N log N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(N) to store the 2N - 1 tree nodes and heap.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. The two lowest-frequency symbols are greedily combined first, ensuring their
 *    depth in the tree is maximized, producing the longest codes for the rarest symbols.
 * 2. Prefix-free property: Every codeword is a path to a leaf, so no codeword can
 *    be an ancestor (prefix) of another.
 */
