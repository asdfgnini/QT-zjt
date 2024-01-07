#ifndef FFMPEG_WIDGET_H
#define FFMPEG_WIDGET_H

#include <QWidget>

#include "media.h"
#include "worker.h"
#include <QPaintEvent>

class FFmpeg_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit FFmpeg_Widget(QWidget *parent = nullptr);
    ~FFmpeg_Widget();
    void play(QString filepath);
    void paintEvent(QPaintEvent*);

    void stop();
private:
    Media* media;
    Controller control;
    QImage image;
signals:

public slots:
    void receiveQimage(const QImage &img);
};

#endif // FFMPEG_WIDGET_H
