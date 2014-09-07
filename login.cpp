#include "login.h"
#include "index.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}

void Login::on_LoginBtn_clicked()
{

    indexform.show();
    this->close();
}
