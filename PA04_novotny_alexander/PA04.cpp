#include <iostream>
#include <random>
#include <ctime>


#include "Sort.h"

#define MAX_NUM_VALUES 100000
#define NUM_ITERATIONS 3
#define NUM_ALGORITHMS 3

#define MIN_VALUE 0
#define MAX_VALUE 1000000

void doAlgorithmTest ( std::mt19937*, unsigned );
void doAlgorithmIteration ( unsigned, std::mt19937*, sortData* );
void fillRandomValues ( unsigned* , unsigned, std::mt19937* );
void fillSortedValues ( unsigned*, unsigned );
void copyValues ( unsigned*, unsigned*, unsigned );
void printData ( sortData*, unsigned, unsigned );
void initRNG ( std::mt19937* );

void resetData ( sortData* );

int main ()
{
    std::mt19937 rng;

    initRNG ( &rng );

    for ( unsigned numValues = 1000; numValues <= MAX_NUM_VALUES; numValues *= 10 )
    {
        doAlgorithmTest ( &rng, numValues );
    }
    
}

void doAlgorithmTest ( std::mt19937* rng, unsigned numValues )
{
    sortData data [ NUM_ALGORITHMS ];

    resetData ( data );

    for ( unsigned iteration = 0; iteration < NUM_ITERATIONS; iteration++ )
    {
        doAlgorithmIteration ( numValues, rng, data );
    }

    printData ( data, numValues, NUM_ITERATIONS );

    std::cout << std::endl;
    resetData ( data );

    doAlgorithmIteration ( numValues, nullptr, data );

    std::cout << "Pre-sorted data:" << std::endl << std::endl;
    printData ( data, numValues, 1 );

    std::cout << "---------------------------------" << std::endl;
}

void doAlgorithmIteration ( unsigned numValues, std::mt19937* rng, sortData* data )
{
    unsigned* master_values = new unsigned [ numValues ];
    unsigned* temp_values = new unsigned [ numValues ];
    unsigned* sorted_values = new unsigned [ numValues ];
    std::chrono::high_resolution_clock::time_point start;
    
    if ( rng != nullptr )
    {
        fillRandomValues ( master_values, numValues, rng );
    }
    else
    {
        fillSortedValues ( master_values, numValues );
    }

    copyValues ( master_values, temp_values, numValues );
    start = std::chrono::high_resolution_clock::now ();
    insertionSort ( temp_values, numValues, data );
    data [ 0 ].time += std::chrono::duration_cast<std::chrono::nanoseconds>
        ( std::chrono::high_resolution_clock::now () - start );

    //std::cout << "Insertion sorted: " << isSorted ( temp_values, numValues ) << std::endl;

    copyValues ( master_values, temp_values, numValues );
    start = std::chrono::high_resolution_clock::now ();
    quickSort ( temp_values, numValues, data + 1 );
    data [ 1 ].time += std::chrono::duration_cast<std::chrono::nanoseconds>
        ( std::chrono::high_resolution_clock::now () - start );

    //std::cout << "Quick sorted: " << isSorted ( temp_values, numValues ) << std::endl;

    copyValues ( master_values, temp_values, numValues );
    start = std::chrono::high_resolution_clock::now ();
    countingSort ( temp_values, sorted_values, numValues, MAX_VALUE, data + 2 );
    data [ 2 ].time += std::chrono::duration_cast<std::chrono::nanoseconds>
        ( std::chrono::high_resolution_clock::now () - start );

    //std::cout << "Count sorted: " << isSorted ( sorted_values, numValues ) << std::endl;

    delete[] master_values;
    delete[] temp_values;
    delete[] sorted_values;
}

void fillRandomValues ( unsigned* values, unsigned size, std::mt19937* rng )
{
    std::uniform_int_distribution<unsigned> valueDistribution ( MIN_VALUE, MAX_VALUE );
    for ( unsigned valueIndex = 0; valueIndex < size; valueIndex++ )
    {
        values [ valueIndex ] = valueDistribution ( *rng );
    }
}

void fillSortedValues ( unsigned* values, unsigned size )
{
    for ( unsigned valueIndex = 0; valueIndex < size; valueIndex++ )
    {
        values [ valueIndex ] = valueIndex;
    }
}

void copyValues ( unsigned* from, unsigned* to, unsigned size )
{
    for ( unsigned index = 0; index < size; index++ )
    {
        to [ index ] = from [ index ];
    }
}

void printData ( sortData* data, unsigned numValues, unsigned numIterations )
{
    std::cout << "Average time for Insertion Sort on " << numValues
        << " values: " << data [ 0 ].time.count () / numIterations << std::endl;
    std::cout << "Average swaps: " << data [ 0 ].swaps / numIterations
        << ", comparisons: " << data [ 0 ].comparisons / numIterations << std::endl;
    std::cout << "Average time for Quick Sort on " << numValues
        << " values: " << data [ 1 ].time.count () / numIterations << std::endl;
    std::cout << "Average swaps: " << data [ 1 ].swaps / numIterations
        << ", comparisons: " << data [ 1 ].comparisons / numIterations << std::endl;
    std::cout << "Average time for Counting Sort on " << numValues
        << " values: " << data [ 2 ].time.count () / numIterations << std::endl;
    std::cout << "Average swaps: " << data [ 2 ].swaps / numIterations
        << ", comparisons: " << data [ 2 ].comparisons / numIterations << std::endl;
}

void initRNG ( std::mt19937* rng )
{
    std::random_device rd;
    unsigned seed = rd.entropy () ? rd () : std::time ( NULL );
    rng->seed ( seed );
}

void resetData ( sortData* data )
{
    for ( int index = 0; index < NUM_ALGORITHMS; index++ )
    {
        data [ index ].comparisons = 0;
        data [ index ].swaps = 0;
        data [ index ].time = data [ index ].time.zero ();
    }
}