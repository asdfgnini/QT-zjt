#ifndef INTERACTION_H
#define INTERACTION_H

#include <QObject>
#include "./network/tcpclient.h"


class Interaction : public QObject
{
    Q_OBJECT
public:
    explicit Interaction(QObject *parent = nullptr);
    ~Interaction();
    Q_INVOKABLE void send(bool hex);
    Q_INVOKABLE void connt(QString ip,QString port);
    Q_INVOKABLE bool state();
    Q_INVOKABLE void setstate(bool state);
    bool receive_message();

private:
    TCPClient tcp;
    bool quit = false;
signals:
    void signvalue(QString value);

};

extern void rece(bool state);

#endif // INTERACTION_H
