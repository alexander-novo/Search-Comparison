// IMPLEMENTATION INFORMATION /////////////////////////////////////////////////
/**
  * @file Sort.cpp
  *
  * @brief Contains misc. functions for Sort.h
  *
  * @version 1.00
  *          Alexander Novotny
  *          First Version
  */
#include "Sort.h"

/**
  * @brief Checks if an array is sorted
  *
  * @param[in] values
  *            Array to check
  *
  * @param[in] size
  *            size of values
  */
bool isSorted ( unsigned* values, unsigned size )
{
    for ( unsigned index = 0; index < size - 1; index++ )
    {
        if ( values [ index ] > values [ index + 1 ] )
        {
            return false;
        }
    }
    return true;
}