#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QUdpSocket>
#include <QTextCharFormat>

namespace Ui {
class Chat;
}

//定义枚举类型，用来区分不同的广播类型
enum MessageType {
    Message,//消息
    NewParticipant,//新用户加入
    ParticipantLeft,//用户退出
    FileName,//文件名
    Refuse //拒绝接收文件
};

class QUdpSocket;

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    ~Chat();

private slots:
    void processPendingDatagrams();

    void currentFormatChanged(const QTextCharFormat &format);

    void on_fontComboBox_currentFontChanged(QFont f);

    void on_sizecComboBox_currentIndexChanged(QString);

    void on_BoldToolBtn_clicked(bool checked);

    void on_ItalicToolBtn_clicked(bool checked);

    void on_UnderToolBtn_clicked(bool checked);

    void on_ColorToolBtn_clicked();

    void on_SaveToolBtn_clicked();

    void on_SendToolBtn_clicked();

    void on_ClearToolBtn_clicked();

    void on_SendBtn_clicked();

private:
    Ui::Chat *ui;

    QUdpSocket * udpSocket;
    qint16 port;

    QColor color;
    QString fileName;

    bool saveFile(const QString &fileName);//保存聊天记录
    void sendMessage(MessageType type,QString serverAddress="");
    QString getIP();
    QString getUserName();
    QString getMessage();
};

#endif // CHAT_H
