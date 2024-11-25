#include "memory_sim.h"
#include <algorithm>
#include <iostream>
#include <vector>

void generateRequest(vector<range>& freeList, vector<alloc>& allocatedList, int clock,
                     int& totalRequests, int& satisfiedRequests, int& unsatisfiedRequests,
                     int& mergeCount, int& smallestBlock, int& largestBlock,
                     double& totalBlockSize, int& shortestLease, int& longestLease, double& totalLeaseDuration) {
    totalRequests++;

    int blockSize = rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE;
    int leaseDuration = rand() % (MAX_LEASE - MIN_LEASE + 1) + MIN_LEASE;
    int leaseExpiry = clock + leaseDuration;

    bool requestSatisfied = false;

    for (auto it = freeList.begin(); it != freeList.end(); ++it) {
        if (it->second >= blockSize) {
            // Allocate memory
            satisfiedRequests++;
            range allocated = {it->first, blockSize};
            allocatedList.push_back({allocated, leaseExpiry});

            // Update free list
            it->first += blockSize;
            it->second -= blockSize;
            if (it->second == 0) {
                freeList.erase(it);
            }

            // Update statistics
            if (blockSize < smallestBlock) {
                smallestBlock = blockSize;
            }
            if (blockSize > largestBlock) {
                largestBlock = blockSize;
            }
            totalBlockSize += blockSize;

            if (leaseDuration < shortestLease) {
                shortestLease = leaseDuration;
            }
            if (leaseDuration > longestLease) {
                longestLease = leaseDuration;
            }
            totalLeaseDuration += leaseDuration;

            requestSatisfied = true;
            break;
        }
    }

    if (!requestSatisfied) {
        unsatisfiedRequests++;
        mergeFreeList(freeList);
        mergeCount++;
    }
}

void checkExpiredLeases(vector<range>& freeList, vector<alloc>& allocatedList, int clock) {
    for (auto it = allocatedList.begin(); it != allocatedList.end(); ) {
        if (it->second <= clock) {
            // Return expired block to free list
            freeList.push_back(it->first);
            it = allocatedList.erase(it);
        } else {
            ++it;
        }
    }
    mergeFreeList(freeList);
}

void mergeFreeList(vector<range>& freeList) {
    sort(freeList.begin(), freeList.end());

    for (size_t i = 0; i < freeList.size() - 1; ++i) {
        if (freeList[i].first + freeList[i].second == freeList[i + 1].first) {
            freeList[i].second += freeList[i + 1].second;
            freeList.erase(freeList.begin() + i + 1);
            --i;
        }
    }
}

void printResults(const vector<range>& freeList, const vector<alloc>& allocatedList,
                  int totalRequests, int satisfiedRequests, int unsatisfiedRequests,
                  int smallestBlock, int largestBlock, double avgBlockSize,
                  int shortestLease, int longestLease, double avgLeaseDuration, int mergeCount) {
    cout << "Free Memory Blocks:\n";
    for (const auto& block : freeList) {
        cout << "[" << block.first << "," << block.second << "]";
    }
    cout << "\n";

    cout << "Allocated Memory Blocks:\n";
    for (const auto& allocation : allocatedList) {
        cout << "[" << allocation.first.first << "," << allocation.first.second << "]";
    }
    cout << "\n";

    cout << "\nSimulation Report:\n";
    cout << "Total Requests: " << totalRequests << "\n";
    cout << "Satisfied Requests: " << satisfiedRequests << "\n";
    cout << "Unsatisfied Requests: " << unsatisfiedRequests << "\n";
    cout << "Block Size-Min: " << smallestBlock << "\n";
    cout << "Block Size-Max: " << largestBlock << "\n";
    cout << "Block Size-Avg: " << avgBlockSize << "\n";
    cout << "Lease Duration-Min: " << shortestLease << "\n";
    cout << "Lease Duration-Max: " << longestLease << "\n";
    cout << "Lease Duration-Avg: " << avgLeaseDuration << "\n";
    cout << "Number of Merges: " << mergeCount << "\n";
}
