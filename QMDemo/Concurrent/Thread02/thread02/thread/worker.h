#pragma once

#include <QThread>


class worker : public QThread
{

public:
    explicit worker(QObject *parent = nullptr);
    ~worker() override;

public slots:
    void abort();//暴露给外界中断线程

protected:
    void run() override;


private:
    bool m_abort = false;


};
