/**
 * @file RealData.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class takes data from the video object detection class containing all store enteries and exits and arranges the data by day and hour so it can be analysed
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __REALDATA_H
#define __REALDATA_H

#include "Analytics.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

/**
 * @brief Construct a RealData object which will contain all the entry/exit data from the Video objection class
 * 
 */
class RealData {
    /*2d - vector that stores 2 vectors(1 with all entry times in seconds, two with all the exits times in seconds).*/
    std::vector<std::vector<int> > mData;

    /*first index of mData contains a vector with all entery times*/
    std::vector<int> mEnterVector;

    /*second index of mData contains vector with all exit times*/
    std::vector<int> mExitVector;

    /*vectors are even so set mSize to the size of mEnter*/
    int mSize;

    /*Calculating the number of hours the data spanned over*/
    int mHours;

    /*Calculating the number of days the data spanned over*/
    int mDays;
public:

/**
* @brief: Construct a RealData object which will contain all the entry/exit data from the Video objection class
* @param: std::vector<std::vector<int> > data : 2d-vector that stores 2 vectors(1 with all entry times in seconds, two with all the exits times in seconds).
* @return: none
*/
    RealData(std::vector<std::vector<int> > data);


/**
* @brief: getter function for mSize
* @param: none
* @return: mSize- the size of the enterVector
*/
    int getSize();

/**
* @brief: getter function for mHours
* @param: none
* @return: mDays- the number of hours data was recorded for
*/
    int getHours();

/**
* @brief: getter function for mDays
* @param: none
* @return: mDays- the number of days data was recorded for
*/
    int getDays();

/**
* @brief: getter function to for mEnterVector
* @param: none
* @return: mEnterVector- the vector containing all the store enteries in seconds
*/
    std::vector<int> getEnterVector();

/**
* @brief: getter function to for mExitVector
* @param: none
* @return: mExitVector- the vector containing all the store exits in seconds
*/
    std::vector<int> getExitVector();

    /**
    * @brief: getter function to for mData
    * @param: none
    * @return: mData- the vector containing the vectors mEnterVector and mExitVector
    */
    std::vector<std::vector<int> > getData();

/**
* @brief: this function takes the RealData object with all the data and places it into a 2-d vector. The vector is arranged by day and each hour for the day. ex: [Day][Hourly analysis]
* @param: std::vector<std::vector<int> > data : 2d-vector that stores 2 vectors(1 with all entry times in seconds, two with all the exits times in seconds).
* @return: realVector - the 2d vector
*/
    std::vector<std::vector<Analytics> > produceData();

/**
* @brief: this function trims uneven values comparing the mEnterVector and mExitVector
* @param: std::vector<std::vector<int> > data : 2d-vector that stores 2 vectors(1 with all entry times in seconds, two with all the exits times in seconds).
* @return: realVector - the 2d vector containing without uneven values
*/
    std::vector<std::vector<int> > getTrimVector(std::vector<std::vector<int> > trimVector);

/**
* @brief destructor for ReadData class
* @param None
*/
    ~RealData();
};

#endif
