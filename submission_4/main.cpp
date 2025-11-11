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
#include <fstream>

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
};

typedef bool (*FNameRead)(const std::string& firstName, const std::string& lastName);

void readFile(const std::string& filename, FNameRead OnNameRead) {
    if (filename.empty()) {
        return;
    }
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string firstName, lastName;
        if (iss >> firstName >> lastName) {
            if (OnNameRead){
                if (!OnNameRead(firstName, lastName)) {
                    break;
                }
            }
        }
    }
}

typedef struct _TSummary {
    long comparisonCount;
    double timeTaken = 0.0;
} TSummary;
static TSummary stats;

static EBankAccountType getRandomAccType() {
    return static_cast<EBankAccountType>(rand() % 5);
}

TLinkedList* bankAccounts = new TLinkedList(true);
TBankAccount** bankAccountsArray = nullptr;

static bool OnNameRead(const std::string& firstName, const std::string& lastName) {
    int accCount = rand() % 2 + 5;
    for (int i = 0; i < accCount; i++) {
        EBankAccountType accType = getRandomAccType();
        TBankAccount* newAccount = new TBankAccount(accType, firstName, lastName);
        bankAccounts->add(newAccount);
    }
    return true;
}

static void resetStats() {
    stats.comparisonCount = 0;
    stats.timeTaken = (static_cast<double>(clock())) / CLOCKS_PER_SEC;
}

static void printStats() {
    stats.timeTaken = (static_cast<double>(clock()) / CLOCKS_PER_SEC) - stats.timeTaken;
    std::cout << "Comparisons: " << stats.comparisonCount << ", Time taken: " << stats.timeTaken << "sec." <<std::endl;
}

static TBankAccount* findAccByNumber(TBankAccount** accountArray, int size, const std::string& accNumber) {
    if (accountArray == nullptr || size == 0) {
        return nullptr;
    }
    for (int i = 0; i < size; i++) {
        stats.comparisonCount++;
        if (accountArray[i]->getAccountNumber() == accNumber) {
            return accountArray[i];
        }
    }
    return nullptr;
}

static void printEveryAccountInDateRange(TBankAccount** accountArray, int size, time_t from, time_t to) {
    if (accountArray == nullptr || size == 0) {
        return;
    }
    int foundCount = 0;
    resetStats();
    for (int i = 0; i < size; i++) {
        stats.comparisonCount++;
        time_t creationTime = accountArray[i]->getCreationTimestamp();
        if (creationTime >= from && creationTime <= to) {
            std::cout << i + 1 << ". Account found:" << std::endl;
            accountArray[i]->printAccountInfo();
            foundCount++;
        }
    }
    printStats();
    if (foundCount == 0) {
        std::cout << "No accounts found in the specified date range." << std::endl;
    }
    else {
        std::cout << "Total accounts found: " << foundCount << std::endl;
    }
}

void main() {
    std::cout << "--- Submission 4: Sosrt & Search ---" << std::endl;

	// Test TBankAccount
	//Gen random account type
	//Change this name for you own names file
	std::string namesFile = "../random_names.txt";
	std::cout << "Reading names from file: " << namesFile << std::endl;
	readFile(namesFile, OnNameRead);
	std::cout << "Total Bank Accounts Created: " << bankAccounts->getSize() << std::endl;
	std::cout << "Converting linked list to array..." << std::endl;
	bankAccountsArray = bankAccounts->ToArray();
	std::cout << "Array created with " << bankAccounts->getSize() << " accounts." << std::endl;


	resetStats();
	int getRandomIndex = rand() % bankAccounts->getSize();
	TBankAccount* foundAccount = findAccByNumber(bankAccountsArray, bankAccounts->getSize(), bankAccountsArray[getRandomIndex]->getAccountNumber());
	if (foundAccount)
	{
		std::cout << "Found Account: " << std::endl;
		foundAccount->printAccountInfo();
	}
	else
	{
		std::cout << "Account not found." << std::endl;
	}
	printStats();

	resetStats();
	foundAccount = findAccByNumber(bankAccountsArray, bankAccounts->getSize(), "1234.56.78901");
	if (foundAccount)
	{
		std::cout << "Found Account: " << std::endl;
		foundAccount->printAccountInfo();
	}
	else
	{
		std::cout << "Account not found." << std::endl;
	}
	printStats();

	// Find All (Integrated): Use your Every() method to find all accounts created in June 2024 and print their details.
	resetStats();
	struct June2024Key {
		time_t start;
		time_t end;
	};
	June2024Key juneKey{};
	std::tm fromToTm = {};
	fromToTm.tm_year = 2024 - 1900; // Year since 1900
	fromToTm.tm_mon = 5; // June (0-based)
	fromToTm.tm_mday = 1; // 1st
	fromToTm.tm_hour = 0;
	fromToTm.tm_min = 0;
	fromToTm.tm_sec = 0;
	juneKey.start = _mkgmtime(&fromToTm); // Use _mkgmtime for UTC
	fromToTm.tm_mday = 30; // 30th
	fromToTm.tm_hour = 23;
	fromToTm.tm_min = 59;
	fromToTm.tm_sec = 59;
	juneKey.end = _mkgmtime(&fromToTm); // Use _mkgmtime for UTC

	TLinkedList* juneAccounts = bankAccounts->Every(
		[](TBankAccount* account, void* searchKey) -> bool {
			June2024Key* key = static_cast<June2024Key*>(searchKey);
			time_t ts = account->getCreationTimestamp();
			return ts >= key->start && ts < key->end;
		}, &juneKey);

	std::cout << "Accounts created in June 2024: " << juneAccounts->getSize() << std::endl;
	printStats();

	juneAccounts->forEach(
		[](TBankAccount* aAccount, int aIndex) {
			std::cout << aIndex + 1 << ". ";
			aAccount->printAccountInfo();
		});

	printEveryAccountInDateRange(bankAccountsArray, bankAccounts->getSize(), juneKey.start, juneKey.end);


	// Cleanup
	// First delete the array, then the linked list
	delete[] bankAccountsArray;
	delete bankAccounts;
}