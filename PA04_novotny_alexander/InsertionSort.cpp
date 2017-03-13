#include "Sort.h"

void insertionSort ( unsigned* values, unsigned size, sortData* data )
{
    //Loop through every value in the array
    //We can skip 0 because it can't be shifted
    for ( unsigned sortedSize = 1; sortedSize < size; sortedSize++ )
    {
        //Look at the next value after the sorted part of the array
        unsigned nextSort = values [ sortedSize ];

        if ( data != nullptr ) data->comparisons++;

        //Starting from where we are, keep going backwards until we find a smaller value
        //Every time we move backwards, shift our values forward
        unsigned insertIndex;
        for ( insertIndex = sortedSize;
            ( insertIndex > 0 ) && ( values [ insertIndex - 1 ] > nextSort );
              insertIndex-- )
        {
            values [ insertIndex ] = values [ insertIndex - 1 ];
            if ( data != nullptr ) data->swaps++;
        }

        //The space we've just created is where our value goes
        values [ insertIndex ] = nextSort;
    }
}