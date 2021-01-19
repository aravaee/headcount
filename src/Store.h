/**
 * @file Store.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class stores all the vectors being collected by the objected detector and stores
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef STORE_H
#define STORE_H

#include <ctime>
#include <vector>

#include <QObject>

/**
 * @brief A class to store all the data for entering and exiting 
 * 
 */
class Store : public QObject {
    Q_OBJECT

    public:
        Store(QObject *parent = 0);
        ~Store();

        std::vector<int> getEnterVector() const;
        std::vector<int> getExitVector() const;

    public slots:
        void personEntered();
        void personExited();

    signals:
        void capacityChanged(unsigned int capacity);

    private:
        std::vector<int> enterVector;
        std::vector<int> exitVector;
        std::time_t startTime;
        unsigned int currentCapacity;
};

#endif // STORE_H
