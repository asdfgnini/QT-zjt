#include "worker.h"

#include <QDebug>
#include <QThread>



Worker::Worker(QObject *parent) : QObject(parent)
{
    node = std::make_shared<TopicSubscribe01>("zjt_SubNode");
    command_subscribe_ = node->create_subscription<std_msgs::msg::String>("command", 10, std::bind(&Worker::command_callback, this, std::placeholders::_1));


}

void Worker::on_doSomething()
{
    qDebug() << "I'm working in thread:" << QThread::currentThreadId();
    qDebug() << "已订阅相关主题 ROS 接收线程开始运行";
    /* 运行节点，并检测退出信号*/

    while (!QThread::currentThread()->isInterruptionRequested())
    {
        // 耗时操作

        rclcpp::spin_some(node);
    }

    // qDebug() << "ros线程 结束";

}
//订阅节点回调函数
void Worker::command_callback(const std_msgs::msg::String::SharedPtr msg)
{
    double speed = 0.0f;
    if(msg->data == "forward")
    {
        speed = 0.2f;
    }
    RCLCPP_INFO(node->get_logger(), "收到[%s]指令，发送速度 %f", msg->data.c_str(),speed);
    emit resultReady(QString(msg->data.c_str()));
}



/******************************************************************/
/******************************************************************/
/******************************************************************/

Controller::Controller(QObject *parent) : QObject(parent)
{
    qDebug() << "Controller's thread is :" << QThread::currentThreadId();

    m_worker = new Worker();
    m_worker->moveToThread(&m_workThread);

    connect(this, &Controller::startRunning, m_worker, &Worker::on_doSomething);
    connect(&m_workThread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(m_worker, &Worker::resultReady, this, &Controller::on_receivResult);

    //开启子线程事件循环
    m_workThread.start();
}

Controller::~Controller()
{
    // qDebug() << "ros线程 销毁";
    m_workThread.quit();
    // qDebug() << "1123";
    m_workThread.requestInterruption();
    m_workThread.wait();
    // qDebug() << "ros线程 退出";
}

void Controller::start()
{
    emit startRunning(m_worker);
}

void Controller::on_receivResult(QString str)
{
    emit Send_value(str);
}
