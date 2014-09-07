#ifndef CHAT_H
#define CHAT_H

#include <QWidget>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    ~Chat();

private slots:
    void on_fontComboBox_currentFontChanged(QFont f);

    void on_sizecComboBox_currentIndexChanged(QString);

    void on_BoldToolBtn_clicked(bool checked);

    void on_ItalicToolBtn_clicked(bool checked);

    void on_UnderToolBtn_clicked(bool checked);

    void on_ColorToolBtn_clicked();

    void on_SaveToolBtn_clicked();

    void on_SendToolBtn_clicked();

    void on_ClearToolBtn_clicked();

private:
    Ui::Chat *ui;

    QColor color;
    QString fileName;

    bool saveFile(const QString &fileName);//保存聊天记录
};

#endif // CHAT_H
