#ifndef INDEX_H
#define INDEX_H

#include "chat.h"
#include <QWidget>
#include <QLabel>

namespace Ui {
class Index;
}

class Index : public QWidget
{
    Q_OBJECT

public:

    explicit Index(QWidget *parent = 0);
    ~Index();

private:
    Ui::Index *ui;

    Chat chatform;//定义全局变量，使弹出窗口不会闪退

private slots:
    void ChatForm();
};

#endif // INDEX_H
