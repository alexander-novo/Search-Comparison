#pragma once

#include <cstdlib>
#include <utility>
#include <chrono>

struct sortData
{
    unsigned comparisons;
    unsigned swaps;
    std::chrono::nanoseconds time;
};

void insertionSort ( unsigned* values, unsigned size, sortData* = nullptr );

void quickSort ( unsigned* values, unsigned size, sortData* = nullptr);

void countingSort ( unsigned* values, unsigned* re, unsigned size, unsigned max, sortData* = nullptr);

bool isSorted ( unsigned* values, unsigned size );