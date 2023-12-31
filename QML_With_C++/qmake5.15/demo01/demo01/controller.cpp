#include "controller.h"

#include <QThread>
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    qDebug() << "Controller's thread is :" << QThread::currentThreadId();

    m_worker = new Worker();

    m_worker->moveToThread(&m_workThread);
    connect(this, &Controller::startRunning, m_worker, &Worker::on_doSomething);
    connect(&m_workThread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(m_worker, &Worker::resultReady, this, &Controller::on_receivResult);

    m_worker_02 = new Worker();

    m_worker_02->moveToThread(&m_workThread_02);
    connect(this, &Controller::startRunning, m_worker_02, &Worker::on_doSomething_02);
    connect(&m_workThread_02, &QThread::finished,m_worker_02, &QObject::deleteLater);
    connect(m_worker_02, &Worker::resultReady, this, &Controller::on_receivResult_02);

    m_workThread.start();
    m_workThread_02.start();
}

Controller::~Controller()
{
    m_workThread.quit();
    m_workThread.wait();

    m_workThread_02.quit();
    m_workThread_02.wait();
}

void Controller::start()
{
    emit startRunning();
}

void Controller::on_receivResult(const QString &str)
{
    qDebug() << str;
}
void Controller::on_receivResult_02(const QString &str)
{
    qDebug() << str;
}
