#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "Media/demuxthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void SetPause(bool isPause);

    void Openfile();
    void play();

private:
    Ui::Widget *ui;
    DemuxThread dt;

};
#endif // WIDGET_H
