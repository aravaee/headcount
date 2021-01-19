/**
 * @file PlotGraphs.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class stores produces graphs based off all the statistics made from the simulated data and the data being collected.
 * @version 0.1
 * @date 2020-11-22
 * @copyright Copyright (c) 2020
 */

#ifndef PLOTGRAPHS_H
#define PLOTGRAPHS_H


#include <QMainWindow>
#include <QApplication>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Widget used to display charts
#include <QtCharts/QChartView>

// Used to draw bars representing data provided
// grouped into categories
#include <QtCharts/QBarSeries>

// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>

// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>

// Used to create stacked bar charts
#include <QtCharts/QHorizontalStackedBarSeries>

// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

// Used to make Pie Charts
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

//Scatter plot
#include <QScatterSeries>

//Spline
#include <QSplineSeries>
#include <iostream>
#include <string>
#include <QString>
#include <QAction>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>

QT_CHARTS_USE_NAMESPACE

/**
 * @brief This class stores produces graphs based off all the statistics made from the simulated data
 * 
 */
class PlotGraphs : public QWidget {
    Q_OBJECT
private:
    std::string mFileName;
    std::vector<double> mData;
public:

    PlotGraphs(std::string fileName);

    ~PlotGraphs();

    QChartView *PlotScatter(QString title, QString xAxisTitle, QString yAxisTitle);

    QChartView *PlotLine(QString title, QString xAxisTitle, QString yAxisTitle);

    QChartView *PlotSpline(QString title, QString xAxisTitle, QString yAxisTitle);

    QChartView *PlotBarGraph(QString title, QString xAxisTitle, QString yAxisTitle);
};

#endif
