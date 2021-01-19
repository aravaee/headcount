/**
* @file ReadCSV.cpp
* @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
* @brief This class reads from the CSV's containing the data which was produced by the GenerateCSV class and stores it into a vector.
* @version 1.0
* @date 2020-12-02
* @copyright Copyright (c) 2020
*/
#include "ReadCSV.h"
#include <iostream>

/**
 * @brief Construct a ReadCSV object which will parse through the CSV
 *
 * @param fileName
 */
ReadCSV::ReadCSV(std::string fileName)
{
  mFileName = fileName;
}

/**
 * @brief the csv file containing all the analytics is parsed line by line and it's data is stored into a vector
 *
 * @return std::vector<double>
 */
std::vector<double> ReadCSV::getData()
{
  std::vector<double> data; // the vector where the retrived values from the csv will be stored
  int count = 0;
  std::ifstream rf(mFileName);

  // if file is empty return
  if (rf.peek() == std::ifstream::traits_type::eof())
  {
    return data;
  }

  // read line by line, retrieve the string with the data, convert it to double and push it to the vector.
  std::string str;
  while (!rf.eof())
  {
    rf >> str;
    double values = stod(str);
    data.push_back(values);
  }
  rf.close();
  return data;
}

/**
 * @brief Destroy ReadCSV object
 *
 */
ReadCSV::~ReadCSV() {}
