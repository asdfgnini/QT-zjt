#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"



//ROS 订阅
class TopicSubscribe01 : public rclcpp::Node
{
public:
    TopicSubscribe01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已创建", name.c_str());
    }

private:

};



class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

private:
    //声明一个节点
    std::shared_ptr<TopicSubscribe01> node;
    // 声明一个订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_;
     // 收到话题数据的回调函数
    void command_callback(const std_msgs::msg::String::SharedPtr msg);

signals:
    void resultReady(QString str); // 向外界发送结果

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



signals:
    void startRunning(Worker *m_worker); // 用于触发新线程中的耗时操作函数

public slots:
    void on_receivResult(QString str); // 接收新线程中的结果
    void start();

signals:
    void Send_value(QString value);

private:
    QThread m_workThread;
    Worker *m_worker;
};





#endif // WORKER_H
