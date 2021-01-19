/**
 * @file Simulation.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class creates artifical data containing all store enteries and exits and arranges the data by day and hour so it can be analysed.
 * @version 0.1
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Simulation.h"

/**
 * @brief Construct Simulation object which will contain all ARTIFICIAL entry/exit data
 * First param is hours that the store is open for per day in the artifical data,
 * Second param is the number of days to generate artifical data for
 * @param hours 
 * @param days 
 */
Simulation::Simulation(int hours, int days)
{
  mHours = hours;
  mDays = days;
}

/**
 * @brief generates a 2-d vector with randomly made artifical data for all store for the hour.
 * The 2-d vector of artifical data. first element is a vector of all enteries for the hour. Secibd element is a vector of all exits for the hour.
 * @return std::vector<std::vector<int> > 
 */
std::vector<std::vector<int>> Simulation::generateRandomVector()
{

  std::vector<std::vector<int>> numbers;
  std::vector<int> exit;
  std::vector<int> enter;

  // random number generator engine
  std::random_device device;
  std::mt19937 engine(device());

  // Define the ranges of the functions
  std::uniform_int_distribution<int> sizeRandom(40, 70);
  std::uniform_int_distribution<int> intialEntry(0, 180);

  // size of enteries/exits defined by the random engine
  int size = sizeRandom(engine);
  enter.push_back(intialEntry(engine));

  std::uniform_int_distribution<int> enterRandom(enter[0], 3000);

  // Generating randome values for the hours for entries and exits
  for (int i = 0; i < size - 1; i++)
  {
    std::uniform_int_distribution<int> exitRandom(enter[i] + 60, enter[i] + 600);
    exit.push_back(exitRandom(engine));
    enter.push_back(enterRandom(engine));
  }

  std::uniform_int_distribution<int> randomExit(enter[size - 1] + 60, enter[size - 1] + 600);
  exit.push_back(randomExit(engine));

  // vectors are sorted then returned in a 2-d array
  std::sort(enter.begin(), enter.end());
  std::sort(exit.begin(), exit.end());

  numbers.push_back(enter);
  numbers.push_back(exit);

  return numbers;
}

/**
 * @brief This function takes the Simulation data and creates an analytics object for each hour,
 *  which are all stored in a 2-d vector for all days. ex: [Day][Hourly analysis]
 * 
 * @return std::vector<std::vector<Analytics> > 
 */
std::vector<std::vector<Analytics>> Simulation::simulatedData()
{
  std::vector<std::vector<Analytics>> simulatedVector;

  for (int i = 0; i < mDays; i++)
  {
    std::vector<Analytics> dayVector;
    for (int j = 0; j < mHours; j++)
    {
      std::vector<std::vector<int>> randomVectors = generateRandomVector();
      Analytics A(randomVectors[0], randomVectors[1], randomVectors[1].size() - 5);
      dayVector.push_back(A);
    }
    simulatedVector.push_back(dayVector);
  }

  return simulatedVector;
}

/**
 * @brief Destroy the Simulation object
 * 
 */
Simulation::~Simulation()
{
}
