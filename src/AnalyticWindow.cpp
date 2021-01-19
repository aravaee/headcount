/**
 * @file AnalyticWindow.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief analyse data
 * @version 1.0
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "MainWindow.h"
#include "AnalyticWindow.h"
#include "Simulation.h"
#include "PlotGraphs.h"
#include "GenerateCSV.h"
#include "Analytics.h"
#include "RealData.h"

#include <QDebug>
#include <QFileDialog>

/**
 * @brief Construct an instance of AnalyticWindow
 * 
 * @param store 
 * @param parent 
 */
AnalyticWindow::AnalyticWindow(Store* store, QWidget *parent) : QWidget(parent)
{
    // Create and display window
    window = new QWidget;
    window->show();
    window->setWindowTitle("Data Analytics");
    window->setFixedSize(420, 220);

    //Create buttomfs to display graphs of various computed analytics

    QPushButton *avgNumDisplayButton = new QPushButton("Display Graph", this);  // average number of people entering store
    QPushButton *avgTimeDisplayButton = new QPushButton("Display Graph", this); // average time spent in store
    QPushButton *maxNumDisplayButton = new QPushButton("Display Graph", this);  // Max number of people in store
    QPushButton *entryDisplayButton = new QPushButton("Display Graph", this);   // Number of store enteries

    // Create button to return to main menu
    QPushButton *backButton = new QPushButton("Back", this);

    // Link the button with functions to analyze and display data in graph form
    connect(avgNumDisplayButton, &QPushButton::clicked, this, &AnalyticWindow::displayAvgPeopleEntering);
    connect(avgTimeDisplayButton, &QPushButton::clicked, this, &AnalyticWindow::displayAvgTimeSpent);
    connect(maxNumDisplayButton, &QPushButton::clicked, this, &AnalyticWindow::displayMaxNumPeople);
    connect(entryDisplayButton, &QPushButton::clicked, this, &AnalyticWindow::displayStoreEntry);

    // Link button to function which clears window and returns to main window
    connect(backButton, &QPushButton::clicked, this, &AnalyticWindow::back);

    // Create labels for the graph display buttons
    QLabel *avgNumDisplayLabel = new QLabel("Average number of people entering store", this);
    QLabel *avgTimeDisplayLabel = new QLabel("Average time spent in store", this);
    QLabel *maxNumDisplayLabel = new QLabel("Max number of people in store", this);
    QLabel *entryDisplayLabel = new QLabel("Number of store enteries", this);

    // Create radio button to chose between real and artifical data
    realDataRadioButton = new QRadioButton("Real Data", this);
    artificialDataRadioButton = new QRadioButton("Artifical Data", this);
    realDataRadioButton->setChecked(true);

    // Arrange and display all the buttons/labels
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(realDataRadioButton, 0, 0);
    layout->addWidget(artificialDataRadioButton, 0, 1);

    layout->addWidget(avgNumDisplayLabel, 1, 0);
    layout->addWidget(avgNumDisplayButton, 1, 1);

    layout->addWidget(avgTimeDisplayLabel, 2, 0);
    layout->addWidget(avgTimeDisplayButton, 2, 1);

    layout->addWidget(maxNumDisplayLabel, 3, 0);
    layout->addWidget(maxNumDisplayButton, 3, 1);

    layout->addWidget(entryDisplayLabel, 4, 0);
    layout->addWidget(entryDisplayButton, 4, 1);

    layout->addWidget(backButton, 5, 1);

    window->setLayout(layout);

    this->store = store;
}

/**
 * @brief Destroy the Analytic Window object
 * 
 */
AnalyticWindow::~AnalyticWindow()
{
}

/**
 * @brief Function to compute and display graph for average people entering the store daily
 * 
 */
void AnalyticWindow::displayAvgPeopleEntering()
{
    const bool useArtificial = artificialDataRadioButton->isChecked();
    showGraphs("Avg People Entering vs Days", "Days", "Avg People Entering", "averagePeopleEntry.csv", useArtificial, 12, 7, 1);
}

/**
 * @brief Function to compute and display graph for average time spent in store per customer per day
 * 
 */
void AnalyticWindow::displayAvgTimeSpent()
{
    const bool useArtificial = artificialDataRadioButton->isChecked();
    showGraphs("Avg Time in Store (seconds) vs Days", "Days", "Avg Time in Store (seconds)", "averageTimeInStore.csv", useArtificial, 12, 7, 2);
}

/**
 * @brief Function to compute and display graph for max number of people in store per day at any time
 * 
 */
void AnalyticWindow::displayMaxNumPeople()
{
    const bool useArtificial = artificialDataRadioButton->isChecked();
    showGraphs("Max Number of People (Hours) vs Days", "Days", "Max Number of People (Hours)", "maxNumberPerDay.csv", useArtificial, 12, 7, 3);
}

/**
 * @brief Function to compute and display graph for number of people entering the store daily
 * 
 */
