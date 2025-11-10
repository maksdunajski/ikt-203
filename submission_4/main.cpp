#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib> // For rand()
#include <random> // For better random number generation
#include <ctime>
#include <cstring> // For memset
#include <cmath>   // For floor
#include <chrono>  // For time manipulation
#include <locale>  // For locale settings
#include <codecvt> // For codecvt_utf8
#include <stdexcept> // For std::invalid_argument
#include <string>

template <typename T>
std::string toString(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}




enum EBankAccountType {
    Checking,
    Savings,
    Credit,
    Pension,
    Loan
};

class TBankAccount {
private:
    std::string accountNumber;
    EBankAccountType accountType;
    time_t creationTimestamp;
    double balance;

public:
    std::string ownerFirstName;
    std::string ownerLastName;

    //TBankAccount(EBankAccountType, std::string, std::string);
    ~TBankAccount();

 // //   std::string getAccountNumber() const;
 //    std::string getCreationTimeString() const;
 //    time_t getCreationTimestamp() const;
 //    double getBalance() const;
 //    void deposit(double);
 //    bool withdraw(double);
 //    EBankAccountType getAccountType() const;
 //    std::string getAccountTypeString() const;
 //    void printAccountInfo() const;

    TBankAccount(EBankAccountType accType, std::string firstName, std::string lastName) : accountType(accType), ownerFirstName(firstName), ownerLastName(lastName) {
        accountNumber = toString(rand() % 9000 + 1000) + "." + toString(rand() % 90 + 10) + "." + toString(rand() % 90000 + 10000);
        balance = 0.0f;

        int month = rand() % 12 + 1;
        int day = rand() % 28 + 1;
        int hour = rand() % 24;
        int minute = rand() % 60;

        std::tm tm = {};
        tm.tm_year = 2024 - 1900;
        tm.tm_mon = rand() % 12;
        tm.tm_mday = rand() % 28 + 1;
        tm.tm_hour = rand() % 24;
        tm.tm_min = rand() % 60;
        tm.tm_sec = 0;
        creationTimestamp = _mkgmtime(&tm);

    if (accType == Checking || accType == Savings || accType == Pension) {
        balance = rand() % 1001;
    }
        else if (accType == Loan) {
            balance=  rand() % 25001 + 25000;
        }
        else if (accType == Credit) {
            balance = -(rand() % 1001);
        }

    }

    std::string getAccountNumber() const {
        return accountNumber;
    }

    EBankAccountType getAccountType() const {
        return accountType;
    }

    time_t getCreationTimestamp() const {
        return creationTimestamp;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
        }
    }

    std::string getAccountTypeString() const {
        switch (accountType) {
            case Checking: return "Checking";
            case Savings: return "Savings";
            case Credit: return "Credit";
            case Pension: return "Pension";
            case Loan: return "Loan";
            default: return "Unknown";
        }
    }

    std::string getCreationTimeString() const {
        std::tm* tm = std::gmtime(&creationTimestamp);
        char buffer[30];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
        return std::string(buffer);
    }


    void printAccountInfo() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Type: " << getAccountTypeString() << std::endl;
        std::cout << "Owner: " << ownerFirstName << " " << ownerLastName << std::endl;
        std::cout << "Creation Time (UTC): " << getCreationTimeString() << std::endl;
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }
};

typedef bool (FCompareAccount)(TBankAccount* account, void* searchKey);
typedef void (FForEachAccount)(TBankAccount* account, int index);
typedef bool (FEveryAccount)(TBankAccount* account, int);

class TLinkedListNode {
public:
    TBankAccount* data;
    TLinkedListNode* next;
    TLinkedListNode(TBankAccount* account) : data(account), next(nullptr) {}
    ~TLinkedListNode(){}
};

class TLinkedList {
    TLinkedListNode* head;
    bool ownsData;
    int size;
public:
    TLinkedList(bool OwnsDat) : head(nullptr), ownsData(OwnsDat), size(0) {
        head = new TLinkedListNode(nullptr);
    }




    ~TLinkedList() {
        while (head->next != nullptr) {
            TLinkedListNode* temp = head->next;
            head->next = temp->next;
            if (ownsData) {
                delete temp->data;
            }
            delete temp;
        }
        delete head;
    }


    int getSize() const {return size;}

    TLinkedListNode* getHead() const {return head;}

    void add(TBankAccount* Data) {
        TLinkedListNode* newNode = new TLinkedListNode(Data);
        newNode->next = head->next;
        head->next = newNode;
        size++;
    }



    TBankAccount* Find(FCompareAccount CompareFunc, void* SearchKey ) {
        TLinkedListNode* current = head->next;
        while (current != nullptr) {
            if (CompareFunc(current->data, SearchKey)) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }



    TLinkedList* Every(FCompareAccount CompareFunc, void* SearchKey) {
        TLinkedList* resultList = new TLinkedList(false);
        TLinkedListNode* current = head->next;
        while (current != nullptr) {
            if (CompareFunc(current->data, SearchKey)) {
                resultList->add(current->data);
            }
            current = current->next;
        }
        return resultList;
    }

    TBankAccount* Every(FEveryAccount EveryFunc) {
        TLinkedListNode* current = head->next;
        int index = 0;
        while (current != nullptr) {
            if (!EveryFunc(current->data, index++)){
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    TBankAccount** ToArray() {
        if (size == 0) {
            return nullptr;
        }
        TBankAccount** array = new TBankAccount*[size];
        TLinkedListNode* current = head->next;
        int index = 0;
        while (current != nullptr && index < size) {
            array[index++] = current->data;
            current = current->next;
        }
        return array;
    }


    void forEach(FForEachAccount Func) {
        TLinkedListNode* current = head->next;
        int index = 0;
        while (current != nullptr) {
            Func(current->data, index++);
            current = current->next;
        }
    }



    void Append(TBankAccount* account){
        TLinkedListNode* newNode = new TLinkedListNode(account);
        TLinkedListNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        size++;
    }
    void Remove(TBankAccount* account) {
        TLinkedListNode* current = head;
        while (current->next != nullptr) {
            if (current->next->data == account) {
                TLinkedListNode* temp = current->next;
                current->next = temp->next;
                if (ownsData) {
                    delete temp->data;
                }
                delete temp;
                size--;
                return;
            }
            current = current->next;
        }
    }





void main () {



}