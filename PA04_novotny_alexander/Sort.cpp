#include "Sort.h"

bool isSorted ( unsigned* values, unsigned size )
{
    for ( unsigned index = 0; index < size - 1; index++ )
    {
        if ( values [ index ] > values [ index + 1 ] )
        {
            //std::cout << "Failed comparing " 
            //    << values [ index ] << " < " << values [ index + 1 ] << std::endl;
            return false;
        }
    }
    return true;
}