void AnalyticWindow::displayStoreEntry()
{
    const bool useArtificial = artificialDataRadioButton->isChecked();
    showGraphs("Number of Enteries vs Days", "Days", "Number of Enteries", "numberOfEntries.csv", useArtificial, 12, 7, 4);
}

/**
 * @brief Function to close AnalyticsWindow
 * 
 */
void AnalyticWindow::back()
{
    window->close();
}

/**
 * @brief Function to compute and display graph for statistic chosen by user
 * 
 * @param title 
 * @param xAxisTitle 
 * @param yAxisTitle 
 * @param csvName 
 * @param useArtificial 
 * @param hours 
 * @param days 
 * @param choice 
 */
void AnalyticWindow::showGraphs(QString title, QString xAxisTitle, QString yAxisTitle, std::string csvName, bool useArtificial, int hours, int days, int choice)
{
    // Create and display new window
    QWidget *displayWindow = new QWidget();
    displayWindow->setWindowTitle("Graph");
    displayWindow->show();
    QGridLayout *displayLayout = new QGridLayout();

    // Vector containing data to be analyzed
    std::vector<std::vector<Analytics>> dataVector;

    // Allow user to chose between artifical and real data
    if (useArtificial) {
        Simulation artificial(hours, days);
        dataVector = artificial.simulatedData();
    } else {
        std::vector<std::vector<int>> inputVector;
        inputVector.push_back(store->getEnterVector());
        inputVector.push_back(store->getExitVector());

        auto realData = RealData(inputVector);
        dataVector = realData.produceData();
    }
    // Generate csv for data based on user input
    GenerateCSV csv(hours, days, dataVector);

    // Compute statistic based on user input and output result to csv file
    if (choice == 1)
    {
        csv.generateAveragePeopleEntry(csvName);
    }
    else if (choice == 2)
    {
        csv.generateAverageTimeInStore(csvName);
    }
    else if (choice == 3)
    {
        csv.generateMaxNumberPerDay(csvName);
    }
    else if (choice == 4)
    {
        csv.generateNumberOfEntries(csvName);
    }
    else
    {
        std::cout << "ENTER WHAT FUNCTION U WANT TO COMPUTER\n";
    }

    // Create multiple graph variation of the staistic from the information in the csv file
    PlotGraphs plot(csvName);
    auto scatterPlot = plot.PlotScatter("Scatter Plot", xAxisTitle, yAxisTitle);
    auto linePlot = plot.PlotLine("Line Plot", xAxisTitle, yAxisTitle);
    auto splinePlot = plot.PlotSpline("Spline Plot", xAxisTitle, yAxisTitle);
    auto barGraphPlot = plot.PlotBarGraph("Bar Graph Plot", xAxisTitle, yAxisTitle);

    // Arrange graphs to display on window
    QStackedLayout *stackedLayout = new QStackedLayout;
    stackedLayout->setSizeConstraint(QLayout::SetMinimumSize);
    stackedLayout->addWidget(scatterPlot);
    stackedLayout->addWidget(linePlot);
    stackedLayout->addWidget(splinePlot);
    stackedLayout->addWidget(barGraphPlot);

    // Add and display labels to window
    QComboBox *pageComboBox = new QComboBox;
    pageComboBox->addItem(tr("Scatter Plot"));
    pageComboBox->addItem(tr("Line Plot"));
    pageComboBox->addItem(tr("Spline Plot"));
    pageComboBox->addItem(tr("Bar Graph Plot"));
    connect(pageComboBox, QOverload<int>::of(&QComboBox::activated),
            stackedLayout, &QStackedLayout::setCurrentIndex);

    QLabel *headerTitle = new QLabel(title);

    QPushButton *exportButton = new QPushButton("Export PDF");

    // Connect export button to function to draw graphs into pdf file
    connect(exportButton, &QPushButton::clicked, displayWindow, [=]() {
        QString filepath = QFileDialog::getSaveFileName(displayWindow, "Export PDF", "exported_graph.pdf", "PDF Files (*.pdf)");

        if (!filepath.endsWith(".pdf")){
            filepath.append(".pdf");
        }

        QPdfWriter writer(filepath);
        writer.setPageSize(QPagedPaintDevice::A4);
        QPainter painter(&writer);

        QChartView *chartView = (QChartView *) stackedLayout->currentWidget();
        QSize originalSize = chartView->size();

        QPixmap pix = chartView->grab();
        int h = painter.window().height()*0.4;
        int w = h * 1.3;
        int x = (painter.window().width()/2) - (w/2);
        int y = (painter.window().height()/2) - (h/2);
        chartView->resize(w, h);
        painter.drawPixmap(x, y, 640, 480, pix);
        chartView->resize(640, 480);
        chartView->render(&painter);

        chartView->resize(originalSize);

        painter.end();
    });

    // Display graphs to window
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(headerTitle);
    mainLayout->addLayout(stackedLayout);
    mainLayout->addWidget(pageComboBox);
    mainLayout->addWidget(exportButton);

    displayWindow->setLayout(mainLayout);
}
