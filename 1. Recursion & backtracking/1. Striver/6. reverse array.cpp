/*
 * Problem: Reverse an Array using Recursion
 *
 * Reverse an array using recursion with multiple approaches.
 *
 * Time: O(n) - we process n/2 pairs
 * Space: O(n) - recursion stack depth is n/2
 */

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Two pointers - swap before recursive call
void reversearr1(int l, int r, int arr[]){
    // Base case: when left >= right, we've processed all pairs
    if(l >= r) return;
    // Swap elements at l and r positions
    swap(arr[l], arr[r]);
    // Recursively reverse the remaining subarray
    reversearr1(l+1, r-1, arr);
}

// Approach 2: Two pointers - swap after recursive call (also correct)
void reversearr2(int l, int r, int arr[]){
    // Base case: when left >= right, we've processed all pairs
    if(l >= r) return;
    // First reverse the inner subarray
    reversearr2(l+1, r-1, arr);
    // Then swap the outer elements
    swap(arr[l], arr[r]);
}

// Approach 3: Single pointer - calculate right index from left
void reversearr3(int i, int arr[], int n){
    // Base case: when we've processed half the array
    if(i >= n/2) return;
    // Swap element at i with element at (n-i-1)
    swap(arr[i], arr[n-i-1]);
    // Recursively process next position
    reversearr3(i+1, arr, n);
}

signed main() {
    int n = 5;
    int arr[n] = {1, 2, 3, 4, 5};


    reversearr1(0, n - 1, arr);
    for(int i = 0; i < n; i++) cout << arr[i] << " ";

    // reversearr2(0, n - 1, arr);
    // for(int i = 0; i < n; i++) cout << arr[i] << " ";
    
    // reversearr3(0, arr, n);
    // for(int i = 0; i < n; i++) cout << arr[i] << " ";
    

    // print the array
    return 0;
}