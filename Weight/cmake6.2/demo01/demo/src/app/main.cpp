#include "widget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "version: " << qVersion();

    qDebug() << "main's thread is:" << QThread::currentThreadId();
    Widget w;
    w.show();
    return a.exec();
}
