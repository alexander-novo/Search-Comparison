#include "Sort.h"

unsigned partition ( unsigned*, unsigned, sortData* = nullptr );

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

unsigned partition ( unsigned* values, unsigned size, sortData* data )
{
    unsigned pivotValue;
    unsigned indexFromLeft = 0;
    unsigned indexFromRight = size - 2;

    //static std::ofstream logFile ( "log.txt" );

    std::swap ( values [ rand () % size ], values [ size - 1 ] );

    pivotValue = values [ size - 1 ];

    /*for ( int i = 0; i < size - 1; i++ )
    {
        logFile << " " << values [ i ] << " ";
    }

    logFile << "[" << values [ size - 1 ] << "]" << std::endl;*/

    while ( indexFromLeft < indexFromRight )
    {
        if ( data != nullptr ) data->comparisons++;
        while ( values [ indexFromLeft ] < pivotValue)
        {
            if ( data != nullptr ) data->comparisons++;
            indexFromLeft++;
        }

        while ( values [ indexFromRight ] > pivotValue && indexFromRight > 0 )
        {
            if ( data != nullptr ) data->comparisons++;
            indexFromRight--;
        }

        if ( indexFromLeft < indexFromRight )
        {
            //logFile << "Swapping " << values [ indexFromLeft ] << ", " << values [ indexFromRight ] << std::endl;
            std::swap ( values [ indexFromLeft ], values [ indexFromRight ] );

            if ( data != nullptr ) data->swaps++;
            
            indexFromLeft++;
            if(indexFromRight >= indexFromLeft) indexFromRight--;
        }
    }

    if ( values [ indexFromLeft ] < pivotValue ) indexFromLeft++;

    std::swap ( values [ indexFromLeft ], values [ size - 1 ] );
    if ( data != nullptr ) data->swaps++;

   /* for ( int i = 0; i < size; i++ )
    {
        if ( i == indexFromLeft )
        {
            logFile << "[" << values [ i ] << "]";
        }
        else
        {
            logFile << " " << values [ i ] << " ";
        }

    }

    logFile << std::endl;*/
    return indexFromLeft;
}