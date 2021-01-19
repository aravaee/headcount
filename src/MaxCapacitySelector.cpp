/**
 * @file MaxCapacitySelector.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief allow user to increase/decrease capacity, selects the Maximum Capacity on the GUI and allows the user to increase by clicking "+" and decrease by clicking "-"
 * @version 1.0
 * @date 2020-12-02
 * @copyright Copyright (c) 2020
 *
 */
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <Qt>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

#include "MaxCapacitySelector.h"

/**
 * @brief: Construct a new Max Capacity Selector:: Max Capacity Selector object
 * @param: parent
 */
MaxCapacitySelector::MaxCapacitySelector(QWidget *parent) : QWidget(parent)
{
    QLabel *label = new QLabel("Max Capacity:", this); // QLabel to create a label on the GUI called Max Capacity so the user can understand

    text = new QLineEdit(); // initializes a new QLineEdit object
    text->setFocusPolicy(Qt::ClickFocus); // sets a text to the Set Focus Ploicy
    text->setPlaceholderText("[0-9999]");
    // acceptable range [1-9999] with no leading zeroes
    text->setValidator(new QRegExpValidator (QRegExp("[0-9]{,4}"), this));
    text->setClearButtonEnabled(true);
    text->setFixedWidth(88);


    // Settings to change the maxcapacity to the when user clicks on it
    QSettings settings;
    maxCapacity = settings.value("core/maxCapacity", 0).toUInt();
    updateText(); // updates the text when the user clicks on a button

    auto increaseButton = new QPushButton("▲", this); // adds a gui button to increase
    connect(increaseButton, &QPushButton::clicked, this, &MaxCapacitySelector::increaseCapacity);

    auto decreaseButton = new QPushButton("▼", this); // adds a gui button to decrease
    connect(decreaseButton, &QPushButton::clicked, this, &MaxCapacitySelector::decreaseCapacity);

    QPushButton *submitButton = new QPushButton("Set", this); // submits the button to set the max capacity
    connect(submitButton, &QPushButton::clicked, this, &MaxCapacitySelector::submitCapacity);

    /*REST OF THE CODE LAYS OUT ALL THE GUI TO DISPLAY IT */
    QVBoxLayout *layoutCapacity = new QVBoxLayout;
    layoutCapacity->addWidget(label);
    layoutCapacity->addWidget(text);
    layoutCapacity->addWidget(increaseButton);
    layoutCapacity->addWidget(decreaseButton);
    layoutCapacity->addWidget(submitButton);

    QHBoxLayout *layoutH = new QHBoxLayout;
    layoutH->addStretch(1);
    layoutH->addLayout(layoutCapacity);
    layoutH->addStretch(1);

    setLayout(layoutH);
}
/**
 * @brief Destroy the Max Capacity Selector:: Max Capacity Selector object
 * 
 */
MaxCapacitySelector::~MaxCapacitySelector()
{
}
/**
 * @brief increment maxCapacity
 * 
 */
void MaxCapacitySelector::increaseCapacity()
{
    text->clearFocus();
    maxCapacity = text->text().toInt(); // sets the text to an int so we increment
    // increments the maxcapacity when user clicks on the "+"
    if (maxCapacity < 9999){
        maxCapacity++;
        updateText(); // updates the text when the user sets it.
    }

}
/**
 * @brief decrement maxCapacity
 * 
 */
void MaxCapacitySelector::decreaseCapacity()
{
    maxCapacity = text->text().toInt(); // sets the text to an int so we increment
    // decreases the maxcapacity when user clicks on the "-"
    if (maxCapacity > 0)
    {
        text->clearFocus();
        maxCapacity--;
        updateText(); // updates the text when the user sets it.
    }
}
/**
 * @brief update label according to the current maxCapacity
 * 
 */
void MaxCapacitySelector::updateText()
{
    // Checks if the max capacity is 0 and then prints nothing to the screen if it occured it updates the text.
    if (maxCapacity == 0) {
        text->setText("");
    } else {
        text->setText(QString::number(maxCapacity)); // sets the max capacity which the user set it to
    }
}

/**
 * @brief allow the user to set the capacity
 * 
 */
void MaxCapacitySelector::submitCapacity()
{
    text->clearFocus(); // clears the texts of the submit capacity

    maxCapacity = text->text().toInt();
    // If the max capcity is greater than 0 updates the texts
    if (maxCapacity >= 0) {
        updateText();

        QSettings settings; // saves the settings to the max capacity adjusted by the user
        settings.setValue("core/maxCapacity", maxCapacity);

        // Lets the user to know the max capacity has been checked.
        QMessageBox msgBox;
        msgBox.setText("Max Capacity Has Been Set!");
        msgBox.exec();
        qDebug() << maxCapacity << " :maxCapacity\n";
    }
}
