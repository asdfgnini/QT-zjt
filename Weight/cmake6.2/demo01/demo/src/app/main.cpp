#include "widget.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "main's thread is: " << QThread::currentThreadId();
    QPushButton button;


    Widget w;
    w.show();
    return a.exec();
}
