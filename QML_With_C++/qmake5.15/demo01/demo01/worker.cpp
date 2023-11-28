#include "worker.h"

#include <QDebug>
#include <QThread>

Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::on_doSomething()
{
    qDebug() << "I'm working in thread:" << QThread::currentThreadId();
    qDebug() << "发送指令";
    m_mutex.lock();
    emit resultReady("设备识别判断");
    m_mutex.unlock();
}

void Worker::on_doSomething_02()
{
    m_mutex.lock();
    qDebug() << "I'm working_02 in thread:" << QThread::currentThreadId();


    emit resultReady("接收数据完成");
    m_mutex.unlock();
}

