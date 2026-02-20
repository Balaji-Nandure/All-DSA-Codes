class myQueue {

    int* arr;
    int front, rear, capacity, count;

  public:
    myQueue(int n) {
        capacity = n;
        arr = new int[n];
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    void enqueue(int x) {
        if (isFull())
            return;
        rear = (rear + 1) % capacity;
        arr[rear] = x;
        count++;
    }

    void dequeue() {
        if (isEmpty())
            return;
        front = (front + 1) % capacity;
        count--;
    }

    int getFront() {
        if (isEmpty())
            return -1;
        return arr[front];
    }

    int getRear() {
        if (isEmpty())
            return -1;
        return arr[rear];
    }
};