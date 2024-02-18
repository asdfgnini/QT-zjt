#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->openfile,&QPushButton::clicked,this,&Widget::Openfile);
    connect(ui->play,&QPushButton::clicked,this,&Widget::play);
    dt.Start();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::SetPause(bool isPause)
{
    if (isPause)
        ui->play->setText(QString::fromLocal8Bit("播 放 "));
    else
        ui->play->setText(QString::fromLocal8Bit("暂 停 "));
}



void Widget::Openfile()
{
    QString name = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择视频文件"));
    if(name.isEmpty())
    {
        return;
    }
    qDebug() << "file name:" << name;
    this->setWindowTitle(name);
    if(!dt.Open(name.toStdString().c_str(),ui->openGLWidget))
    {
        QMessageBox::information(0,"error","open file failed");
        return;
    }
    SetPause(dt.isPause);
}

void Widget::play()
{
    bool isPause = !dt.isPause;
    SetPause(isPause);
    dt.SetPause(isPause);
}

