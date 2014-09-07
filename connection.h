#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>

static bool CreateConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("MyChat");
    if (!db.open())
    {
        qDebug() << "Failed to connect!";
        return false;
    }
    else qDebug() << "Success to connent!";

    ////////////////////////////////////////////////////////////
    //text
    QSqlQuery query(db);
    query.exec("select id ,usernumb from UserInfo");

    while(query.next())
    {
        int value0 = query.value(0).toInt();
        int value1 = query.value(1).toInt();
        qDebug() << value0 << value1 ;
    }
    ////////////////////////////////////////////////////////////

}

#endif // CONNECTION_H
