/**
 * @file ComposeWindow.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief compose and email
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef COMPOSEWINDOW_H
#define COMPOSEWINDOW_H

#include <QtWidgets>
/**
 * @brief class which represents window that allows user to compose and send notification emails 
 * 
 */
class ComposeWindow : public QWidget
{
    Q_OBJECT

public:
    ComposeWindow(QWidget *parent = 0);

    ~ComposeWindow();

private slots:
    void employeesMessage();
    void customersMessage();
    void everyoneMessage();
    void clearAll();
    void sendMessage();
    void back();

private:
    QWidget *window;
    QLineEdit *subjectLineEdit;
    QTextEdit *messageTextEdit;

    QRadioButton *employeesRadioButton;
    QRadioButton *customersRadioButton;
    QRadioButton *everyoneRadioButton;
};

#endif // COMPOSEWINDOW_H
