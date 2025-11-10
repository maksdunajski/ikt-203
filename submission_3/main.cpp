#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
// Kompleksitet: Kommentarer før hver funksjon/metode angir (T = tid, S = plass) for nåværende implementasjon.
class TStackArray {
private:
     int maxSize = 0;
     int* stackArray = nullptr;
     int top = -1;
public:
     // T: O(n) (allokerer array), S: O(n)
     TStackArray(int size) : maxSize(size) {
          stackArray = new int[maxSize];
     }
     // T: O(1), S: O(1)
     ~TStackArray() {
          delete[] stackArray;
     }
     // T: O(1), S: O(1)
     void push(int item) {
          if (top < maxSize - 1) {
               stackArray[++top] = item;
          }
          else {
               std::cout << "Stack Overflow" << std::endl;
          }
     }
     // T: O(1), S: O(1)
     int Pop() {
          if (!IsEmpty()) {
               return stackArray[top--];
          }
          else {
               std::cout << "Stack is empty" << std::endl;
               return -1;
          }
     }
     // T: O(1), S: O(1)
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
     // T: O(n) (allokerer array), S: O(n)
     TQueueArray(int size) : maxSize(size) {
          queueArray = new int[maxSize];
     }
     // T: O(1), S: O(1)
     ~TQueueArray() {
          delete[] queueArray;
     }
     // T: O(1) (amortisert med modulo), S: O(1)
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
     // T: O(1), S: O(1)
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
     // T: O(1), S: O(1)
     int Peek() const {
          if (!IsEmpty()) {
               return queueArray[front];
          }
          else {
               std::cout << "Queue is empty" << std::endl;
               return -1;
          }
     }
     // T: O(1), S: O(1)
     bool IsEmpty() const {
          return itemCount == 0;
     }
};

class TNodeInteger {
public:
     int data;
     TNodeInteger* next;
     // T: O(1), S: O(1)
     TNodeInteger(int data) : data(data), next(nullptr) {}
};

class TStackLinkedList {
private:
     TNodeInteger* top = nullptr;
public:
     // T: O(1), S: O(1)
     TStackLinkedList() {
          top = new TNodeInteger(0); // Dummy node
     }
     // T: O(k) hvor k = antall elementer, S: O(1)
     ~TStackLinkedList() {
          while (!IsEmpty()) {
               Pop();
          }
          delete top;
     }
     // T: O(1), S: O(1)
     void Push(int item) {
          TNodeInteger* newNode = new TNodeInteger(item);
          newNode->next = top->next;
          top->next = newNode;
     }
     // T: O(1), S: O(1)
     int Pop() {
          if (!IsEmpty()) {
               TNodeInteger* temp = top->next;
               int item = temp->data;
               top->next = temp->next;
               delete temp;
               return item;
          }
          else {
               std::cout << "Stack is empty" << std::endl;
               return -1;
          }
     }
     // T: O(1), S: O(1)
     int Peek() const {
          if (!IsEmpty()) {
               return top->next->data;
          }
          else {
               std::cout << "Stack is empty" << std::endl;
               return -1;
          }
     }
     // T: O(1), S: O(1)
     bool IsEmpty() const {
          return top->next == nullptr;
     }
};

class TQueueLinkedList {
private:
     TNodeInteger* front = nullptr;
     TNodeInteger* back = nullptr;
public:
     // T: O(1), S: O(1)
     TQueueLinkedList() {
          front = new TNodeInteger(0); // Dummy node
          back = front;
     }
     // T: O(k) hvor k = antall elementer, S: O(1)
     ~TQueueLinkedList() {
          while (!IsEmpty()) {
               Dequeue();
          }
          delete front;
     }
     // T: O(1), S: O(1)
     void Enqueue(int item) {
          TNodeInteger* newNode = new TNodeInteger(item);
          back->next = newNode;
          back = newNode;
     }
     // T: O(1), S: O(1)
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
     // T: O(1), S: O(1)
     int Peek() const {
          if (!IsEmpty()) {
               return front->next->data;
          }
          else {
               std::cout << "Queue is empty" << std::endl;
               return -1;
          }
     }
     // T: O(1), S: O(1)
     bool IsEmpty() const {
          return front->next == nullptr;
     }
};

// ReverseString: L = lengde på streng. Nåværende T: O(L^2) (strlen i loop), S: O(L)
static std::string ReverseString(const char* aStr) {
     TStackArray stack(strlen(aStr));
     for (int i = 0; i < strlen(aStr); i++) {
          stack.push(aStr[i]);
     }
     std::string reversedStr;
     while (!stack.IsEmpty()) {
          reversedStr += static_cast<char>(stack.Pop());
     }
     return reversedStr;
}

// Factorial: n = input. T: O(n), S: O(n) (stack-array lagrer 2..n)
static int Factorial(int n) {
     if (n<0) {
          return -1;
     }
     if (n == 0 || n == 1) {
          return 1;
     }
     TStackArray stack(n);
     for (int i = 2; i <= n; i++) {
          stack.push(i);
     }
     int result = 1;
     while (!stack.IsEmpty()) {
          result = result * stack.Pop();
     }
     return result;
}

