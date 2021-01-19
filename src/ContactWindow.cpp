/**
 * @file ContactWindow.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief prompt a dialogue that allows user to add contact
 * @version 0.1
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "ContactWindow.h"
#include "DBConnection.h"
#include "MainWindow.h"
#include <QDebug>
#include <QRegExpValidator>

/**
 * @brief Construct a new Contact Window object that allows the user to add contact
 * 
 * Using this window user can input their full name, email, phone number, role and preferred method of contact
 * 
 * @param parent 
 */
ContactWindow::ContactWindow(QWidget *parent) : QWidget(parent)
{
    // Create and display new window
    window = new QWidget;
    window->show();

    // Set title and window size
    window->setWindowTitle("Register Contact Information");
    window->setFixedHeight(275);
    window->setFixedWidth(450);

    // Create a label and a line edit for first name, with some basic regex validation (only 2-15 letters allowed)
    QLabel *firstNameLabel = new QLabel("First Name:", this);
    firstNameLineEdit = new QLineEdit;
    firstNameLineEdit->setPlaceholderText("First Name");
    firstNameLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{2,15}"), this));
    firstNameLineEdit->setClearButtonEnabled(true);

    // Create a label and a line edit for last name, with some basic regex validation (only 2-15 letters allowed)
    QLabel *lastNameLabel = new QLabel("Last Name:", this);
    lastNameLineEdit = new QLineEdit;
    lastNameLineEdit->setPlaceholderText("Last Name");
    lastNameLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{2,15}"), this));
    lastNameLineEdit->setClearButtonEnabled(true);

    // Create a label and a line edit for email address , with some basic regex validation
    QLabel *emailLabel = new QLabel("Email Address:", this);
    emailLineEdit = new QLineEdit;
    emailLineEdit->setPlaceholderText("email@address.com");
    emailLineEdit->setValidator(new QRegExpValidator(QRegExp("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"), this));
    emailLineEdit->setMaxLength(30);
    emailLineEdit->setClearButtonEnabled(true);

    // Create a label and a line edit for phone number , with some basic regex validation (only 10 numbers allowed)
    QLabel *phoneNumberLabel = new QLabel("Phone Number:", this);
    phoneNumberLineEdit = new QLineEdit;
    phoneNumberLineEdit->setPlaceholderText("(226) 123-4567");
    phoneNumberLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{10}"), this));
    phoneNumberLineEdit->setClearButtonEnabled(true);

    // To choose perferred method of contact
    QLabel *contactMethodLabel = new QLabel("Preferred Method of Contact:", this);
    emailCheckBox = new QCheckBox("Email", this);
    phoneNumberCheckBox = new QCheckBox("Phone Number", this);

    // Return button to leave window without adding contact
    QPushButton *backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &ContactWindow::back);

    // Button to add contact
    QPushButton *addContactButton = new QPushButton("Add Contact", this);
    connect(addContactButton, &QPushButton::clicked, this, &ContactWindow::submitContactInformation);

    // Button to clear all text fields and radio button selection
    QPushButton *clearAllButton = new QPushButton("Clear", this);
    connect(clearAllButton, &QPushButton::clicked, this, &ContactWindow::clearAll);

    // Radio button to select contact's role
    QLabel *roleLabel = new QLabel("Role:", this);
    employeeRadioButton = new QRadioButton("Employee", this);
    customerRadioButton = new QRadioButton("Customer", this);

    // Arrange all the form fields on the window
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(emailCheckBox);
    buttonLayout->addStretch(1); // spreads eveything
    buttonLayout->addWidget(phoneNumberCheckBox, Qt::AlignRight);

    QHBoxLayout *rolesLayout = new QHBoxLayout;
    rolesLayout->addWidget(employeeRadioButton);
    rolesLayout->addStretch(1); // spreads eveything
    rolesLayout->addWidget(customerRadioButton, Qt::AlignRight);

    QGridLayout *addAndClearLayout = new QGridLayout;
    addAndClearLayout->addWidget(addContactButton, 0, 0);
    addAndClearLayout->addWidget(clearAllButton, 0, 1);

    // Display all the form fields on the window, main layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(firstNameLabel, 0, 0);
    layout->addWidget(firstNameLineEdit, 0, 1);

    layout->addWidget(lastNameLabel, 1, 0);
    layout->addWidget(lastNameLineEdit, 1, 1);

    layout->addWidget(emailLabel, 2, 0);
    layout->addWidget(emailLineEdit, 2, 1);

    layout->addWidget(phoneNumberLabel, 3, 0);
    layout->addWidget(phoneNumberLineEdit, 3, 1);

    layout->addWidget(roleLabel, 4, 0);
    layout->addLayout(rolesLayout, 4, 1);

    layout->addWidget(contactMethodLabel, 5, 0);
    layout->addLayout(buttonLayout, 5, 1);

    layout->addWidget(backButton, 6, 0);
    layout->addLayout(addAndClearLayout, 6, 1);

    window->setLayout(layout);
}

