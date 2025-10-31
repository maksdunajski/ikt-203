#include <iostream>
#include <string>
#include <cstdlib>

void printNaturalNumbersRecursion(int n) {
    if (n == 0) {
        return;
    }
    printNaturalNumbersRecursion(n-1);
    std::cout << n << std::endl;

}

int calculateFactorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * calculateFactorial(n-1);
}

int power(int base, int exponent){
    if (exponent == 0) {
    return 1;
    }
    return base * power(base, exponent-1);
}

int fibonacci(int n) {
    if (n <= 1) {
    return 1;
    }
return fibonacci(n-1) + fibonacci(n-2);
}

int countOccurrences(std::string s, char c) {
    if (s.length() == 0) {
        return 0;
    }
    int lastCount = (s.back() == c) ? 1 : 0;
    s = s.substr(0, s.length() - 1);
    return lastCount + countOccurrences(s, c);
}



int findLargestElement(int arr[], int size) {
    if (size == 1) {
        return arr[0];
    }
    int mid = size / 2;
    int highestLeft = findLargestElement(arr, mid);
    int highestRight = findLargestElement(arr + mid, size - mid);
    return (highestLeft > highestRight) ? highestLeft : highestRight;
}

void traverseAsciiTable(char start, char end) {
    if (start > end) {
        return;
    }
    std::cout << start << " " << std::endl;
    traverseAsciiTable(start+1, end);
    std::cout << start << std::endl;
}

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    int arr[20] = {};
    for (int i = 0; i < 20; i++) {
        arr[i] = rand() % 100;
}

    int n;
    std::string s;
    char c;
    char start;
    char end;
    std::cout << "Enter n: " << std::endl;
    std::cin >> n;
    std::cin.ignore();
    std::cout << "Enter c: " << std::endl;
    std::cin >> c;
    std::cin.ignore();
    std::cout << "Enter s : " << std::endl;
    std::getline(std::cin, s);
    std::cin.ignore();
    std::cout << "Enter start : " << std::endl;
    std::cin >> start;
    std::cout << "Enter end : " << std::endl;
    std::cin >> end;
    printNaturalNumbersRecursion(n);
    std::cout << "Factorial of " << n << ": " << calculateFactorial(n) << std::endl;
    std::cout << "Power of " << n << ": " << power(3, 2) << std::endl;
    std::cout << "Fobonacci of " << n << ": " << fibonacci(n) << std::endl;
    std::cout << countOccurrences(s, c) << std::endl;
    std::cout << "arr: ";
        for (int i = 0; i < 20; i++) {
            std::cout << arr[i] << " ";
        }
    std::cout << "Largest element of arr is: " << findLargestElement(arr, 20) << std::endl;
    traverseAsciiTable(start, end);
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.