#include "worker.h"
#include <QDebug>

worker::worker(QObject *parent) : QThread(parent)
{

}


worker::~worker()
{
    qDebug() << "析构线程";
    m_abort = true;      // 设置将线程退出标志
    this->wait();        // 等待线程退出
}

void worker::abort()
{
    m_abort = true;
}


void worker::run()
{
    qDebug() << "开始线程";
    m_abort = false;
    int i = 0;
    forever
    {

        qDebug() << "子线程";
        QThread::sleep(1);

        // 退出线程
        if(m_abort) break;
    }

    qDebug() << "退出线程";

}