/**
 * @brief Destroy the Contact Window object
 * 
 */
ContactWindow::~ContactWindow()
{
}

/**
 * @brief Adds new contact after all fields have been populated
 * 
 */
void ContactWindow::submitContactInformation()
{
    // Identify contact's prefered method of contact based on radio button selected
    QString preferEmail = (emailCheckBox->isChecked()) ? "1" : "0";
    QString preferPhoneNumber = (phoneNumberCheckBox->isChecked()) ? "1" : "0";

    // Identify contact's role based on radio button selected
    QString role = "";
    if (employeeRadioButton->isChecked())
    {
        role = "Employee";
    }
    else if (customerRadioButton->isChecked())
    {
        role = "Customer";
    }

    QMessageBox msgBox;
    bool isContactAdded;
    DBConnection DB("ContactList.db");

    // Check if database connection is open
    if (DB.isConnectionOpen())
    {
        // Create table if it does not already exist
        DB.createTable();
        // Query to add contact to database
        isContactAdded = DB.addContact(firstNameLineEdit->text(), lastNameLineEdit->text(),
                                       emailLineEdit->text(), phoneNumberLineEdit->text(),
                                       role, preferEmail, preferPhoneNumber);
        // If query was successfully added output success or missing info message
        if (isContactAdded)
        {
            msgBox.setText("Sucess!");
            window->hide();
        }
        else
        {
            msgBox.setText("Oops. You missed some required information. Please try again.");
        }
        msgBox.exec();
    }
    // If connection to database failed output error message
    else
    {
        qDebug() << "Couldn't connect to the database";
    }
}

/**
 * @brief Closes window when back button is pressed
 * 
 */
void ContactWindow::back()
{
    window->close();
}
/**
 * @brief Clears all the values in add contact fields
 * 
 */

void ContactWindow::clearAll()
{
    firstNameLineEdit->setText("");
    lastNameLineEdit->setText("");
    emailLineEdit->setText("");
    phoneNumberLineEdit->setText("");

    // Since by default radio buttons are exclusive, we have to unable it first, and then uncheck it
    emailCheckBox->setAutoExclusive(false);
    emailCheckBox->setChecked(false);
    emailCheckBox->setAutoExclusive(true);

    phoneNumberCheckBox->setAutoExclusive(false);
    phoneNumberCheckBox->setChecked(false);
    phoneNumberCheckBox->setAutoExclusive(true);

    employeeRadioButton->setAutoExclusive(false);
    employeeRadioButton->setChecked(false);
    employeeRadioButton->setAutoExclusive(true);

    customerRadioButton->setAutoExclusive(false);
    customerRadioButton->setChecked(false);
    customerRadioButton->setAutoExclusive(true);

    // Unselects any selected text fields
    if (firstNameLineEdit->hasFocus())
    {
        firstNameLineEdit->clearFocus();
    }
    if (lastNameLineEdit->hasFocus())
    {
        lastNameLineEdit->clearFocus();
    }
    if (phoneNumberLineEdit->hasFocus())
    {
        phoneNumberLineEdit->clearFocus();
    }

}
