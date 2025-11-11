#include <iostream>
#include <>

typedef struct _TSummary {
    long long comparisonCount;
    long long swaps;
    double timeTaken;
} TSummmary;
static _TSummary stats;

static void resetStats() {
    stats.comparisonCount = 0;
    stats.swaps = 0;
	stats.timeTaken = (static_cast<double>(clock())) / CLOCKS_PER_SEC;
}

static void printStastics() {
    stats.timeTaken = (static_cast<double>(clock())) / CLOCKS_PER_SEC - stats.timeTaken;
    std::cout << "Comparisons: " << stats.comparisonCount << ", Swaps: " << stats.swaps << ", Time taken : " << statistics.timeTaken << " seconds." << std::endl;
}

static EBankAccountType getRandomAccountType() {

}

void main() {



}
