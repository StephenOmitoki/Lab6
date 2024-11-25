# Lab6

This program simulates a memory management system in C++, maintaining two lists:

A free memory list containing available memory holes.
A list of allocated requests, tracking satisfied memory requests and their lease durations.

It handles operations like generating memory requests, checking for expired leases, merging adjacent memory holes, and printing a detailed simulation report.

How to Run:
Compile and run the program using a C++ compiler. 
Execute the main function to begin the simulation.

Functionalities:

Initialization:
The free memory list is initialized with a single block representing the entire memory space.

Memory Request Generation:
Simulates requests for memory allocation and determines whether the request can be satisfied based on the available memory.

Lease Expiry Check:
Automatically returns expired allocated blocks to the free memory list and attempts to merge adjacent holes.

Merging Free Blocks:
Ensures that adjacent memory holes are combined to optimize available memory.

Statistics Calculation:

Tracks and reports simulation statistics, including:
Total, satisfied, and unsatisfied requests.
Minimum, maximum, and average block sizes.
Minimum, maximum, and average lease durations.
The total number of memory merges performed.

Simulation Report:
Provides a comprehensive report with lists of free and allocated memory blocks and detailed metrics.

Program Flow:

Initialization:

The free memory list starts with a single range covering the entire memory space.
The allocated list is empty at the start.

Main Simulation Loop:

In each cycle, the program:
Checks for expired leases.
Generates memory requests at regular intervals.
Updates statistics if requests are satisfied.

Final Report:

Outputs the memory state and detailed simulation metrics.

Requirements:
A C++ compatible compiler.
