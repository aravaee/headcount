/**
 * @file Analytics.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class provides us with a statisical analysis of our data given by the object detection video feed.
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <algorithm>

#include "Analytics.h"

/**
 * @brief Construct a new Analytics Object to perform our statistical analysis
 * First vector containing all entry times to the store in seconds,
 * Second vector containing all exit times to the store in seconds
 * Last integer is the max capacity of the store set by the owner
 * 
 * @param enterVector 
 * @param exitVector 
 * @param maxCapacity 
 */
Analytics::Analytics(std::vector<int> enterVector, std::vector<int> exitVector, int maxCapacity)
{
    mEnterVector = enterVector; // Setting the member variable to the enter times of the vector given to us by the user
    mExitVector = exitVector;   // Setting the member variable to the exit times of the vector given to us by the user
    mMaxCapacity = maxCapacity;

    // mSize represents the number of store actions for both entries or exits
    if (mEnterVector.size() == mExitVector.size())
    {
        mSize = mEnterVector.size();
    }
    // The vectors passed through the analytics class should already be the same size, otherwise throw an error (exit).
    else
    {
        exit(0);
    }
    // Checking if there is any data inside the vectors to work with.
    if (mSize == 0)
    {
        exit(1);
    }
}

/**
 * @brief This function uses the mEnterVector and mExitVector to create a vector containing the count of people after every update in the store (entry/exit)
 *  Containing every update of entry/exit in the vector
 * @return std::vector<int> 
 */
std::vector<int> Analytics::storeUpdates()
{
    std::vector<int> countPeople;                                           // this vectors store the amount of people in the store at a given time.
    int totalCount = 0, currCount = 0, enterPosition = 0, exitPosition = 0; // Tracks the position of the people exiting and entering

    // Calculates the current count of the store by keep comparing the size of the enterVector and exitVector at the different times (seconds)
    for (int i = 0; i < mSize * 2; i++)
    {
        if (mEnterVector[enterPosition] <= mExitVector[exitPosition] && enterPosition < mSize)
        {
            currCount++;
            countPeople.push_back(currCount);
            enterPosition++;
        }
        else
        {
            currCount--;
            countPeople.push_back(currCount);
            exitPosition++;
        }
    }
    return countPeople;
}

/**
 * @brief This function returns the average time a person spends inside a store.
 * Returns the average time people spend in store
 * @return double 
 */
double Analytics::averageTimeInStore()
{
    double sumTime = 0.; // creating a variable to store the sum of times of the vectors

    for (int i = 0; i < mSize; i++)
    {
        sumTime += mExitVector[i] - mEnterVector[i]; // Accumulating the time of the vectors inside
    }

    return ((double)sumTime / (double)mSize); // Dividing the accumulated sum by the size of the vector to get the average time spent
}

/**
 * @brief This function calculates the average number of people inside the store
 * Returns the avg number of people in store
 * @return double 
 */
double Analytics::averagePeopleEntry()
{
    std::vector<int> countPeople; // this vectors store the amount of people in the store at every entry/exit
    countPeople = storeUpdates();
    int totalCount = 0;

    // counting the totalCount of people in store which'll then be averaged out
    for (int i = 0; i < countPeople.size(); i++)
    {
        totalCount += countPeople[i];
    }

    return ((double)totalCount / (double)countPeople.size());
}

/**
 * @brief calculates the number of people that entered the store
 * Returns the number of enteries
 * @return int 
 */
int Analytics::numberOfEntries()
{
    return mSize;
}

/**
 * @brief calculates the max number of people in the store
 * Returns the max number of people that were ever in store
 * @return int 
 */
int Analytics::maxNumberPerDay()
{
    std::vector<int> countPeople; // this vectors store the amount of people in the store at every entry/exit
    countPeople = storeUpdates(); // returns a vector with a log of store occupancy. The max of index that vector will be the max number per day
    return *std::max_element(countPeople.begin(), countPeople.end());
}

/**
 * @brief calculates the times the max capacity of the store was reached by the customers
 * Returns occurrances containing the number of times the max capacity was reached
 * @return int 
 */
int Analytics::maxCapacityOccurences()
{
    std::vector<int> countPeople; // this vectors store the amount of people in the store at every entry/exit
    countPeople = storeUpdates();
    int occurrances = 0;

    for (int i = 0; i < countPeople.size(); i++)
    {
        if (countPeople[i] == mMaxCapacity)
            occurrances++;
    }
    return occurrances;
}

/**
 * @brief this returns a vector with the time of people entering
 * Returns a vector containing the times in seconds of all store enteries
 * @return std::vector<int> 
 */
std::vector<int> Analytics::getEnterVector()
{
    return mEnterVector;
}

/**
 * @brief: this returns a vector with the time of people exiting
 * @param: None
 * @return: vector
 */
std::vector<int> Analytics::getExitVector()
{
    return mExitVector;
}

/**
 * @brief Destroy the Analytics object
 * 
 */
Analytics::~Analytics()
{
}
