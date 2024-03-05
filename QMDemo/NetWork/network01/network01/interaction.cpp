#include "interaction.h"


Interaction::Interaction(QObject *parent)
    : QObject{parent}
{
    // tcp.Connect("192.168.0.103",8000);
}

Interaction::~Interaction()
{
    qDebug() << "析构";
    quit = true;
}

void Interaction::send(bool hex)
{
    tcp.Send("abc",hex);
}

void Interaction::connt(QString ip, QString port)
{
    qDebug() << ip << port;
    tcp.Connect(ip,port.toInt());
}


bool Interaction::receive_message()
{
    while(!quit)
    {
        if(tcp.getqueue_state())
        {
            continue;
        }
        std::shared_ptr<QByteArray> value = tcp.receive_message();
        qDebug() << "value: " << *value;
        QString str = QString(*value);
        emit signvalue(str);
    }
    return true;
}

bool Interaction::state()
{
    if(tcp.Getstate() == QAbstractSocket::ConnectedState)
    {
        return true;
    }
    return false;
}

void Interaction::setstate(bool state)
{
    tcp.setHexstate(state);
}

void rece(bool state)
{
    qDebug() << state;
}
