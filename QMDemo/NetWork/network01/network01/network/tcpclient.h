#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include "queue.h"
// #include <QByteArray>

class TCPClient : public QObject
{
    Q_OBJECT

public:
    explicit TCPClient(QObject *parent = nullptr);
    ~TCPClient();

    void Connect(QString ipadress,quint16 port);
    qint64 Send(QString str,bool hexmode = false);
    std::shared_ptr<QByteArray> receive_message();
    QAbstractSocket::SocketState Getstate();
    void setHexstate(bool state);

    bool getqueue_state();

private:
    void init();
    void connectSlots();

private slots:
    void on_connected();
    void on_disconnected();
    void on_stateChanged(QAbstractSocket::SocketState state);
    bool on_readyRead();
    void on_errorOccurred(QAbstractSocket::SocketError error);


private:
    QTcpSocket* m_tcpClient = nullptr;
    threadsafe_queue_ptr<QByteArray> safe_que;
    QAbstractSocket::SocketState state = QAbstractSocket::UnconnectedState;
    bool hexstate = false;
};

#endif // TCPCLIENT_H
