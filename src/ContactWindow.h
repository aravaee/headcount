/**
 * @file ContactWindow.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief prompt a dialogue that allows user to add contact
 * @version 0.1
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CONTACTWINDOW_H
#define CONTACTWINDOW_H
#include <QtWidgets>
#include <QRadioButton>

/**
 * @brief Class for window whcih allows user to add contacts
 * 
 */
class ContactWindow : public QWidget
{
    Q_OBJECT

    public:
        ContactWindow(QWidget *parent = 0);

        ~ContactWindow();
        Q_SLOT void back();
        Q_SLOT void submitContactInformation();
        Q_SLOT void clearAll();

    private:
        QWidget *window;

        QLineEdit *firstNameLineEdit;
        QLineEdit *lastNameLineEdit;
        QLineEdit *emailLineEdit;
        QLineEdit *phoneNumberLineEdit;

        QCheckBox *emailCheckBox;
        QCheckBox *phoneNumberCheckBox;

        QRadioButton *employeeRadioButton;
        QRadioButton *customerRadioButton;


};

#endif // CONTACTWINDOW_H