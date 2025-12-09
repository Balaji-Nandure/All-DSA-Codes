/*
Question: Solve Tower of Hanoi with recursion.

Given n disks on source rod A, move all disks to target rod C using auxiliary rod B.

Rules:
- Only one disk can be moved at a time.
- Only top disk of any rod can be moved.
- A larger disk cannot be placed on top of a smaller disk.

Print each move as: "Move disk X from rod Y to rod Z".

Expected moves for 3 disks:
Move disk 1 from rod A to rod C
Move disk 2 from rod A to rod B
Move disk 1 from rod C to rod B
Move disk 3 from rod A to rod C
Move disk 1 from rod B to rod A
Move disk 2 from rod B to rod C
Move disk 1 from rod A to rod C

Also print the total number of moves at the end.

Approach:
- For n disks, move (n-1) disks from source to auxiliary, move nth disk to target, then move (n-1) from auxiliary to target.
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive function to solve Tower of Hanoi
void towerOfHanoi(int n, char src, char aux, char dest, int &moveCount) {
    if(n == 0) return;
    // Move n-1 disks from src to aux using dest as auxiliary
    towerOfHanoi(n-1, src, dest, aux, moveCount);
    // Move nth disk from src to dest
    cout << "Move disk " << n << " from rod " << src << " to rod " << dest << endl;
    moveCount++;
    // Move n-1 disks from aux to dest using src as auxiliary
    towerOfHanoi(n-1, aux, src, dest, moveCount);
}

int main() {
    int n = 3; // You can change for more disks
    int moveCount = 0;
    towerOfHanoi(n, 'A', 'B', 'C', moveCount);
    cout << "Total moves: " << moveCount << endl;
    return 0;
}
