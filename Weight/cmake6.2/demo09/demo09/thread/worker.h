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
    void resultReady(unsigned char* p,int w,int h); // 向外界发送结果
    void worker_new_frame();
public slots:
    void on_doSomething(Media *media,unsigned char* out_buffer); // 耗时操作
};

//控制类
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void start(Media *media);

signals:
    void startRunning(Media *media,unsigned char* out_buffer); // 用于触发新线程中的耗时操作函数
    void send_IMG(unsigned char* p,int w,int h);
    void newframe();
public slots:
    void on_receivResult(unsigned char* p,int w,int h); // 接收新线程中的结果
    void on_newframe();
private:
    QThread m_workThread;
    Worker *m_worker;
    unsigned char* out_buffer = nullptr;


};


#endif // WORKER_H
