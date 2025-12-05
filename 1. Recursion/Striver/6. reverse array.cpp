#include <bits/stdc++.h>
using namespace std;

void reversearr1(int l, int r, int arr[]){
    if(l >= r) return;
    swap(arr[l], arr[r]);
    reversearr1(l+1, r-1, arr);
}

// both are correct
void reversearr2(int l, int r, int arr[]){
    if(l >= r) return;
    reversearr2(l+1, r-1, arr);
    swap(arr[l], arr[r]);
}

// using single pointer
void reversearr3(int i, int arr[], int n){
    if(i >= n/2) return;
    swap(arr[i], arr[n-i-1]);
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