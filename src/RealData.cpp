/**
 * @file RealData.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @version 0.1
 * @date 2020-11-22
 * @copyright Copyright (c) 2020
 * This class takes data from the video object detection class containing all store enteries and exits and arranges the data by day and hour so it can be analysed
 */

#include "RealData.h"

 /**
 * @brief: Construct a RealData object which will contain all the entry/exit data from the Video objection class
 * @param: std::vector<std::vector<int> > data : 2d-vector that stores 2 vectors(1 with all entry times in seconds, two with all the exits times in seconds).
 * @return: none
 */
RealData::RealData(std::vector<std::vector<int> > data) {

    mData = data; //2d - vector that stores 2 vectors(1 with all entry times in seconds, two with all the exits times in seconds).
    mData = getTrimVector(mData); //trimming uneven values so the analytics class can process it
    mEnterVector = mData[0]; //first index of mData contains a vector with all entery times
    mExitVector = mData[1]; //second index of mData contains vector with all exit times
    mSize = mEnterVector.size(); //vectors are even so set mSize to the size of mEnter


    /* Checking if there is any data inside the vectors to work with. */
    if (mSize == 0) {
        perror("Your array is empty, there is no data to analyse");
        //exit(1);
    }

    // Storing last time an entry or exit happened
    int timeLast = 0;

    if (mSize > 0)
    {
        if (mEnterVector[mSize - 1] > mExitVector[mSize - 1])
        {
            timeLast = mEnterVector[mSize - 1];
        }
        else
        {
            timeLast = mExitVector[mSize - 1];
        }
    }

    mHours = (timeLast / 3600) + 1; //Calculating the number of hours the data spanned over
    mDays = (timeLast / (86400)) + 1; //Calculating the number of days the data spanned over
}


/**
* @brief: this function takes the RealData object with all the data and places it into a 2-d vector. The vector is arranged by day and each hour for the day. ex: [Day][Hourly analysis]
* @param: std::vector<std::vector<int> > data : 2d-vector that stores 2 vectors(1 with all entry times in seconds, two with all the exits times in seconds).
* @return: realVector - the 2d vector
*/
std::vector<std::vector<Analytics> > RealData::produceData() {

    std::vector<std::vector<Analytics> > realVector;

    if (mSize == 0) {
        return realVector;
    }

    std::vector<int> hourlyEnter;
    std::vector<int> hourlyExit;
    int enterPos = 0; //current position of the mEnter vector, need for splitting data to hourly.
    int exitPos = 0; //current position of the mExit vector, need for splitting to hourly.

    //Loop through each days and all it's hours
    for (int i = 1; i <= mDays; i++) {
        std::vector<Analytics> dayVector;
        for (int j = 1; j <= mHours; j++) {

            //Parsing the mEnterVector and splitting into hours. keep tracking current position of vectors
            while (mEnterVector[enterPos] < (j * 3600) && enterPos < mSize) {

                hourlyEnter.push_back(mEnterVector[enterPos]);
                enterPos++;
            }
            while (mExitVector[exitPos] < (j * 3600) && exitPos < mSize)
            {

                hourlyExit.push_back(mExitVector[exitPos]);
                exitPos++;
            }

            //hours are trimmed for the analysis class
            std::vector<std::vector<int> > trimVector;
            trimVector.push_back(hourlyEnter);
            trimVector.push_back(hourlyExit);
            trimVector = getTrimVector(trimVector);

            //Create an analytics object for the hour and push it to the day vector containing all days
            Analytics A(trimVector[0], trimVector[1], trimVector[1].size() - 5);
            dayVector.push_back(A);

            //Clear hourly vectors, so other hours can be made
            hourlyEnter.clear();
            hourlyExit.clear();
        }
        realVector.push_back(dayVector); //after each day is processed push it to the realVector
    }
    return realVector;

}

/**
* @brief: getter function for mSize
* @param: none
* @return: mSize- the size of the enterVector
*/
int RealData::getSize() { return mSize; }

/**
* @brief: getter function for mHours
* @param: none
* @return: mHours- the number of hours data was recorded for
*/
int RealData::getHours() { return mHours; }

/**
* @brief: getter function for mDays
* @param: none
* @return: mDays- the number of days data was recorded for
*/
int RealData::getDays() { return mDays; }

/**
* @brief: getter function to for mEnterVector
* @param: none
* @return: mEnterVector- the vector containing all the store enteries in seconds
*/
std::vector<int> RealData::getEnterVector() { return mEnterVector; }

/**
* @brief: getter function to for mExitVector
* @param: none
* @return: mExitVector- the vector containing all the store exits in seconds
*/
std::vector<int> RealData::getExitVector() { return mExitVector; }

/**
* @brief: getter function to for mData
* @param: none
* @return: mExitVector- the vector containing the vectors mEnterVector and mExitVector
*/
std::vector<std::vector<int> > RealData::getData() { return mData; }

/**
* @brief: this function trims uneven values comparing the mEnterVector and mExitVector
* @param: std::vector<std::vector<int> > data : 2d-vector that stores 2 vectors(1 with all entry times in seconds, two with all the exits times in seconds).
* @return: realVector - the 2d vector containing without uneven values
*/
std::vector<std::vector<int> > RealData::getTrimVector(std::vector<std::vector<int> > trimVector) {

    if (trimVector[0].size() != trimVector[1].size()) {

        int enterSize, exitSize, diff;
        enterSize = trimVector[0].size();
        exitSize = trimVector[1].size();

        if (enterSize > exitSize)
        {
            diff = enterSize - exitSize;
            for (int i = 0; i < diff; i++)
            {
                trimVector[0].pop_back();
            }
        }
        if (exitSize > enterSize)
        {
            diff = exitSize - enterSize;
            for (int i = 0; i < diff; i++)
            {
                trimVector[1].pop_back();
            }
        }
    }

    return trimVector;
}

/**
* @brief destructor for ReadData class
* @param None
*/
RealData::~RealData() {

}
