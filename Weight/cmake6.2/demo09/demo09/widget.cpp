#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    filepath = QString("C:\\Users\\Administrator\\Desktop\\Qt\\demo02\\demo02\\dove_640x360.mp4");
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::slot_play);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot_play()
{
    ui->lineEdit->setText(filepath);
    ui->openGLWidget->play(filepath);
}
