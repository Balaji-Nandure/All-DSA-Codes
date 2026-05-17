/*
Problem: Queue Using Array

GFG: https://www.geeksforgeeks.org/problems/implement-queue-using-array/1

Description:
Implement a queue of fixed size n using array with operations:
enqueue, dequeue, getFront, getRear, isEmpty, isFull.

Approach:
Use circular queue with:
- frontIdx: index of current front
- rearIdx : index of current rear
- sz      : current number of elements
- cap     : maximum capacity

All operations run in O(1).
*/

#include <bits/stdc++.h>
using namespace std;

class Queue {
  private:
    int* arr;
    int frontIdx;
    int rearIdx;
    int sz;
    int cap;

  public:
    Queue(int n) {
        cap = n;
        arr = new int[cap];
        frontIdx = 0;
        rearIdx = -1;
        sz = 0;
    }

    void enqueue(int x) {
        if (isFull()) return;
        rearIdx = (rearIdx + 1) % cap;
        arr[rearIdx] = x;
        sz++;
    }

    void dequeue() {
        if (isEmpty()) return;
        frontIdx = (frontIdx + 1) % cap;
        sz--;
        if (sz == 0) {
            frontIdx = 0;
            rearIdx = -1;
        }
    }

    int getFront() {
        if (isEmpty()) return -1;
        return arr[frontIdx];
    }

    int getRear() {
        if (isEmpty()) return -1;
        return arr[rearIdx];
    }

    bool isEmpty() {
        return sz == 0;
    }

    bool isFull() {
        return sz == cap;
    }
};


