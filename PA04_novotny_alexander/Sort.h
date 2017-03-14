// HEADER INFORMATION /////////////////////////////////////////////////////////
/**
  * @file Sort.h
  * 
  * @brief Contains sorting algorithms and misc. functions and structs related
  *
  * @version 1.00
  *          Alexander Novotny
  *          First version
  */
#pragma once

// INCLUDES ///////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <utility>
#include <chrono>
#include <cstring>


// STRUCT DEFINITION //////////////////////////////////////////////////////////
//Used to keep track of algorithm metrics
struct sortData
{
    unsigned comparisons;
    unsigned swaps;
    std::chrono::nanoseconds time;
};
// SORTING FUNCTIONS //////////////////////////////////////////////////////////

void insertionSort ( unsigned* values, unsigned size, sortData* = nullptr );

void quickSort ( unsigned* values, unsigned size, sortData* = nullptr);

void countingSort ( unsigned* values, unsigned* re, unsigned size, unsigned max, sortData* = nullptr);

// UTILITY FUNCTIONS //////////////////////////////////////////////////////////

bool isSorted ( unsigned* values, unsigned size );