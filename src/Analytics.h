/**
 * @file Analytics.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class provides us with a statisical analysis of our data given by the object detection video feed.
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __ANALYTICS_H
#define __ANALYTICS_H

#include <vector>
#include <cmath>
#include <numeric>

/**
 * @brief Construct a new Analytics Object to perform statistical analysis
 * 
 */
class Analytics
{
private:
  std::vector<int> mEnterVector;
  std::vector<int> mExitVector;
  int mSize; // Size of vector
  int mMaxCapacity;

public:
  Analytics(std::vector<int> enterVector, std::vector<int> exitVector,
            int maxCapacity);
  double averageTimeInStore();
  double averagePeopleEntry();
  int maxCapacityOccurences();
  int numberOfEntries();
  int maxNumberPerDay();
  std::vector<int> storeUpdates();
  std::vector<int> getEnterVector();
  std::vector<int> getExitVector();
  ~Analytics();
};

#endif
