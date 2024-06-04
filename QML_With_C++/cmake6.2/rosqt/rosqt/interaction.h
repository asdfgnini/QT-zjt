#ifndef INTERACTION_H
#define INTERACTION_H

#include <QObject>
#include <QDebug>
#include "thread/worker.h"


class Interaction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ getvalue WRITE setvalue NOTIFY valueChanged)
public:
    explicit Interaction(QObject *parent = nullptr);

    QString getvalue() const { return ros_value; }
        void setvalue(const QString& value) { ros_value = value; emit valueChanged(); }

    Q_INVOKABLE void start_ros();
    Q_INVOKABLE QString get_ros_value();

private:
    Controller control;

    QString ros_value;


signals:
    void valueChanged();
public slots:
    void Receive_value(QString value); //接收来自线程的数据


};

#endif // INTERACTION_H
