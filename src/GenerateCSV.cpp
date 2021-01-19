/**
 * @file GenerateCSV.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief 
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <cassert>
#include "GenerateCSV.h"

/**
 * @brief Create a GenerateCSV object to process the analytics and store them in a csv
 * First param is number of hours that the store is open for daily,
 * Second is number of days that the analysis is being made for, 
 * The last vector is matrix that stores every days, all it's hours, and the analysis object for each.
 * @param hours 
 * @param days 
 * @param vector 
 */
GenerateCSV::GenerateCSV(int hours, int days, std::vector<std::vector<Analytics>> vector)
{
    mHours = hours;
    mDays = days;
    mVector = vector;
}

/**
 * @brief retrieves the average time spent in store and stores it into a csv
 * First param is the name of the csv file to write the data to
 * @param filename 
 */
void GenerateCSV::generateAverageTimeInStore(std::string filename)
{

    std::ofstream writeOutput(filename);
    assert(writeOutput.is_open());
    double dailyAvg = 0.;

    for (int i = 0; i < mVector.size(); i++)
    {
        for (int j = 0; j < mVector[i].size(); j++)
        {
            if (j < mVector[i].size() - 1)
            {
                dailyAvg += (mVector[i][j].averageTimeInStore());
            }
        }
        dailyAvg = dailyAvg / (mVector[i].size());
        writeOutput << dailyAvg << "\n";
    }
    writeOutput.close();
}

/**
 * @brief retrieves the average number of enteries to the store and stores it into a csv
 * First param is the name of the csv file to write the data to
 * @param filename 
 */
void GenerateCSV::generateAveragePeopleEntry(std::string filename)
{

    std::ofstream writeOutput(filename);
    assert(writeOutput.is_open());
    double dailyAvg = 0.;

    // retrieving statistic from the vector, once retrieved write it to the pdf
    for (int i = 0; i < mVector.size(); i++)
    {
        for (int j = 0; j < mVector[i].size(); j++)
        {
            if (j < mVector[i].size() - 1)
            {
                dailyAvg += (mVector[i][j].averagePeopleEntry());
            }
        }
        dailyAvg = dailyAvg / (mVector[i].size());
        writeOutput << dailyAvg << "\n";
    }
    writeOutput.close();
}

/**
 * @brief retrieves the total enteries to the store and stores it into a csv
 * First param is the name of the csv file to write the data to
 * @param filename 
 */
void GenerateCSV::generateNumberOfEntries(std::string filename)
{

    std::ofstream writeOutput(filename);
    assert(writeOutput.is_open());
    int dailyAvg = 0;

    for (int i = 0; i < mVector.size(); i++)
    {
        for (int j = 0; j < mVector[i].size(); j++)
        {
            if (j < mVector[i].size() - 1)
            {
                dailyAvg += (mVector[i][j].numberOfEntries());
            }
        }

        dailyAvg = dailyAvg / (mVector[i].size());
        writeOutput << dailyAvg << "\n";
    }
    writeOutput.close();
}

/**
 * @brief retrieves the number of enteries to the store and stores it into a csv
 * First param is the name of the csv file to write the data to
 * @param filename 
 */
void GenerateCSV::generateMaxNumberPerDay(std::string filename)
{

    std::ofstream writeOutput(filename);
    assert(writeOutput.is_open());
    int dailyAvg = 0;

    for (int i = 0; i < mVector.size(); i++)
    {
        for (int j = 0; j < mVector[i].size(); j++)
        {
            if (j < mVector[i].size() - 1)
            {
                dailyAvg += (mVector[i][j].maxNumberPerDay());
            }
        }
        dailyAvg = dailyAvg / (mVector[i].size());
        writeOutput << dailyAvg << "\n";
    }
    writeOutput.close();
}

/**
 * @brief Destroy the Generate CSV object
 * 
 */
GenerateCSV::~GenerateCSV()
{
}
