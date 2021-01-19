/**
 * @file DBConnection.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief manages database and data manipulation
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "DBConnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
/**
 * @brief Construct a new DBConnection::DBConnection object
 * 
 * @param path 
 */
DBConnection::DBConnection(const QString &path)
{
    // Check if database connection is already created
    static bool setup = false;
    if (setup)
    {
        return;
    }
    // Connect to database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    // If app is unable to connect to databse output error
    if (!db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
        setup = true;
    }
}
/**
 * @brief Destroy the DBConnection::DBConnection object
 * 
 */
DBConnection::~DBConnection()
{
    QSqlDatabase db = QSqlDatabase::database(); // default connection
    db.close();
    qDebug() << "~DBConnection() closed the connection";
}
/**
 * @brief check if the connection is open
 * 
 * @return true 
 * @return false 
 */
bool DBConnection::isConnectionOpen() const
{
    QSqlDatabase db = QSqlDatabase::database(); // default connection
    return db.isOpen();
}
/**
 * @brief close the connection and remove the database entirely
 * 
 */
void DBConnection::closeConnection()
{
    QSqlDatabase db = QSqlDatabase::database(); // default connection

    // Check to see if the database connection is open
    if (db.isOpen())
    {
        QString connection;
        connection = db.connectionName();
        // Close connection to databse
        db.close();
        db = QSqlDatabase();
        // Remove database connection
        db.removeDatabase(connection);
        qDebug() << "closeConnection() closed the connection";
    }
}
/**
 * @brief creates table Contact and all the necessary columns
 * 
 * @return true 
 * @return false 
 */
bool DBConnection::createTable()
{
    bool success = true;
    // Query to create Contact table
    QSqlQuery query;
    query.prepare("CREATE TABLE Contact(ID INTEGER PRIMARY KEY, FirstName TEXT NOT NULL, LastName TEXT NOT NULL,"
                  " Email TEXT NOT NULL, PhoneNumber TEXT NOT NULL, Role TEXT NOT NULL, PreferEmail TEXT NOT NULL, PreferPhoneNumber TEXT NOT NULL);");

    // Output error message if query fails
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'Contact': one might already exist.";
        success = false;
    }

    return success;
}
/**
 * @brief adds appropriate data to each field
 * 
 * @param FirstName 
 * @param LastName 
 * @param Email 
 * @param PhoneNumber 
 * @param Role
 * @param PreferEmail 
 * @param PreferPhoneNumber 
 * @return true 
 * @return false 
 */
bool DBConnection::addContact(const QString &FirstName, const QString &LastName, const QString &Email, const QString &PhoneNumber,
                              const QString &Role, const QString &PreferEmail, const QString &PreferPhoneNumber)
{
    bool success = false;

    // Check if all form fields have been populated
    if (!FirstName.isEmpty() && !LastName.isEmpty() && !Email.isEmpty() && !PhoneNumber.isEmpty() && !Role.isEmpty() && !PreferEmail.isEmpty() && !PreferPhoneNumber.isEmpty())
    {
        // Query to insert data into Contact table
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO Contact(FirstName, LastName, Email, PhoneNumber, Role, PreferEmail, PreferPhoneNumber)"
                         " VALUES (:FirstName, :LastName, :Email, :PhoneNumber, :Role, :PreferEmail, :PreferPhoneNumber)");
        queryAdd.bindValue(":FirstName", FirstName);
        queryAdd.bindValue(":LastName", LastName);
        queryAdd.bindValue(":Email", Email);
        queryAdd.bindValue(":PhoneNumber", PhoneNumber);
        queryAdd.bindValue(":Role", Role);
        queryAdd.bindValue(":PreferEmail", PreferEmail);
        queryAdd.bindValue(":PreferPhoneNumber", PreferPhoneNumber);
        qDebug() << FirstName << LastName << Email << PhoneNumber << Role << PreferEmail << PreferPhoneNumber;

        // If contact was added successfully return true
        if (queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "addContact failed: " << queryAdd.lastError();
        }
    }
    // If any of the fields were not filled in, output error message
    else
    {
        qDebug() << "addContact failed: fields cannot be empty";
    }

    return success;
}

/**
 * @brief Construct a vector containing names and emails depending on the role
 * 
 * @param recipient 
 */
std::vector<std::pair<QString, QString> >DBConnection::listOfEmails(QString recipient)
{
    // Vector of type pair, contains two strings, names and emails
    std::vector<std::pair<QString, QString> > namesAndEmails;
    QSqlDatabase db = QSqlDatabase::database(); // default connection

    // Check to see if the database connection is open
    if (db.isOpen())
    {
        // Query to get all the necessary information about the contacts
        QSqlQuery query("SELECT * FROM Contact");
        int FirstNameID = query.record().indexOf("FirstName");
        int LastNameID = query.record().indexOf("LastName");
        int EmailID = query.record().indexOf("Email");
        int RoleID = query.record().indexOf("Role");
        int PreferEmailID = query.record().indexOf("PreferEmail");

        QString FirstName;
        QString LastName;
        QString FullName;
        QString Email;
        QString Role;
        QString PreferEmail;

        // Go through every contact
        while (query.next())
        {
            // Store full name, role and if they prefer to be contacted by email
            FirstName = query.value(FirstNameID).toString();
            LastName = query.value(LastNameID).toString();
            Role = query.value(RoleID).toString();
            PreferEmail = query.value(PreferEmailID).toString();

            // Check to see if the person wants to be contacted
            // Check to see if recipient is either "Employee" or "Customer" and if they are, add them to the vector
            if(PreferEmail == "1"){
                if(Role == recipient){
                    Email = query.value(EmailID).toString();
                    FullName = FirstName + " " + LastName;
                    namesAndEmails.push_back(std::make_pair(FullName, Email));
                }
                // If recipient is everyone, store both "Employee" and "Customer in the vector
                else if("Everyone" == recipient){
                    Email = query.value(EmailID).toString();
                    FullName = FirstName + " " + LastName;
                    namesAndEmails.push_back(std::make_pair(FullName, Email));
                }
            }
        }
    }
    return namesAndEmails;
}