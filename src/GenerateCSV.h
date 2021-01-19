/**
 * @file GenerateCSV.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class provides us with a csv containing data for each of the statistical analysis made by the Analytics class.
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __GENERATECSV_H
#define __GENERATECSV_H

#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Create a GenerateCSV object to process the analytics and store them in a csv
 * 
 */
class GenerateCSV
{
private:
  int mHours, mDays;
  std::vector<std::vector<Analytics>> mVector;

public:
  GenerateCSV(int hours, int days, std::vector<std::vector<Analytics>> vector);
  void generateAverageTimeInStore(std::string filename);
  void generateAveragePeopleEntry(std::string filename);
  void generateNumberOfEntries(std::string filename);
  void generateMaxNumberPerDay(std::string filename);
  ~GenerateCSV();
};

#endif
