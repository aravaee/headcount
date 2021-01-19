/**
 * @file ComposeWindow.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief compose an email
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "ComposeWindow.h"
#include "MainWindow.h"
#include "EmailNotification.h"
#include <QDebug>
/**
 * @brief Construct a new ComposeWindow object
 * 
 *  Constructor for compose window object which allows user to draft a message and
 *  notify employees/customers through email in case of an outbreak
 * 
 * @param parent 
 */
ComposeWindow::ComposeWindow(QWidget *parent) : QWidget(parent)
{
    // Create new window
    window = new QWidget;
    window->show();
    window->setWindowTitle("Compose an Email");
    window->setFixedWidth(520);

    // Give window title and create labels to identify subject field and recepients
    QLabel *titleLabel = new QLabel("Default Message:", this);
    QLabel *toLabel = new QLabel("To:", this);
    QLabel *subjectLabel = new QLabel("Subject:", this);

    // Create text field for subject and message text
    subjectLineEdit = new QLineEdit;
    messageTextEdit = new QTextEdit;

    // Create buttons to send, cancel, and clear message
    QPushButton *employeesMessageButton = new QPushButton("Employees", this);
    QPushButton *customersMessageButton = new QPushButton("Customers", this);
    QPushButton *everyoneMessageButton = new QPushButton("Everyone", this);

    // Create buttons to send, cancel, and clear message
    QPushButton *clearAllButton = new QPushButton("Clear", this);
    QPushButton *backButton = new QPushButton("Back", this);
    QPushButton *sendButton = new QPushButton("Send", this);

    // Connect the button to function that generates default messages
    connect(employeesMessageButton, &QPushButton::clicked, this, &ComposeWindow::employeesMessage);
    connect(customersMessageButton, &QPushButton::clicked, this, &ComposeWindow::customersMessage);
    connect(everyoneMessageButton, &QPushButton::clicked, this, &ComposeWindow::everyoneMessage);
    connect(clearAllButton, &QPushButton::clicked, this, &ComposeWindow::clearAll);

    // Connect button to function that sends message
    connect(sendButton, &QPushButton::clicked, this, &ComposeWindow::sendMessage);
    connect(backButton, &QPushButton::clicked, this, &ComposeWindow::back);

    // Radio button to  allow user to chose recepients
    employeesRadioButton = new QRadioButton("Employees", this);
    customersRadioButton = new QRadioButton("Customers", this);
    everyoneRadioButton = new QRadioButton("Everyone", this);
    
    // Arrange radio button to choose recepient
    QGridLayout *radioButtonLayout = new QGridLayout;
    radioButtonLayout->addWidget(employeesRadioButton, 0, 0);
    radioButtonLayout->addWidget(customersRadioButton, 0, 1);
    radioButtonLayout->addWidget(everyoneRadioButton, 0, 2);

    // Arrange radio button to choose default message
    QGridLayout *messageButtonLayout = new QGridLayout;
    messageButtonLayout->addWidget(employeesMessageButton, 0, 0);
    messageButtonLayout->addWidget(customersMessageButton, 0, 1);
    messageButtonLayout->addWidget(everyoneMessageButton, 0, 2);
    messageButtonLayout->addWidget(clearAllButton, 0, 3);    

    // Arrange title, to, and subject labels and buttons
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(titleLabel, 0, 0);
    gridLayout->addLayout(messageButtonLayout, 0, 1);

    gridLayout->addWidget(toLabel, 1, 0);
    gridLayout->addLayout(radioButtonLayout, 1, 1);

    gridLayout->addWidget(subjectLabel, 2, 0);
    gridLayout->addWidget(subjectLineEdit, 2, 1);

    QGridLayout *buttonLayout = new QGridLayout;
    buttonLayout->addWidget(backButton, 0, 0);
    buttonLayout->addWidget(sendButton, 0, 1);

    // main layout to display all widgets 
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(gridLayout);
    layout->addWidget(messageTextEdit);
    layout->addLayout(buttonLayout);
    
    window->setLayout(layout);
}

/**
 * @brief Destroy the Compose Window object
 * 
 */
ComposeWindow::~ComposeWindow()
{
}

/**
 * @brief Default message for employee notification
 * 
 * Sets the subject, message and radio button to appropriate values 
 */
