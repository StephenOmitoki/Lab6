#ifndef MEMORY_SIM_H
#define MEMORY_SIM_H

#include <vector>
#include <utility>

using namespace std;

// Constants
const int MEMORY_SIZE = 1000;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int MIN_LEASE = 40;
const int MAX_LEASE = 70;
const int TIME_LIMIT = 1000;
const int REQUEST_INTERVAL = 10;

// Type definitions
using range = pair<int, int>;   // {start, size}
using alloc = pair<range, int>; // {allocated range, lease expiry}

// Function declarations
void generateRequest(vector<range>& freeList, vector<alloc>& allocatedList, int clock,
                     int& totalRequests, int& satisfiedRequests, int& unsatisfiedRequests,
                     int& mergeCount, int& smallestBlock, int& largestBlock,
                     double& totalBlockSize, int& shortestLease, int& longestLease, double& totalLeaseDuration);

void checkExpiredLeases(vector<range>& freeList, vector<alloc>& allocatedList, int clock);
void mergeFreeList(vector<range>& freeList);
void printResults(const vector<range>& freeList, const vector<alloc>& allocatedList,
                  int totalRequests, int satisfiedRequests, int unsatisfiedRequests,
                  int smallestBlock, int largestBlock, double avgBlockSize,
                  int shortestLease, int longestLease, double avgLeaseDuration, int mergeCount);

#endif
