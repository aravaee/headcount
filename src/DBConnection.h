/**
 * @file DBConnection.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief definition of DBConnection class
 * @version 1.0
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <vector>

#include <QSqlDatabase>

class DBConnection
{
public:
       DBConnection(const QString &path);
       ~DBConnection();
       bool isConnectionOpen() const;
       void closeConnection();
       bool createTable();
       bool addContact(const QString &FirstName, const QString &LastName, const QString &Email,
                       const QString &PhoneNumber, const QString &Role, const QString &PreferEmail, const QString &PreferPhoneNumber);
       std::vector<std::pair<QString, QString> >listOfEmails(QString recipient);
};

#endif // DBCONNECTION_H
