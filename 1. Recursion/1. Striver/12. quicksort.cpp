#include <bits/stdc++.h>
using namespace std;

// partition function with Lomuto's partition scheme
// Partition1 is with i = low - 1
int partition1(vector<int>& arr, int low, int high) {
    // we can choose any element as pivot.
    int pivot = arr[high]; // choose last element as pivot
    int i = low - 1; // place for swapping

    // running this till high - 1 because pibote is present at high.
    for (int j = low; j <= high - 1; ++j) {
        // CHANGE HERE: > instead of <. if you want to sort in descending order.
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // put pivot into correct position
    return i + 1;
}

// in this partition i = low (I will prefer this partition but both are correct)
int partition(vector<int>& arr, int low, int high) {
    // we can choose any element as pivot.
    int pivot = arr[high]; // choose last element as pivot
    int i = low;
    for (int j = low; j <= high - 1; j++) {
        // CHANGE HERE: > instead of <. if you want to sort in descending order.
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;  
        }
    }
    // Finally put pivot in correct place
    swap(arr[i], arr[high]);  
    return i;

}

// in this we are choosing middle element as pivot // just a variation
int partition2(vector<int>& arr, int low, int high) {
    // choose middle element as pivot
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];

    // move pivot to the end so that the rest of the code works unchanged
    swap(arr[mid], arr[high]);

    int i = low;
    for (int j = low; j <= high - 1; j++) {
        // CHANGE HERE: > instead of <. if you want to sort in descending order.
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    // put pivot in its correct position
    swap(arr[i], arr[high]);
    return i;
}


// quick sort recursive implementation
void quickSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    // choose pivote and put it in correct position  i.e at index pi.
    // after this pi will be at correct position
    int pi = partition(arr, low, high);
    // sort left part
    // left part is from low to pi - 1
    quickSort(arr, low, pi - 1);
    // sort right part
    // right part is from pi + 1 to high
    quickSort(arr, pi + 1, high);
}

int main() {
    vector<int> arr = {5, 4, 3, 7,12, 11, 13, 14, 9, 6, 2, 1, 16, 17, 10, 15 , 18, 19, 20};
    int n = arr.size();
    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    return 0;
}
