#include "PlotGraphs.h"
#include "ReadCSV.h"

PlotGraphs::PlotGraphs(std::string fileName){
    mFileName = fileName;
    ReadCSV reader(mFileName);
    mData = reader.getData();
}

PlotGraphs::~PlotGraphs() {

}

QChartView *PlotGraphs::PlotScatter(QString title, QString xAxisTitle, QString yAxisTitle)  {

    QScatterSeries *series = new QScatterSeries();

    for (int i = 0; i < mData.size();i++){
        series->append(i,mData[i]);
    }
    QChart *chart = new QChart();

    chart->legend()->hide();
    chart->addSeries(series);
    //chart->createDefaultAxes();
    chart->setTitle(title);

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText(xAxisTitle);
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(yAxisTitle);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    return chartView;
}

QChartView *PlotGraphs::PlotLine(QString title, QString xAxisTitle, QString yAxisTitle)  {

    QLineSeries* series = new QLineSeries();

    for (int i = 0; i < mData.size();i++){
        series->append(i,mData[i]);
    }
    QChart *chart = new QChart();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(title);

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText(xAxisTitle);
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(yAxisTitle);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}


QChartView *PlotGraphs::PlotSpline(QString title, QString xAxisTitle, QString yAxisTitle)  {

    QSplineSeries *series = new QSplineSeries();
    for (int i = 0; i < mData.size();i++){
        series->append(i,mData[i]);
    }
    QChart *chart = new QChart();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(title);

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText(xAxisTitle);
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(yAxisTitle);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

QChartView *PlotGraphs::PlotBarGraph(QString title, QString xAxisTitle, QString yAxisTitle)  {

    QBarSeries *series = new QBarSeries();
    for (int i = 0; i < mData.size() ;i++){
        std::string str = "Day " + std::to_string(i + 1); // day 1, etc
        QString qstr = QString::fromStdString(str);
        QBarSet *set = new QBarSet(qstr);
        //for (int j = 0; j < mData.size();j++)
        *set << mData[i];
        series->append(set);
    }

    QChart *chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->addSeries(series);
    // chart->createDefaultAxes();
    chart->setTitle(title);

    QChartView *chartView = new QChartView(chart);
    chart->setAnimationOptions(QChart::NoAnimation);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(yAxisTitle);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chartView;

}

