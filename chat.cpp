#include "chat.h"
#include "ui_chat.h"
#include <QFile>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

Chat::~Chat()
{
    delete ui;
}


//设置字体样式
void Chat::on_fontComboBox_currentFontChanged(QFont f)
{
    ui->MessageEdit->setCurrentFont(f);
    ui->MessageEdit->setFocus();
}


//设置字体大小
void Chat::on_sizecComboBox_currentIndexChanged(QString size)
{
    ui->MessageEdit->setFontPointSize(size.toDouble());
    ui->MessageEdit->setFocus();
}

//字体加粗
void Chat::on_BoldToolBtn_clicked(bool checked)
{
    if(checked)
    {
        ui->MessageEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->MessageEdit->setFontWeight(QFont::Normal);
    }
    ui->MessageEdit->setFocus();
}

//字体倾斜
void Chat::on_ItalicToolBtn_clicked(bool checked)
{
    ui->MessageEdit->setFontItalic(checked);
    ui->MessageEdit->setFocus();
}

//添加下划线
void Chat::on_UnderToolBtn_clicked(bool checked)
{
    ui->MessageEdit->setFontUnderline(checked);
    ui->MessageEdit->setFocus();
}

//设置字体颜色
void Chat::on_ColorToolBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
    if (color.isValid())
    {
        ui->MessageEdit->setTextColor(color);
        ui->MessageEdit->setFocus();
    }
}

//保存聊天记录
void Chat::on_SaveToolBtn_clicked()
{
    if(ui->MessageBrowser->document()->isEmpty())
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
    out<<ui->MessageBrowser->toPlainText();
    return true;
}

//发送文件
void Chat::on_SendToolBtn_clicked()
{

}

//删除聊天记录
void Chat::on_ClearToolBtn_clicked()
{
    ui->MessageBrowser->clear();
}
