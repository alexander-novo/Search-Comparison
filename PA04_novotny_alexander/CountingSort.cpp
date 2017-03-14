// IMPLEMENTATION INFORMATION /////////////////////////////////////////////////
/**
  * @file CountingSort.cpp
  *
  * @brief Implementation of counting sort from Sort.h
  */
#include "Sort.h"

/**
  * @brief Sorts an array
  * 
  * @par Algorithm
  *      Counts every unique possible value, then figures out the index each
  *      value belongs in by adding the previous index to the count
  *
  * @pre re must be at least as large as values
  *
  * @pre values must not contain any values less than max
  *
  * @param[in] values
  *            The array to sort

  * @param[in] size
  *            The size of values
  *
  * @param[in] max
  *            The maximum possible value in values
  *
  * @param[out] re
  *             The sorted array
  *
  * @param[out] data
  *             Keeps track of algorithm data such as comparisons and swaps performed
  */
void countingSort ( unsigned* values, unsigned* re,
                    unsigned size, unsigned max, sortData* data )
{
    unsigned* count = new unsigned [ max + 1 ];
    unsigned trueMax = 0;
    memset ( count, 0, sizeof ( *count ) * ( max + 1 ) );

    for ( unsigned valueIndex = 0; valueIndex < size; valueIndex++ )
    {
        count [ values [ valueIndex ] ]++;
        if ( values [ valueIndex ] > trueMax ) trueMax = values [ valueIndex ];
        if ( data != nullptr ) data->comparisons++;
    }

    for ( unsigned countIndex = 1; countIndex < trueMax; countIndex++ )
    {
        count [ countIndex ] += count [ countIndex - 1 ];
        if ( data != nullptr ) data->comparisons++;
    }

    for ( unsigned valueIndex = 0; valueIndex < size; valueIndex++ )
    {
        re [ count [ values [ valueIndex ] ] - 1 ] = values [ valueIndex ];
        count [ values [ valueIndex ] ]--;
        if ( data != nullptr ) data->swaps++;
    }

    delete[] count;
}