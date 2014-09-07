#include "index.h"
#include "chat.h"
#include "ui_index.h"
#include <QFile>
#include <QScrollBar>
#include <QTableWidget>
#include <QVBoxLayout>

Index::Index(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Index)
{
    ui->setupUi(this);

    //设置滚动条样式
//    QFile file(":/ScrollBar.qss");
//    file.open(QFile::ReadOnly);
//    ui->FriendList->verticalScrollBar()->setStyleSheet(file.readAll());

    ui->FriendList->setIconSize(QSize(60,60));//设置QListWidget中的单元项的图片大小
    ui->FriendList->addItem(new QListWidgetItem(QIcon(QObject::tr(":/myImage/images/text.png")), QObject::tr("China\n")));
    ui->FriendList->addItem(new QListWidgetItem(QIcon(QObject::tr(":/myImage/images/text.png")), QObject::tr("China\n")));
    connect(ui->FriendList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ChatForm()));
}

Index::~Index()
{
    delete ui;
}

void Index::ChatForm()
{
    chatform.show();
}
