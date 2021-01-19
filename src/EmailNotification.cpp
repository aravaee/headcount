/**
 * @file EmailNotification.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Send an email to a list of recipients
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <QtCore>
#include <SimpleMail/SimpleMail>
#include "EmailNotification.h"
#include "DBConnection.h"
#include <QDebug>

/**
 * @brief Construct Email Notification object to send an email to a list of recipients
 * 
 * Create a connection the database and calls a function that returns list of emails in a vector of type pair.
 * Make a connection to the server, in this case smtp, along with necessary credentials
 * If the connection was sucessful, it will loop through the list of emails and send email to each person
 * 
 * @param recipient 
 * @param subject 
 * @param body 
 */
EmailNotification::EmailNotification(const QString &recipient, const QString &subject, const QString &body)
{
    // Create a connection to the database and pull the list of emails
    DBConnection DB("ContactList.db");
    std::vector<std::pair<QString, QString> > namesAndEmails = DB.listOfEmails(recipient);

    // Sender's credential
    const QString senderEmail = "headcountdemo@gmail.com";
    const QString senderPassword = "HeadcountDemo1234";
    const QString senderName = "Headcount Demo";

    QString recipientName = "";
    QString recipientEmail = "";

    // First we need to create an Server object
    auto server = new SimpleMail::Server;

    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)
    server->setHost(QLatin1String("smtp.gmail.com"));
    server->setPort(465);
    server->setConnectionType(SimpleMail::Server::SslConnection);

    // We need to set the username and the password for smtp authentification.
    server->setUsername(senderEmail);
    server->setPassword(senderPassword);

    for (const auto& p : namesAndEmails)
    {
        recipientName = p.first;
        recipientEmail = p.second;

        // Now we create a MimeMessage object. This will be the email.
        SimpleMail::MimeMessage message;
        message.setSender(SimpleMail::EmailAddress(senderEmail, senderName));
        message.setSubject(subject);
        
        // First we create a MimeText object.
        // This must be created with new otherwise it will be deleted once we leave the scope.
        auto text = new SimpleMail::MimeText;

        // Now add some text to the email.
        text->setText(body);

        // Now add it to the mail
        message.addPart(text);
        message.addTo(SimpleMail::EmailAddress(recipientEmail, recipientName));
        
        // Now we can send the mail
        SimpleMail::ServerReply *reply = server->sendMail(message);
        QObject::connect(reply, &SimpleMail::ServerReply::finished, [reply] {
            qDebug() << "ServerReply finished" << reply->error() << reply->responseText();
            reply->deleteLater(); // delete object
        });
        qDebug() << "END";
    }
}

/**
 * @brief Destroy Email Notification object
 * 
 */
EmailNotification::~EmailNotification()
{
}

