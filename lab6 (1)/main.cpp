#include "memory_sim.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for random number generation

    vector<range> freeList = {{0, MEMORY_SIZE}}; // Initially, all memory is free
    vector<alloc> allocatedList;

    int clock = 0, totalRequests = 0, satisfiedRequests = 0, unsatisfiedRequests = 0, mergeCount = 0;
    int smallestBlock = INT_MAX, largestBlock = INT_MIN;
    int shortestLease = INT_MAX, longestLease = INT_MIN;
    double totalBlockSize = 0, totalLeaseDuration = 0;
    double avgBlockSize = 0, avgLeaseDuration = 0;

    do {
        // Check expired leases
        checkExpiredLeases(freeList, allocatedList, clock);

        // Generate request every REQUEST_INTERVAL
        if (clock % REQUEST_INTERVAL == 0) {
            generateRequest(freeList, allocatedList, clock, totalRequests, satisfiedRequests,
                            unsatisfiedRequests, mergeCount, smallestBlock, largestBlock,
                            totalBlockSize, shortestLease, longestLease, totalLeaseDuration);
        }
    } while (++clock <= TIME_LIMIT);

    // Calculate averages
    if (satisfiedRequests > 0) {
        avgBlockSize = totalBlockSize / satisfiedRequests;
    } else {
        avgBlockSize = 0;
    }

    if (satisfiedRequests > 0) {
        avgLeaseDuration = totalLeaseDuration / satisfiedRequests;
    } else {
        avgLeaseDuration = 0;
    }

    // Print simulation results
    printResults(freeList, allocatedList, totalRequests, satisfiedRequests, unsatisfiedRequests,
                 smallestBlock, largestBlock, avgBlockSize, shortestLease, longestLease, avgLeaseDuration, mergeCount);

    return 0;
}
