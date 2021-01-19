/**
 * @file EmailNotification.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Send an email to a list of recipients
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef EMAILNOTIFICATION_H
#define EMAILNOTIFICATION_H

#include <QCoreApplication>
#include <SimpleMail/SimpleMail>

/**
 * @brief send an email using smtp.gmail.com with subject and body message
 * 
 */
class EmailNotification
{
private:

public:
  EmailNotification(const QString &recipient, const QString &subject, const QString &body);

  ~EmailNotification();
};

#endif // EMAILNOTIFICATION_H
