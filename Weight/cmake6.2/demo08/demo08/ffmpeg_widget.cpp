#include "ffmpeg_widget.h"
#include <QPainter>


FFmpeg_Widget::FFmpeg_Widget(QWidget *parent)
    : QWidget{parent}
{
    media = new Media();
    connect(&control,&Controller::send_IMG,this,&FFmpeg_Widget::receiveQimage);
}

FFmpeg_Widget::~FFmpeg_Widget()
{
    delete media;
}

void FFmpeg_Widget::play(QString filepath)
{
    media->Open(filepath);
    control.start(media);
}

void FFmpeg_Widget::receiveQimage(const QImage &img)
{
    image = img.scaled(this->size());
    update();
}

void FFmpeg_Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,image);
}

void FFmpeg_Widget::stop()
{
    qDebug() << "OK";
    control.stop();

}
