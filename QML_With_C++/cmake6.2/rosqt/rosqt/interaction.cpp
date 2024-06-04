#include "interaction.h"

Interaction::Interaction(QObject *parent)
    : QObject{parent}
{
    connect(&control,&Controller::Send_value,this,&Interaction::Receive_value);

}

void Interaction::start_ros()
{
    control.start();
}

QString Interaction::get_ros_value()
{
    return ros_value;
}




void Interaction::Receive_value(QString value)
{
    qDebug() << "ros value: " <<  value;
    ros_value = value;
}
