/**
 * @file SettingsWindow.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class stores produces a settings option to change up the object detection, maximum capacity, and many more on the GUI
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QCheckBox>
#include <QComboBox>
#include <QWidget>

#include "ObjectTracker.h"

/**
 * @brief Class stores produces a settings option to change up the object detection, maximum capacity, and many more on the GUI
 * 
 */
class SettingsWindow : public QWidget {
    Q_OBJECT

    public:
        SettingsWindow(ObjectTracker *objectTracker, QWidget *parent = 0);

        ~SettingsWindow();

    private slots:
        void save();

    private:
        ObjectTracker *objectTracker;

        QCheckBox *drawBoundingBoxesCheckBox;
        QCheckBox *drawCentroidsCheckBox;
        QCheckBox *drawThresholdsCheckBox;
        QCheckBox *showStatesCheckBox;
        QCheckBox *showFrameNumberCheckBox;
        QCheckBox *showFrameStatusCheckBox;

        QComboBox *enterDirectionComboBox;
};

#endif // SETTINGSWINDOW_H
