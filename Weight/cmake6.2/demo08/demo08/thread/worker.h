#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include <QThread>
#include <QImage>


#include "../media.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:
    void resultReady(const QImage &img); // 向外界发送结果

public slots:
    void on_doSomething(Media *media); // 耗时操作
};

//控制类
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void start(Media *media);
    void stop();
signals:
    void startRunning(Media *media); // 用于触发新线程中的耗时操作函数
    void send_IMG(const QImage &img);
public slots:
    void on_receivResult(const QImage &img); // 接收新线程中的结果

private:
    QThread m_workThread;
    Worker *m_worker;
    QImage img;
};


#endif // WORKER_H
