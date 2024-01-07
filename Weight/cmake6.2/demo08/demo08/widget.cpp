#include "widget.h"
#include "./ui_widget.h"

#include <QPushButton>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    filepath = QString("F:\\QML\\dove_640x360.mp4");
    // filepath = QString("C:\\Users\\Administrator\\Desktop\\Qt\\demo01\\demo01\\test.mp4");


    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::slot_play);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::slot_stop);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::slot_play()
{
    ui->lineEdit->setText(filepath);
    ui->Player->play(filepath);

}

void Widget::slot_stop()
{
    ui->Player->stop();
}
