#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "./thread/ThreadWorkerControl.h"
#include <QDebug>
#include <functional>


class Task{

public:
    bool printfvalue()
    {
        qDebug() << "task value: " << m_value;
        return false;
    }

    std::function<bool()> tobind()
    {
        std::function<bool()> func = std::bind(&Task::printfvalue,this);
        return func;
    }

    void setvalue(int value)
    {
        m_value = value;
    }
private:
    int m_value;
};

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

    //普通函数
    uint64_t id = ThreadController::getInstance()->work(workCall, resultCall);
    qDebug() << "id: " << id;

    //类成员函数
    Task task;
    task.setvalue(100);
    id = ThreadController::getInstance()->work(std::bind(&Task::printfvalue,&task),resultCall);
    qDebug() << "task id: " << id;

    //另一种方式类成员函数
    task.setvalue(50);
    id = ThreadController::getInstance()->work(task.tobind(),resultCall);
    qDebug() << "task2 id: " << id;


    qDebug() << ThreadController::getInstance()->getAllWorkId();

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
