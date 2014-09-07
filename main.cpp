#include "connection.h"
#include "login.h"
#include "index.h"
#include <QApplication>
#include <QTextCodec>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(CreateConnection())
    {
        return 1;
    }

    // 打开MySQL


    Login w;
    w.show();

    return a.exec();
}
