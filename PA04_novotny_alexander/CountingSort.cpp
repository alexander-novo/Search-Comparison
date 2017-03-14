#include "Sort.h"

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