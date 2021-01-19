/**
 * @file Store.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class stores all the vectors being collected by the objected detector and stores
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Store.h"
#include <QSettings>
#include "EmailNotification.h"

/**
 * @brief Construct a new Store:: Store object, The constructor sets the initial capacity to zero and the initial time to 0.
 * QObject allows us to use a lot of the event based methods and signals
 * @param parent 
 */
Store::Store(QObject *parent) : QObject(parent)
{
    startTime = std::time(nullptr); // setting the time to 0 at the beginning
    currentCapacity = 0;            // capacity of the people in the frame
}

/**
 * @brief Destroy  Store object
 * 
 */
Store::~Store()
{
}

/**
 * @brief The method returns all the counts of the people entering and stores it into a vector.
 * 
 * @return std::vector<int> 
 */
std::vector<int> Store::getEnterVector() const
{
    return enterVector;
}

/**
 * @brief The method returns all the counts of the people exit and stores it into a vector.
 * 
 * @return std::vector<int> 
 */
std::vector<int> Store::getExitVector() const
{
    return exitVector;
}

/**
 * @brief stores when people are entered
 * 
 * The method stores the time of the people entering into a vector
 * and the current capacity of the people in the frame and sends an email
 * notifcation to all the employees if the store capacity is maxed out.
 * 
 */
void Store::personEntered()
{
    std::time_t enterTime = std::time(nullptr) - startTime; // starts counting the time
    enterVector.push_back(enterTime); // stores the time in the vector

    currentCapacity++;
    emit capacityChanged(currentCapacity);

    QSettings settings; // QSettings object which allows to access methods to the settings class
    unsigned int maxCapacity = settings.value("core/maxCapacity", 0).toUInt();  // sets the maxcapity which the user has sent

    /* if the max capacity is greater than 0 and the current capacity is equal to
     * the max capacity it will send an email notifcation to all the current employees
     * so they are all notified not to allow users to enter.
     */
    if (maxCapacity > 0 && currentCapacity == maxCapacity)
    {
        QString subject = "Automatic Capacity Alert";
        QString message = QString("Be advised, the max capacity of %1 has been reached.\nThank You.").arg(maxCapacity);
        EmailNotification("Everyone", subject, message);
    }
}

/**
 * @brief The method stores the time of the people exiting into a vector.
 * 
 */
void Store::personExited()
{
     /**Checks the current capacity is greater than 0 and subtracts if some exits the frame
        and then emits a signal to the GUI to decrease the current capacity in the frame.*/
    if (currentCapacity > 0)
    {
        std::time_t exitTime = std::time(nullptr) - startTime;
        exitVector.push_back(exitTime);

        currentCapacity--;
        emit capacityChanged(currentCapacity);
    }
}
