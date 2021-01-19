/**
 * @file MaxCapacitySelector.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief allow user to increase/decrease capacity, Selects the Maximum Capacity on the GUI and allows the user to increase by clicking "+" and decrease by clicking "-"
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 *
 */
#ifndef MAXCAPACITYSELECTOR_H
#define MAXCAPACITYSELECTOR_H

#include <QLineEdit>
#include <QWidget>

/**
 * @brief implemenetaion of MaxCapacitySelector, allow user to increase/decrease capacity
 *
 */
class MaxCapacitySelector : public QWidget
{
    Q_OBJECT

public:
    MaxCapacitySelector(QWidget *parent = 0);
    ~MaxCapacitySelector();

private slots:
    void increaseCapacity();
    void decreaseCapacity();

private:
    unsigned int maxCapacity;

    QLineEdit *text;

    void updateText();
    void submitCapacity();
};

#endif // MAXCAPACITYSELECTOR_H
