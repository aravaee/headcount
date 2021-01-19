/**
 * @file main.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief the entry point of program, we initialize and start the Qt application
 * @version 0.1
 * @date 2020-11-11
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>

#include <QObject>
#include <QThread>

#include "MainWindow.h"
#include "ObjectTracker.h"
#include "VideoSource.h"

Q_DECLARE_METATYPE(cv::Mat)

/**
 * @brief checks if correct number of arguments provided, initialization before passing the control to the Qt library, creates a window for UI
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[]) {
    // Register necessary OpenCV and custom types to work with Qt
    qRegisterMetaType<cv::Mat>();

    qRegisterMetaType<ObjectTracker::DrawFlags>();
    qRegisterMetaTypeStreamOperators<ObjectTracker::DrawFlags>();

    // Set the organization and application name for the Qt settings system
    QCoreApplication::setOrganizationName("CS3307Group1");
    QCoreApplication::setApplicationName("Headcount");

    QApplication app(argc, argv);

    MainWindow window;
    window.resize(700, 400);
    window.setWindowTitle("Headcount");
    window.show();

    return app.exec();
}
