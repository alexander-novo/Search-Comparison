// PROGRAM INFORMATION ////////////////////////////////////////////////////////
/**
  * @file PA04.cpp
  *
  * @brief Compares three sorting algorithms
  *
  * @details Generates random data multiple times and sorts it through
  *          insertion sort, quick sort, and counting sort. Keeps track of
  *          run time, comparisons, and swaps of each sorting algorithm.
  *
  * @version 1.00
  *          Alexander Novotny (3/13/2017)
  *          First Version
  */

// INCLUDES ///////////////////////////////////////////////////////////////////
#include <iostream>
#include <random>
#include <ctime>

#include "Sort.h"

// MACRO DEFINITIONS //////////////////////////////////////////////////////////
//The largest dataset size
#define MAX_NUM_VALUES 100000
//Number of time each algorithm should be run, per iteration
#define NUM_ITERATIONS 3
//Number of algorithms
#define NUM_ALGORITHMS 3

//Minimum and maximum random numbers
#define MIN_VALUE 0
#define MAX_VALUE 1000000

// FUNCTION PROTOTYPES ////////////////////////////////////////////////////////
void doAlgorithmTest ( std::mt19937*, unsigned );
void doAlgorithmIteration ( unsigned, std::mt19937*, sortData* );
void fillRandomValues ( unsigned* , unsigned, std::mt19937* );
void fillSortedValues ( unsigned*, unsigned );
void copyValues ( unsigned*, unsigned*, unsigned );
void printData ( sortData*, unsigned, unsigned );
void initRNG ( std::mt19937* );
void resetData ( sortData* );

// MAIN FUNCTION //////////////////////////////////////////////////////////////
int main ()
{
    std::mt19937 rng;

    //seed RNG
    initRNG ( &rng );

    //Run our algorithms with 1,000 10,000 and 100,000 values
    for ( unsigned numValues = 1000; numValues <= MAX_NUM_VALUES; numValues *= 10 )
    {
        doAlgorithmTest ( &rng, numValues );
    }
    
}

/**
  * @brief Tests several algorithms several times and prints information about them
  * 
  * @details Runs all sorting algorithms NUM_ITERATIONS times and prints out the
  *          mean run time, mean number of swaps, and mean number of comparisons.
  *          Generates random and pre-sorted data.
  *
  * @pre rng is already seeded
  *
  * @param[in] rng
  *            The random number generator to be used to generate the random mumbers
  *
  * @param[in] numValues
  *            The size of the dataset to generate and use
  */
void doAlgorithmTest ( std::mt19937* rng, unsigned numValues )
{
    sortData data [ NUM_ALGORITHMS ];

    //initialise
    resetData ( data );

    //run the algroithms NUM_ITERATIONS times to take the average of them all
    for ( unsigned iteration = 0; iteration < NUM_ITERATIONS; iteration++ )
    {
        doAlgorithmIteration ( numValues, rng, data );
    }

    //Now print our average data
    printData ( data, numValues, NUM_ITERATIONS );
    std::cout << std::endl;

    //And do it again for pre-sorted data
    resetData ( data );
    doAlgorithmIteration ( numValues, nullptr, data );

    std::cout << "Pre-sorted data:" << std::endl << std::endl;
    printData ( data, numValues, 1 );
    std::cout << "---------------------------------" << std::endl;
}

/**
  * @brief Runs several sorting algorithms on the same dataset
  *
  * @details Generates random numbers or pre-sorted numbers and runs all the
  *          sorting algorithms on them.
  *
  * @param[in] numValues
  *            The size of the dataset to generate and use
  *
  * @param[in] rng
  *            Pointer to the random number generator to use. nullptr to use
  *            pre-sorted data
  * 
  * @param[in] data
  *            Pointer to the variable to store data about the algorithms in
  */
void doAlgorithmIteration ( unsigned numValues, std::mt19937* rng, sortData* data )
{
    //Generate numbers into here
    unsigned* master_values = new unsigned [ numValues ];
    //Copy master values into here to sort
    unsigned* temp_values = new unsigned [ numValues ];
    //Timer variable
    std::chrono::high_resolution_clock::time_point start;
    
    //Random numbers or pre-sorted numbers
    if ( rng != nullptr )
    {
        fillRandomValues ( master_values, numValues, rng );
    }
    else
    {
        fillSortedValues ( master_values, numValues );
    }

    // ALGORITHMS

    copyValues ( master_values, temp_values, numValues );
    start = std::chrono::high_resolution_clock::now ();
    insertionSort ( temp_values, numValues, data );
    data [ 0 ].time += std::chrono::duration_cast<std::chrono::nanoseconds>
        ( std::chrono::high_resolution_clock::now () - start );

    copyValues ( master_values, temp_values, numValues );
    start = std::chrono::high_resolution_clock::now ();
    quickSort ( temp_values, numValues, data + 1 );
    data [ 1 ].time += std::chrono::duration_cast<std::chrono::nanoseconds>
        ( std::chrono::high_resolution_clock::now () - start );

    start = std::chrono::high_resolution_clock::now ();
    countingSort ( master_values, temp_values, numValues, MAX_VALUE, data + 2 );
    data [ 2 ].time += std::chrono::duration_cast<std::chrono::nanoseconds>
        ( std::chrono::high_resolution_clock::now () - start );

    delete[] master_values;
    delete[] temp_values;
}

