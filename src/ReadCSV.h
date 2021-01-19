/**
 * @file ReadCSV.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class reads from the CSV's containing the data which was produced by the GenerateCSV class and stores it into a vector.
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef READCSV_H
#define READCSV_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

/**
 * @brief class which reads and stores data read from csv
 * 
 */
class ReadCSV{

private:
    std::string mFileName;

public:
    ReadCSV(std::string fileName);
    ~ReadCSV();
    std::vector<double> getData();
};

#endif
