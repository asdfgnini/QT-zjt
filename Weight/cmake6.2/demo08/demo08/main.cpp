#include "widget.h"

#include <QApplication>

// extern "C"{
// #include "libavutil/avutil.h"
// }


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    // qDebug() << "FFmpeg version is: "<< av_version_info();

    w.show();
    return a.exec();
}
