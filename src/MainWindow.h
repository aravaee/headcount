/**
 * @file MainWindow.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief creates the main window and allow user to select a video
 * @version 0.1
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLabel>

#include "Store.h"
#include "ObjectTracker.h"
#include "VideoSource.h"
#include "ContactWindow.h"
#include "ComposeWindow.h"
#include "AnalyticWindow.h"

/**
 * @brief implementation of MainWindow, create a signal when video is opened, create a slot in response to signal
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Main Window:: Main Window object
     * @param capture
     * @param objectDetector
     * @param parent
     */
    MainWindow(QWidget *parent = 0);
    /**
     * @brief destrcutor for the MainWIndowclass
     *
     */
    ~MainWindow();

private slots:
    /**
     * @brief opens a video through the selected path
     *
     */
    void openFile();
    /**
     * @brief opens the camera to display the video
     *
     */
    void openCamera();
    /**
     * @brief open a new window for the user to enter their contact info
     *
     */
    void openAddNewContact();
    /**
     * @brief displays the contacts that exist in the database
     *
     */
    void openContacts();
    /**
     * @brief opens a composed window
     *
     */
    void openCompose();
    /**
     * @brief opens a Analytic Window
     *
     */
    void openAnalyticWindow();
    /**
     * @brief opens a settings Window
     *
     */
    void openSettingsWindow();
    /**
     * @brief Updates the capactiy everytime it has been changed
     *
     */
    void updateCapacityLabel(unsigned int capacity);

private:
    Store *store;

    ObjectTracker *objectTracker;

    VideoSource *videoSource;

    QLabel *fileNameLabel;
    QLabel *currentCapacityLabel;

    ContactWindow *contactWindow;
    ComposeWindow *composeWindow;
    AnalyticWindow *analyticWindow;
};

#endif // MAINWINDOW_H
