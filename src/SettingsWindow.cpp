/**
 * @file SettingsWindow.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief This class stores produces a settings option to change up the object detection, maximum capacity, and many more on the GUI
 * @version 1.0
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSettings>

#include "SettingsWindow.h"

/**
 * @brief Constructor that allows to change the settings of the boxes on the video, the line on the video the max capacity and etc..
 *
 * @param objectTracker
 * @param parent
 */
SettingsWindow::SettingsWindow(ObjectTracker *objectTracker, QWidget *parent) : QWidget(parent) {
    QSettings settings;
    const auto drawFlags = settings.value("tracker/drawFlags").value<ObjectTracker::DrawFlags>();
    const auto enterDirection = settings.value("tracker/enterDirection").toUInt();

    // Create the "Draw Flags" group box with check boxes to select individual flags
    QGroupBox *drawFlagsGroup = new QGroupBox("Draw Flags");

    // Create the "Draw Bounding box" group box with check boxes to select individual flags
    drawBoundingBoxesCheckBox = new QCheckBox("Draw Bounding Boxes");
    drawBoundingBoxesCheckBox->setChecked(drawFlags.testFlag(ObjectTracker::DrawBoundingBoxes));

    // Create the "Draw Centroids box" group box with check boxes to select individual flags
    drawCentroidsCheckBox = new QCheckBox("Draw Centroids");
    drawCentroidsCheckBox->setChecked(drawFlags.testFlag(ObjectTracker::DrawCentroids));

    // Create the "Draw Threshold box" group box with check boxes to select individual flags
    drawThresholdsCheckBox = new QCheckBox("Draw Thresholds");
    drawThresholdsCheckBox->setChecked(drawFlags.testFlag(ObjectTracker::DrawThresholds));

    // Shows the state of the boxes which are checked or not.
    showStatesCheckBox = new QCheckBox("Show States");
    showStatesCheckBox->setChecked(drawFlags.testFlag(ObjectTracker::ShowStates));

    // shows the frame number of the video being used.
    showFrameNumberCheckBox = new QCheckBox("Show Frame Number");
    showFrameNumberCheckBox->setChecked(drawFlags.testFlag(ObjectTracker::ShowFrameNumber));

    // Shows the frame status
    showFrameStatusCheckBox = new QCheckBox("Show Frame Status");
    showFrameStatusCheckBox->setChecked(drawFlags.testFlag(ObjectTracker::ShowFrameStatus));

    QGridLayout *drawFlagsLayout = new QGridLayout;
    drawFlagsLayout->setSizeConstraint(QLayout::SetMinimumSize);
    drawFlagsLayout->addWidget(drawBoundingBoxesCheckBox, 0, 0);
    drawFlagsLayout->addWidget(drawCentroidsCheckBox, 1, 0);
    drawFlagsLayout->addWidget(drawThresholdsCheckBox, 2, 0);
    drawFlagsLayout->addWidget(showStatesCheckBox, 0, 1);
    drawFlagsLayout->addWidget(showFrameNumberCheckBox, 1, 1);
    drawFlagsLayout->addWidget(showFrameStatusCheckBox, 2, 1);
    drawFlagsGroup->setLayout(drawFlagsLayout);

    // Create the "Enter Direction" group box with a combo box to select the direction
    QGroupBox *enterDirectionGroup = new QGroupBox("Enter Direction");

    enterDirectionComboBox = new QComboBox;
    enterDirectionComboBox->addItem("Up");
    enterDirectionComboBox->addItem("Down");
    enterDirectionComboBox->addItem("Left");
    enterDirectionComboBox->addItem("Right");
    enterDirectionComboBox->setCurrentIndex(enterDirection);

    // Sets the constraints changed by the user to the video
    QVBoxLayout *enterDirectionLayout = new QVBoxLayout;
    enterDirectionLayout->setSizeConstraint(QLayout::SetMinimumSize);
    enterDirectionLayout->addWidget(enterDirectionComboBox);
    enterDirectionGroup->setLayout(enterDirectionLayout);

    // Create "Close" button
    QPushButton *closeButton = new QPushButton("&Close", this);
    connect(closeButton, &QPushButton::clicked, this, &SettingsWindow::close);

    // Create "Save" button
    QPushButton *saveButton = new QPushButton("&Save", this);
    connect(saveButton, &QPushButton::clicked, this, &SettingsWindow::save);

    // Add "Close" and "Save" buttons to a layout
    // Add a stretchable space to position them to the right
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    buttonLayout->addWidget(saveButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    mainLayout->addWidget(drawFlagsGroup);
    mainLayout->addWidget(enterDirectionGroup);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    this->objectTracker = objectTracker;

    this->setWindowTitle("Settings");
    this->setLayout(mainLayout);
}

/**
 * @brief Destroy the Settings Window object
 *
 */
SettingsWindow::~SettingsWindow() {

}

/**
 * @brief Allows the user to apply the specified settings and also saves it a source medium so they can load the next time the program is launched
 *
 */
void SettingsWindow::save() {
    ObjectTracker::DrawFlags drawFlags;

    // Checked if the draw bound boxes have been checked and if it has it changes the settings for the video
    if (drawBoundingBoxesCheckBox->isChecked()) {
        drawFlags |= ObjectTracker::DrawBoundingBoxes;
    }
    // Checked if the draw Centroids boxes have been checked and if it has it changes the settings for the video
    if (drawCentroidsCheckBox->isChecked()) {
        drawFlags |= ObjectTracker::DrawCentroids;
    }
    // Checked if the draw Thresholds boxes have been checked and if it has it changes the settings for the video
    if (drawThresholdsCheckBox->isChecked()) {
        drawFlags |= ObjectTracker::DrawThresholds;
    }
    // Checked if the show stats have been checked and if it has it changes the settings for the video
    if (showStatesCheckBox->isChecked()) {
        drawFlags |= ObjectTracker::ShowStates;
    }
    // Checked if the show number of frames in the video have been checked and if it has it changes the settings for the video
    if (showFrameNumberCheckBox->isChecked()) {
        drawFlags |= ObjectTracker::ShowFrameNumber;
    }
    // Checked if the show frame status box have been checked and if it has it changes the settings for the video
    if (showFrameStatusCheckBox->isChecked()) {
        drawFlags |= ObjectTracker::ShowFrameStatus;
    }

    const auto enterDirection = enterDirectionComboBox->currentIndex();

    // saves the settings so the next time the user opens it, it automatically saves.
    QSettings settings;
    settings.setValue("tracker/drawFlags", QVariant::fromValue(drawFlags));
    settings.setValue("tracker/enterDirection", enterDirection);

    objectTracker->setDrawFlags(drawFlags);
    objectTracker->setEnterDirection(static_cast<ObjectTracker::EnterDirection>(enterDirection));

    this->close();
}
