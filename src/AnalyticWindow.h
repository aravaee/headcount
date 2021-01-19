/**
 * @file AnalyticWindow.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Window which analyzes data collected (or generated) and displays it in the form of graphs
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef REALANALYTICWINDOW_H
#define REALANALYTICWINDOW_H

#include <QtWidgets>
#include <QRadioButton>
#include "Store.h"

/**
 * @brief Class to analyse the data collected (or generated)
 * 
 */
class AnalyticWindow : public QWidget
{
    Q_OBJECT

public:
    AnalyticWindow(Store *store, QWidget *parent = 0);
    ~AnalyticWindow();

private slots:
    void displayAvgPeopleEntering();
    void displayAvgTimeSpent();
    void displayMaxNumPeople();
    void displayStoreEntry();
    void back();

private:
    void showGraphs(QString title, QString xAxisTitle, QString yAxisTitle, std::string csvName, bool useArtificial = true, int hours = 0, int days = 0, int choice = 0);

    QWidget *window;
    QRadioButton *realDataRadioButton;
    QRadioButton *artificialDataRadioButton;

    Store *store;
};

#endif // REALANALYTICWINDOW_H
