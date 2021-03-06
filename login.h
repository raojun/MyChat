#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "index.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_LoginBtn_clicked();

private:
    Ui::Login *ui;

    Index indexform;
};

#endif // LOGIN_H