// SimulateWaitLine: fast størrelse (5). T: O(1) for denne konfigurasjonen (O(k) generelt), S: O(1) (O(k) generelt)
static void SimulateWaitLine() {
     TQueueArray queue(5);
     for (int i = 1; i <= 5; i++) {
          std::cout << "Customer " << i << " arrives." << std::endl;
          queue.Enqueue(i);
     }
     while (!queue.IsEmpty()) {
          int servedCustomer = queue.Dequeue();
          std::cout << "Customer " << servedCustomer << " is served." << std::endl;
     }
}

static const int grid_size = 7;
static int grid[grid_size][grid_size];
static bool visited[grid_size][grid_size] = { false };

// initializeGrid: T: O(g^2), S: O(1) ekstra (dataene er globale)
static void initializeGrid() {
     std::srand(std::time(0));
     for (int i = 0; i < grid_size; i++) {
          for (int j = 0; j < grid_size; j++) {
               grid[i][j] = std::rand() % 9;
               visited[i][j] = false;
          }
     }
}

// isValid: T: O(1), S: O(1)
static bool isValid(int row, int col) {
     return row >= 0 && row < grid_size && col >= 0 && col < grid_size && !visited[row][col];
}

// DFS: T: O(g^2), S: O(g^2) (stack worst case)
static bool DFS(int startRow, int startCol) {
     TStackArray stack(grid_size * grid_size);
     int cellPos = startRow * grid_size + startCol;
     stack.push(cellPos);
     while (!stack.IsEmpty()) {
          cellPos = stack.Pop();
          int row = cellPos / grid_size;
          int col = cellPos % grid_size;
          if (grid[row][col] == 0) {
               std::cout << "Zero found at (" << row << ", " << col << ")" << std::endl;
               return true;
          }
          std::cout << "Visiting (" << row << ", " << col << ") with value " << grid[row][col] << std::endl;
          visited[row][col] = true;
          int neighbors[4][2] = { { row - 1, col}, { row, col + 1}, { row + 1, col}, { row, col - 1} };
          for (int i = 0; i < 4; i++) {
               int newRow = neighbors[i][0];
               int newCol = neighbors[i][1];
               if (isValid(newRow, newCol)) {
                    cellPos = newRow * grid_size + newCol;
                    stack.push(newRow * grid_size + newCol);
               }
          }
     }
     std::cout << "No zero found in the grid." << std::endl;
     return false;
}

// BFS: T: O(g^2), S: O(g^2) (queue worst case)
static bool BFS(int startRow, int startCol) {
     TQueueArray queue(grid_size * grid_size);
     int cellPos = startRow * grid_size + startCol;
     queue.Enqueue(cellPos);
     while (!queue.IsEmpty()) {
          cellPos = queue.Dequeue();
          int row = cellPos / grid_size;
          int col = cellPos % grid_size;
          if (grid[row][col] == 0) {
               std::cout << "Zero found at (" << row << ", " << col << ")" << std::endl;
               return true;
          }
          std::cout << "Visiting (" << row << ", " << col << ") with value " << grid[row][col] << std::endl;
          visited[row][col] = true;
          int neighbors[4][2] = { { row - 1, col}, { row, col + 1}, { row + 1, col}, { row, col - 1} };
          for (int i = 0; i < 4; i++) {
               int newRow = neighbors[i][0];
               int newCol = neighbors[i][1];
               if (isValid(newRow, newCol)) {
                    cellPos = newRow * grid_size + newCol;
                    queue.Enqueue(newRow * grid_size + newCol);
               }
          }
     }
     std::cout << "No zero found in the grid." << std::endl;
     return false;
}

// main: Domineres av ReverseString (O(L^2)), Factorial (O(n)), DFS/BFS (O(g^2)).
int main() {
     std::string original = "Mjau mjau jeg er en katt";
     std::string reversed = ReverseString(original.c_str());
     std::cout << "Original string: " << original << std::endl;
     std::cout << "Reversed string: " << reversed << std::endl;

     std::cout << "Factorial of 5: " << Factorial(5) << std::endl;
     std::cout << "Simulating wait line:" << std::endl;
     SimulateWaitLine();

     initializeGrid();

     int startRow = std::rand() % grid_size;
     int startCol = std::rand() % grid_size;
     std::cout << "Starting DFS from (" << startRow << ", " << startCol << "):" << std::endl;
     DFS(startRow, startCol);
     std::cout << "Re-initializing grid for BFS:" << std::endl;
     for (int i = 0; i < grid_size; i++) {
          for (int j = 0; j < grid_size; j++) {
               visited[i][j] = false;
          }
     }
     std::cout << "Starting BFS from (" << startRow << ", " << startCol << "):" << std::endl;
     BFS(startRow, startCol);
     return 0;
}
