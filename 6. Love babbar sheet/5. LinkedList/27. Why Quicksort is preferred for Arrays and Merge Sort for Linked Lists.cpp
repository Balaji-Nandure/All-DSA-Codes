/**
 * ============================================================================
 * Problem: Why QuickSort is Preferred for Arrays and Merge Sort for Linked Lists
 * Category: LinkedList / Sorting / Systems & Computer Architecture
 * 
 * Conceptual Question:
 * Why is QuickSort the industry standard for contiguous Arrays (e.g. `std::sort`),
 * while Merge Sort is the preferred standard for Linked Lists (e.g. `std::list::sort`)?
 * 
 * In-Depth Architectural & Algorithmic Comparison:
 * ============================================================================
 * 
 * 1. CPU Cache Locality (Spatial and Temporal):
 *    -------------------------------------------------------------------------
 *    - Arrays:
 *        Elements reside in strictly contiguous physical memory.
 *        When `arr[i]` is read, the hardware CPU prefetcher loads an entire 64-byte
 *        cache line containing adjacent elements (arr[i+1], arr[i+2]...).
 *        QuickSort iterates linearly over contiguous memory, resulting in near-zero
 *        cache misses and maximizing hardware memory bandwidth.
 *    - Linked Lists:
 *        Nodes are individually allocated via `malloc`/`new` and scattered randomly
 *        throughout the heap.
 *        Each pointer hop (`curr = curr->next`) accesses a new arbitrary memory page,
 *        triggering frequent L1/L2/L3 CPU cache misses. QuickSort's primary speed
 *        advantage (cache locality) is completely lost.
 * 
 * 2. Random Access vs Sequential Traversal:
 *    -------------------------------------------------------------------------
 *    - QuickSort requires O(1) random access:
 *        * Choosing efficient pivots (Median-of-three: low, mid, high).
 *        * Hoare's dual-pointer bidirectional scanning (`left++`, `right--`).
 *        * In a singly linked list, moving backwards (`right--`) is impossible
 *          without an O(N) linear scan!
 *    - Merge Sort requires only sequential access:
 *        * Merge Sort reads elements strictly sequentially from left to right.
 *        * It never requires backward traversal or index-based jumps.
 * 
 * 3. Auxiliary Memory Overhead:
 *    -------------------------------------------------------------------------
 *    - Arrays:
 *        * Merge Sort requires an auxiliary array of size O(N) to merge two sorted
 *          halves, incurring substantial memory allocation and copying overhead.
 *        * QuickSort is strictly IN-PLACE, using only O(log N) stack frames.
 *    - Linked Lists:
 *        * Merging two sorted linked lists requires ZERO auxiliary memory (O(1) space).
 *          Nodes are simply re-linked by changing their `next` pointer references!
 *        * Thus, the primary drawback of Merge Sort (O(N) extra space) vanishes
 *          completely on linked lists!
 * 
 * 4. Algorithmic Stability:
 *    -------------------------------------------------------------------------
 *    - Merge Sort is inherently STABLE (preserves the original relative order
 *      of elements with equal keys).
 *    - QuickSort is inherently UNSTABLE.
 *    - For linked data structures representing records, stability is highly desired.
 * 
 * 5. Worst-Case Guarantees:
 *    -------------------------------------------------------------------------
 *    - Merge Sort guarantees O(N log N) time in ALL cases (best, average, and worst).
 *    - QuickSort degrades to O(N^2) in its worst case if an adversarial pivot is selected.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// Demonstration of O(1) Memory Merge for Linked Lists vs Array Merge
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Demonstration {
public:
    /**
     * O(1) Space Pointer Merge:
     * Notice no 'new' or heap allocation occurs; only existing pointer addresses are modified!
     */
    static Node* mergeLinkedListsInPlace(Node* l1, Node* l2) {
        Node dummy(0);
        Node* tail = &dummy;

        while (l1 != nullptr && l2 != nullptr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // In linked lists, merging is an O(1) memory operation because we simply
            // swing existing pointers rather than allocating an auxiliary buffer.
            if (l1->data <= l2->data) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = (l1 != nullptr) ? l1 : l2;
        return dummy.next;
    }

    /**
     * Array Merge:
     * Requires an O(N) auxiliary vector and physical element copying.
     */
    static void mergeArray(vector<int>& arr, int low, int mid, int high) {
        vector<int> temp(high - low + 1);
        int i = low, j = mid + 1, k = 0;

        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= high) temp[k++] = arr[j++];

        for (int p = 0; p < k; ++p) {
            arr[low + p] = temp[p];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "============================================================\n";
    cout << "  QUICKSORT FOR ARRAYS vs MERGE SORT FOR LINKED LISTS\n";
    cout << "============================================================\n\n";

    cout << "1. CACHE LOCALITY:\n";
    cout << "   - Arrays: Contiguous memory -> Sequential hardware prefetching -> 0 Cache Misses.\n";
    cout << "   - Lists:  Scattered heap addresses -> Random memory hops -> High L1/L2 misses.\n\n";

    cout << "2. AUXILIARY SPACE:\n";
    cout << "   - Array Merge Sort: Requires O(N) extra memory buffer.\n";
    cout << "   - List Merge Sort:  Requires O(1) extra space (pointer re-linking only!).\n\n";

    cout << "3. RANDOM ACCESS:\n";
    cout << "   - QuickSort relies on O(1) random indexing for pivot selection and Hoare partition.\n";
    cout << "   - Linked lists only support O(1) sequential forward access.\n\n";

    cout << "4. CONCLUSION:\n";
    cout << "   - Arrays + QuickSort = Cache Friendly + O(1) In-Place Space = Optimal!\n";
    cout << "   - Lists + MergeSort  = O(1) Pointer Merge + Sequential Access + Stable = Optimal!\n";
    cout << "============================================================\n";

    return 0;
}

/**
 * SUMMARY TABLE FOR QUICK REVISION:
 * ----------------------------------------------------------------------------
 * Feature             | Arrays (QuickSort)        | Linked Lists (Merge Sort)
 * --------------------+---------------------------+---------------------------
 * Cache Locality      | Outstanding (Contiguous)  | Poor (Scattered Nodes)
 * Random Access       | O(1) Required by QS       | Not Supported (O(N))
 * Extra Memory Needed | O(log N) stack            | O(1) Aux (Only pointer rewires)
 * Worst Case Time     | O(N^2)                    | O(N log N) Guaranteed
 * Stability           | Unstable                  | Stable
 * ----------------------------------------------------------------------------
 */
