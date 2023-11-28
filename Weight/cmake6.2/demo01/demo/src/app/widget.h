#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "worker.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    Controller controller;
};
#endif // WIDGET_H
