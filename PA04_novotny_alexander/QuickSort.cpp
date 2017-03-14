// IMPLEMENTATION FILE ////////////////////////////////////////////////////////
/**
  * @file QuickSort.cpp
  *
  * @brief implementation of the quick sort algorithm from Sort.h
  *
  * @version 1.00
  *          Alexander Novotny
  *          First Version
  */
#include "Sort.h"

unsigned partition ( unsigned*, unsigned, sortData* = nullptr );

/**
  * @brief Sorts an array
  *
  * @par Algorithm
  *      Splits the array into two around a central pivot, then repeats
  *      on those smaller halves. Uses insertionSort for when size <= 2
  *
  * @param[in] values
  *            The array to sort
  *
  * @param[in] size
  *            The size of values
  *
  * @param[out] data
  *             Keeps track of algorithm data such as comparisons and swaps performed
  */
void quickSort ( unsigned* values, unsigned size, sortData* data )
{
    if ( size > 2 )
    {
        unsigned pivotIndex = partition ( values, size, data);

        quickSort ( values, pivotIndex, data );
        quickSort ( values + pivotIndex + 1, size - pivotIndex - 1, data );
    }
    else
    {
        insertionSort ( values, size, data );
    }
}

/**
  * @brief Splits an array in two around a central pivot
  *
  * @details Used by quickSort() as the main sorting function
  *
  * @par Algorithm
  *      Chooses a "pivot" value randomly from values. Loop through the array
  *      from the outer edges into the center, looking for values which are
  *      less than or greater than the pivot value, and swap them so that
  *      the array gets split into two - one half less than the pivot and
  *      the other greater
  *
  * @param[in] values
  *            The array of values to swap
  *
  * @param[in] size
  *            The size of values
  *
  * @param[out] data
  *             Keeps track of algorithm data such as comparisons and swaps performed
  *
  * @return The index of the pivot
  */
unsigned partition ( unsigned* values, unsigned size, sortData* data )
{
    unsigned pivotValue;
    unsigned indexFromLeft = 0;
    unsigned indexFromRight = size - 2;

    //static std::ofstream logFile ( "log.txt" );

    //Choose a random value in the array and place it at the end
    //This value is now our pivot
    std::swap ( values [ rand () % size ], values [ size - 1 ] );
    pivotValue = values [ size - 1 ];

    //Keep going until indexFromLeft and indexFromRight cross each other at the center
    while ( indexFromLeft < indexFromRight )
    {
        if ( data != nullptr ) data->comparisons++;
        //Starting from the left, keep going right until we find a value greater than pivot
        while ( values [ indexFromLeft ] < pivotValue)
        {
            if ( data != nullptr ) data->comparisons++;
            indexFromLeft++;
        }

        //Starting from the right, keep going until we find a value less than pivot
        while ( values [ indexFromRight ] > pivotValue && indexFromRight > 0 )
        {
            if ( data != nullptr ) data->comparisons++;
            indexFromRight--;
        }

        //Swap the two values we just found
        if ( indexFromLeft < indexFromRight )
        {
            std::swap ( values [ indexFromLeft ], values [ indexFromRight ] );

            if ( data != nullptr ) data->swaps++;
            
            indexFromLeft++;
            if(indexFromRight >= indexFromLeft) indexFromRight--;
        }
    }

    //Every now and then, indexFromLeft and indexFromRight will be one apart while swapping
    //And will then end up on the same index
    //We need to decide on which side of the pivot that index belongs
    if ( values [ indexFromLeft ] < pivotValue )
    {
        indexFromLeft++;
    }

    //Now, nicely place our pivot in the center
    std::swap ( values [ indexFromLeft ], values [ size - 1 ] );
    if ( data != nullptr ) data->swaps++;

    return indexFromLeft;
}