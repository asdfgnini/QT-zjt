#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Interaction/interaction.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Interaction>("Interaction",1,0,"Interaction");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/demo/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
