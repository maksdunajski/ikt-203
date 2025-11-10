#include <iostream>
#include <string>
#include <cstdlib>

// Tidskompleksitet: O(n)\n// Plasskompleksitet: O(n) (rekursjonsstakk)
void printNaturalNumbersRecursion(int n) {
    if (n == 0) {
        return;
    }
    printNaturalNumbersRecursion(n-1);
    std::cout << n << std::endl;

}

// Tidskompleksitet: O(n)\n// Plasskompleksitet: O(n) (rekursjonsstakk)
int calculateFactorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * calculateFactorial(n-1);
}

// Tidskompleksitet: O(exponent) (lineær)\n// Plasskompleksitet: O(exponent) (rekursjonsstakk)
int power(int base, int exponent){
    if (exponent == 0) {
    return 1;
    }
    return base * power(base, exponent-1);
}

// Tidskompleksitet: O(2^n) (eksponentiell, naiv Fibonacci)\n// Plasskompleksitet: O(n) (maksimal rekursjonsdybde)
int fibonacci(int n) {
    if (n <= 1) {
    return 1;
    }
return fibonacci(n-1) + fibonacci(n-2);
}

// Tidskompleksitet: O(n^2) (substr kopierer O(n) hver av n kall)\n// Plasskompleksitet: O(n^2) (rekursjonsstakk + samtidige string-kopier)\n// (Merk: Uten å telle kopi-størrelser er ekstra plass O(n))
int countOccurrences(std::string s, char c) {
    if (s.length() == 0) {
        return 0;
    }
    int lastCount = (s.back() == c) ? 1 : 0;
    s = s.substr(0, s.length() - 1);
    return lastCount + countOccurrences(s, c);
}



// Tidskompleksitet: O(n) (alle elementer besøkes én gang)\n// Plasskompleksitet: O(log n) (rekursjonsdybde ved todeling)
int findLargestElement(int arr[], int size) {
    if (size == 1) {
        return arr[0];
    }
    int mid = size / 2;
    int highestLeft = findLargestElement(arr, mid);
    int highestRight = findLargestElement(arr + mid, size - mid);
    return (highestLeft > highestRight) ? highestLeft : highestRight;
}

// Tidskompleksitet: O(k) der k = (end - start + 1); hvert tegn behandles to ganger men fortsatt O(k)\n// Plasskompleksitet: O(k) (rekursjonsdybde)
void traverseAsciiTable(char start, char end) {
    if (start > end) {
        return;
    }
    std::cout << start << " " << std::endl;
    traverseAsciiTable(start+1, end);
    std::cout << start << std::endl;
}

// Tidskompleksitet (main): Avhenger av input og de kallte funksjonene: O(n + exponent + 2^n + arrSize + range)\n// Plasskompleksitet (main): Summen av rekursjonsdybder nevnt over.
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
    std::cout << "Enter int n: " << std::endl;
    std::cin >> n;
    std::cin.ignore();
    std::cout << "Enter char for string occurence: " << std::endl;
    std::cin >> c;
    std::cin.ignore();
    std::cout << "Enter string: " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, s);
    std::cout << "Enter start for ascii traversal: " << std::endl;
    std::cin >> start;
    std::cin.ignore();
    std::cout << "Enter end for ascii traversal: " << std::endl;
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