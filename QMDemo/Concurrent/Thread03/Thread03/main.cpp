#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "./thread/ThreadWorkerControl.h"
#include <QDebug>

bool workCall()
{
    qDebug() << "执行子线程任务";
    return true;
}

void resultCall(bool state)
{
    qDebug() << state;
    qDebug() << "执行子线程任务结果";
}


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);


    uint64_t id = ThreadController::getInstance()->work(workCall, resultCall);
    qDebug() << "id: " << id;
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
