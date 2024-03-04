#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include <QThread>
#include <QImage>




class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:
    void resultReady(); // 向外界发送结果

public slots:
    void on_doSomething(); // 耗时操作
};

//控制类
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void start();
signals:
    void startRunning(); // 用于触发新线程中的耗时操作函数
public slots:
    void on_receivResult(); // 接收新线程中的结果

private:
    QThread m_workThread;
    Worker *m_worker;
};


#endif // WORKER_H