void ComposeWindow::employeesMessage()
{
    subjectLineEdit->setText("COVID-19: Recent Outbreak and Safety Measures");
    messageTextEdit->setPlainText("Dear staff,\n\n"
    "Please be advised that we were notified that an employee has tested positive for COVID-19. "
    "As an immediate response to protect the health and safety of our workforce, we are notifying all employees about our temporary closure. "
    "If you experience symptoms of COVID-19 illness, please inform human resources and contact your health care provider. "
    "We will keep all medical information confidential and will only disclose it on a need-to-know basis.\n\n"
    "Your health and safety are our priority. "
    "We are immediately assessing this situation and will contact you as soon as possible via email with all relevant workplace notices detailing "
    "your rights and protections as our employee.\n"
    "\nStay Safe,\n"
    "Headcount");
    employeesRadioButton->setChecked(true);
}

/**
 * @brief Default message for customer notification
 * 
 * Sets the subject, message and radio button to appropriate values 
 */
void ComposeWindow::customersMessage()
{
    subjectLineEdit->setText("ATTENTION CUSTOMERS: Recent COVID-19 Outbreak");
    messageTextEdit->setPlainText("Dear customers,\n\n"
    "We recently became aware that a staff member in our facility tested positive for COVID-19. "
    "While we are unable to identify the individual due to the confidential nature of the medical information, "
    "we can share that it has been a few days since the individual was last in attendance.\n\n"
    "For your saftey, you may receive a call from the health department. "
    "Please stay home and contact your health care provider if you feel sick. "
    "It is recommended that you call ahead to your healthcare provider before going to the physician’s office, "
    "clinic, urgent care or emergency room so they can be prepared for your arrival.\n"
    "\nPlease note, our facility will be temproary closed until furthur notice.\n"
    "\nSincerely,\n"
    "Headcount");
    customersRadioButton->setChecked(true);
}

/**
 * @brief Default message for both customer and employee notification
 * 
 * Sets the subject, message and radio button to appropriate values 
 */
void ComposeWindow::everyoneMessage()
{
    subjectLineEdit->setText("COVID-19: Update");
    messageTextEdit->setPlainText("A Note From Us,\n\n"
    "We have always prioritized the safety of our customers and employees, and in these uncertain times, "
    "this is no different. That’s why we are practicing and enforcing best practices for social distancing "
    "and self-isolation in the midst of COVID-19. We are excited to announce we will be reopening in two weeks! "
    "You can count on us to keep up-to-date with the latest recommendations by provincial guidelines.\n \n"
    "We encourage you to stay safe. This includes practicing safe social distancing. "
    "We are thinking about our customers and look forward to serving you again in the future when lockdown recommendations "
    "have been lifted.\n"
    "\nWe are excited to see you again,\n"
    "\nRegards,\n"
    "Headcount");
    everyoneRadioButton->setChecked(true);
}

/**
 * @brief Clears all the values in add contact fields
 * Sets texts to empty string, uncheck radio buttons and remove focus
 */
void ComposeWindow::clearAll(){
    subjectLineEdit->setText("");
    messageTextEdit->setPlainText("");

    employeesRadioButton->setAutoExclusive(false);
    employeesRadioButton->setChecked(false);
    employeesRadioButton->setAutoExclusive(true);

    customersRadioButton->setAutoExclusive(false);
    customersRadioButton->setChecked(false);
    customersRadioButton->setAutoExclusive(true);

    everyoneRadioButton->setAutoExclusive(false);
    everyoneRadioButton->setChecked(false);
    everyoneRadioButton->setAutoExclusive(true);

    if(subjectLineEdit->hasFocus()){
        subjectLineEdit->clearFocus();
    }
    if(messageTextEdit->hasFocus()){
        messageTextEdit->clearFocus();
    }

}

/**
 * @brief Sends an email to recepient(s)
 * 
 * Finds out which radio buttons is check and assign the recipient to {"Employee", "Customer", "Everyone"}
 * Creates EmailNotification object to send email composed in window by user to recipients
 * 
 */
void ComposeWindow::sendMessage()
{
    QString recipient;
    if(employeesRadioButton->isChecked()){
        recipient = "Employee";
    }
    else if(customersRadioButton->isChecked()){
        recipient = "Customer";
    }
    else if(everyoneRadioButton->isChecked())
    {
        recipient = "Everyone";
    }
    
    EmailNotification email(recipient, subjectLineEdit->text(), messageTextEdit->toPlainText());

    QMessageBox msgBox;
    msgBox.setText("Your message has been sent!");
    msgBox.exec();
    back();
}

/**
 * @brief Closes window when back button is pressed
 * 
 */
void ComposeWindow::back()
{
    window->close();
}
