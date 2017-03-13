#include "Sort.h"

void countingSort ( unsigned* values, unsigned* re,
                    unsigned size, unsigned max, sortData* data )
{
    unsigned* count = new unsigned [ max + 1 ];
    memset ( count, 0, sizeof ( *count ) * ( max + 1 ) );

    for ( int valueIndex = 0; valueIndex < size; valueIndex++ )
    {
        count [ values [ valueIndex ] ]++;
        if ( data != nullptr ) data->comparisons++;
    }

    for ( int countIndex = 1; countIndex < max; countIndex++ )
    {
        count [ countIndex ] += count [ countIndex - 1 ];
        if ( data != nullptr ) data->comparisons++;
    }

    for ( int valueIndex = 0; valueIndex < size; valueIndex++ )
    {
        re [ count [ values [ valueIndex ] ] - 1 ] = values [ valueIndex ];
        count [ values [ valueIndex ] ]--;
        if ( data != nullptr ) data->swaps++;
    }

    delete[] count;
}