/**
  * @brief Fills an array with random values
  *
  * @details Fills an array with random values between MIN_VALUE and MAX_VALUE
  *
  * @post values
  *       Will be filled with random values
  *
  * @param[in] values
  *            An array of numbers to be filled with random input. Size must
  *            be greater than or equal to size.
  *
  * @param[in] size
  *            The size of the value array
  *
  * @param[in] rng
  *            Pointer to the rng to use
  */
void fillRandomValues ( unsigned* values, unsigned size, std::mt19937* rng )
{
    std::uniform_int_distribution<unsigned> valueDistribution ( MIN_VALUE, MAX_VALUE );
    for ( unsigned valueIndex = 0; valueIndex < size; valueIndex++ )
    {
        values [ valueIndex ] = valueDistribution ( *rng );
    }
}

/**
  * @brief Fills an array with sorted values
  *
  * @post values
  *       Will be filled with sorted values
  *
  * @param[in] values
  *            An array to be filled with sorted input. Size must be greater
  *            than or equal to size.
  *
  * @param[in] size
  *            The size of the value array
  */
void fillSortedValues ( unsigned* values, unsigned size )
{
    for ( unsigned valueIndex = 0; valueIndex < size; valueIndex++ )
    {
        values [ valueIndex ] = valueIndex;
    }
}

/**
  * @brief Copies one array to another
  *
  * @pre from and to must be identical in size
  *
  * @post to will be identical to from
  *
  * @param[in] from
  *            The array to copy from
  *
  * @param[in] size
  *            The size of both arrays
  *
  * @param[out] to
  *             The array to copy to
  */
void copyValues ( unsigned* from, unsigned* to, unsigned size )
{
    for ( unsigned index = 0; index < size; index++ )
    {
        to [ index ] = from [ index ];
    }
}

/**
  * @brief Formats and prints sorting data
  *
  * @pre data should contain total amounts, to be averaged by the function
  *
  * @param[in] data
  *            An array of sorting data.
  *            data[0] should be insertion sort
  *            data[1] should be quick sort
  *            data[2] should be counting sort
  *
  * @param[in] numValues
  *            The number of values that were sorted
  *
  * @param[in] numIteration
  *            The number of iterations for purposes of finding averages
  */
void printData ( sortData* data, unsigned numValues, unsigned numIterations )
{
    std::cout << "Average time for Insertion Sort on " << numValues
        << " values: " << data [ 0 ].time.count () / numIterations << " nanoseconds" << std::endl;
    std::cout << "Average swaps: " << data [ 0 ].swaps / numIterations
        << ", comparisons: " << data [ 0 ].comparisons / numIterations << std::endl;
    std::cout << "Average time for Quick Sort on " << numValues
        << " values: " << data [ 1 ].time.count () / numIterations << " nanoseconds" << std::endl;
    std::cout << "Average swaps: " << data [ 1 ].swaps / numIterations
        << ", comparisons: " << data [ 1 ].comparisons / numIterations << std::endl;
    std::cout << "Average time for Counting Sort on " << numValues
        << " values: " << data [ 2 ].time.count () / numIterations << " nanoseconds" << std::endl;
    std::cout << "Average swaps: " << data [ 2 ].swaps / numIterations
        << ", comparisons: " << data [ 2 ].comparisons / numIterations << std::endl;
}

/**
  * @brief seeds an rng
  *
  * @details seeds an rng with a random_device or time if there is no entropy
  *
  * @post rng will be seeded
  *
  * @param[in] rng
  *            The rng to seed
  */
void initRNG ( std::mt19937* rng )
{
    std::random_device rd;
    unsigned seed = rd.entropy () ? rd () : std::time ( NULL );
    rng->seed ( seed );
}

/**
  * @brief initialises a sortData object
  *
  * @details Sets the comparisons and swaps of a sortData object to 0, and resets
  *          the timer.
  *
  * @post data will be re-initialised
  *
  * @param[out] data
  *             The data to initialise
  */
void resetData ( sortData* data )
{
    for ( int index = 0; index < NUM_ALGORITHMS; index++ )
    {
        data [ index ].comparisons = 0;
        data [ index ].swaps = 0;
        data [ index ].time = data [ index ].time.zero ();
    }
}