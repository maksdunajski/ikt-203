#include <iostream>


class Tstack {
private:
     int maxSize = 0;
     int* stackArray = nullptr;
     int top = -1;
     public:
     TstackArray(int size) : maxSize(size) {
          stackArray = new int[maxSize];
     }
     ~TstackArray() {
          delete[] stackArray;
     }

     void push(int item) {
          if (top < maxSize - 1) {
               stackArray[++top] = item;
          }
          else {
               std::cout << "Stack Overflow" << std::endl;
          }
     }
     int Pop() {
          if (!IsEmpty()) {
               return stackArray[top];
          }
          else {
               std::cout << "Stack is empty" << std::endl;
               return -1;
          }
     }
     bool IsEmpty() const {
          return top == -1;
     }
};



class TQueueArray {
     private:
     int maxSize = 0;
     int* queueArray = nullptr;
     int front = 0;
     int back = -1;
     int itemCount = 0;
     public:
     TQueueArray(int size) : maxSize(size) {
          queueArray = new int[maxSize];
     }
     ~TQueueArray() {
          delete[] queueArray;
     }
     void Enqueue(int item) {
          if (itemCount < maxSize) {
               back = (back + 1) % maxSize;
               queueArray[back] = item;
               itemCount++;
          }
          else {
               std::cout << "Queue overflow" << std::endl;
          }
     }
     int Dequeue() {
          if (!IsEmpty()) {
               int item = queueArray[front];
               front = (front + 1) % maxSize;
               itemCount--;
               return item;
          }
          else {
               std::cout << "Queue Underflow" << std::endl;
               return -1;
          }
     }
     int Peek() const {
          if (!IsEmpty()) {
               return queueArray[front];
          }
          else {
               std::cout << "Queue is empty" << std::endl;
               return -1;
          }
     }
     bool isEmpty() const {
          return itemCount == 0;
     }
};

class TNodeInteger {
public:
     int data;
     TNodeInteger* next;
     TNodeInteger(int data) : data(data), next(nullptr) {}
};

class TStackLinkedList {
private:
     TNodeInteger* front = nullptr;
     TNodeInteger* back = nullptr;
public:
     TQueueLinkedList() {
          front = new TNodeInteger(0);
          back = front;
     }
     ~TStackLinkedList() {
          while (!IsEmpty()) {
               Dequeue();
          }
          delete front;
     }
     void Enqueue(int item) {
          TNodeInteger* newNode = new TNodeInteger(item);
          back->next = newNode;
          back = newNode;
     }
     int Dequeue() {
          if (!IsEmpty()) {
               TNodeInteger* temp = front->next;
               int item = temp->data;
               front->next = temp->next;
               if (back == temp) {
                    back = front;
               }
               delete temp;
               return item;
          }
          else {
               std::cout << "Queue underflow" << std::endl;
               return -1;
          }
     }
     int Peek() const {
          if (!IsEmpty()) {
               return front->next->data;
          }
          else {
               std::cout << "Queue is empty" << std::endl;
               return -1;
          }
          bool IsEmpty() const {
               return front->next == nullptr;
          }
     }
};


void main() {

}