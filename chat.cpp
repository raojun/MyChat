#include "chat.h"
#include "ui_chat.h"
#include <QFile>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include <QPushButton>
#include <QColorDialog>
#include <QudpSocket>
#include <QHostInfo>

Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);

    udpSocket=new QUdpSocket(this);//创建UDP套接字并初始化
    port=45454;
    udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);

    //关联信号和槽
    connect(ui->messageTextEdit,SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this,SLOT(currentFormatChanged(const QTextCharFormat)));
}

Chat::~Chat()
{
    delete ui;
}

void Chat::sendMessage(MessageType type,QString serverAddress)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    QString localHostName=QHostInfo::localHostName();
    QString address=getIP();
    out<<type<<getUserName()<<localHostName;

    switch(type)
    {
        case Message:
            if (ui->messageTextEdit->toPlainText()=="")//判断消息是否为空
            {
                QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
                return;
            }
            out<<address<<getMessage();//想发送的数据中写入本机IP和输入的消息文本
            ui->messageBrower->verticalScrollBar()->setValue(ui->messageBrower->verticalScrollBar()->maximum());
            break;
        case NewParticipant:
            break;
        case ParticipantLeft:
            break;//离开用户不做任何处理
        case FileName:
            break;
        case Refuse:
            break;
    }

    //使用writeDatagram()函数进行UDP广播
    udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,port);
}

//processPendingDatagrams()槽的实现
void Chat::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(&datagram,QIODevice::ReadOnly);
        int messageType;
        in>>messageType;//获取消息类型
        QString userName,localHostName,ipAddress,message;
        QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        switch(messageType)
        {
            case Message://普通信息，就获取用户名，主机名，IP和消息数据
                in>>userName>>localHostName>>ipAddress>>message;
                ui->messageBrower->setTextColor(Qt::blue);
                ui->messageBrower->setCurrentFont(QFont("Times New Roman",12));
                ui->messageBrower->append("["+userName+"]"+time);
                ui->messageBrower->append(message);
                break;
            case NewParticipant:

                break;
            case ParticipantLeft:

                break;
            case FileName:

                break;
            case Refuse:

                break;
        }
    }
}

//获取IP地址
QString Chat::getIP()
{
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    foreach(QHostAddress address,list)
    {
        if(address.protocol()==QAbstractSocket::IPv4Protocol)
        {
            return address.toString();
        }
    }
    return 0;
}

//获取用户名
QString Chat::getUserName()
{
    QStringList envVariables;
    envVariables<<"USERNAME.*"<<"USER.*"<<"USERDOMAIN.*"
                <<"HOSTNAME.*"<<"DOMAINNAME.*";
    QStringList environment=QProcess::systemEnvironment();
    foreach(QString string,envVariables)
    {
        int index=environment.indexOf(QRegExp(string));
        if(index!=-1)
        {
            QStringList stringList=environment.at(index).split('=');
            if(stringList.size()==2)
            {
                return stringList.at(1);
                break;
            }
        }
    }
    return "unknown";
}

//获取用户输入的聊天信息
QString Chat::getMessage()
{
    //从消息文本编辑器中获取用户输入的聊天信息
    QString msg=ui->messageTextEdit->toHtml();
    ui->messageTextEdit->clear();//将文本编辑器中的内容清空
    ui->messageTextEdit->setFocus();
    return msg;
}

//currentFormatChanged()槽的定义
void Chat::currentFormatChanged(const QTextCharFormat &format)
{
    ui->fontComboBox->setCurrentFont(format.font());
    //如果字体大小出错，使用12号字体
    if(format.fontPointSize()<9)
    {
        ui->sizecComboBox->setCurrentIndex(3);
    }
    else
    {
        ui->sizecComboBox->setCurrentIndex(ui->sizecComboBox
                ->findText(QString::number(format.fontPointSize())));
    }
    ui->BoldToolBtn->setChecked(format.font().bold());
    ui->ItalicToolBtn->setChecked(format.font().italic());
    ui->UnderToolBtn->setChecked(format.font().underline());
    color=format.foreground().color();
}

//设置字体样式
void Chat::on_fontComboBox_currentFontChanged(QFont f)
{
    ui->messageTextEdit->setCurrentFont(f);
    ui->messageTextEdit->setFocus();
}


//设置字体大小
void Chat::on_sizecComboBox_currentIndexChanged(QString size)
{
    ui->messageTextEdit->setFontPointSize(size.toDouble());
    ui->messageTextEdit->setFocus();
}

//字体加粗
void Chat::on_BoldToolBtn_clicked(bool checked)
{
    if(checked)
    {
        ui->messageTextEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->messageTextEdit->setFontWeight(QFont::Normal);
    }
    ui->messageTextEdit->setFocus();
}

//字体倾斜
void Chat::on_ItalicToolBtn_clicked(bool checked)
{
    ui->messageTextEdit->setFontItalic(checked);
    ui->messageTextEdit->setFocus();
}

//添加下划线
void Chat::on_UnderToolBtn_clicked(bool checked)
{
    ui->messageTextEdit->setFontUnderline(checked);
    ui->messageTextEdit->setFocus();
}

//设置字体颜色
void Chat::on_ColorToolBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
    if (color.isValid())
    {
        ui->messageTextEdit->setTextColor(color);
        ui->messageTextEdit->setFocus();
    }
}

//保存聊天记录
void Chat::on_SaveToolBtn_clicked()
{
    if(ui->messageBrower->document()->isEmpty())
    {
        QMessageBox::warning(0,tr("警告"),tr("聊天记录为空，无法保存！"),QMessageBox::Ok);
    }
    else
    {
        QString fileName=QFileDialog::getSaveFileName(this,tr("保存聊天记录"),
                            tr("聊天记录"),tr("文本(*.txt);;All File(*.*"));
        if(!fileName.isEmpty())
        {
            saveFile(fileName);
        }
    }
}

//保存文件
bool Chat::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,tr("保存文件"),tr("无法保存文件 %1:\n%2")
                                    .arg(fileName)
                                    .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out<<ui->messageBrower->toPlainText();
    return true;
}

//发送文件
void Chat::on_SendToolBtn_clicked()
{

}

//删除聊天记录
void Chat::on_ClearToolBtn_clicked()
{
    ui->messageBrower->clear();
}

//发送信息
void Chat::on_SendBtn_clicked()
{
    sendMessage(Message);
}
