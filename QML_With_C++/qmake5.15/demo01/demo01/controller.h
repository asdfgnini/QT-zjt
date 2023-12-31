#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

#include "worker.h"

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
    void on_receivResult(const QString &str); // 接收新线程中的结果
    void on_receivResult_02(const QString &str); // 接收新线程中的结果

private:
    QThread m_workThread;
    QThread m_workThread_02;
    Worker *m_worker;
    Worker *m_worker_02;


};
#endif // CONTROLLER_H
