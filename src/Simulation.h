/**
 * @file Simulation.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class creates artifical data containing all store enteries and exits and arranges the data by day and hour so it can be analysed.
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SIMULATION_H
#define __SIMULATION_H

#include "Analytics.h"
#include <cstdlib>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>

/**
 * @brief This class can create artifical data over the span of days/hours that it is set to.
 * This shows what the real data could look like if used over the long term
 * 
 */
class Simulation
{
private:
  int mHours;
  int mDays;

public:
  Simulation(int hours, int days);
  std::vector<std::vector<int>> generateRandomVector();
  std::vector<std::vector<Analytics>> simulatedData();
  ~Simulation();
};

#endif
