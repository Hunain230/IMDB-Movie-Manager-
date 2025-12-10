#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
using namespace std; 

struct QNode {

    int data;
    QNode* next;

    QNode(int val) {

        data = val;
        next = NULL;
    }
};

class Queue {

private:
    QNode* front;
    QNode* rear;

    int size;

public:

    Queue() {
        front = NULL;
        rear = NULL;

        size = 0;
    }

    void enqueue(int value) {

        QNode* newNode = new QNode(value);

        if (rear == NULL) {
            front = rear = newNode;
        }

        else {
            rear->next = newNode;
            rear = newNode;
        }

        size++;
    }

    int dequeue() {

        if (isEmpty()) {

            return -1;
        }

        QNode* temp = front;

        int val = front->data;
        front = front->next;

        if (front == NULL) {
            rear = NULL;
        }

        delete temp;

        size--;
        return val;
    }

    int peek() {
        if (isEmpty()) {
            return -1;
        }

        return front->data;
    }

    bool isEmpty() {
        return front == NULL;
    }

    int getSize() {

        return size;
    }

    void clear() {

        while (!isEmpty()) {
            dequeue();
        }

    }
};

#endif
