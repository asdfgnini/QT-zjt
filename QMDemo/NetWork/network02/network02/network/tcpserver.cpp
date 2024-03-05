#include "tcpserver.h"
#include <QAbstractSocket>
#include <QDebug>
#include <qhostinfo.h>


TCPServer::TCPServer(QObject *parent) :
    QObject(parent)
{
    init();
    connectSlots();
}

TCPServer::~TCPServer()
{
#ifdef QT_DEBUG
    qDebug() <<"~TCPServer()";
#endif

}

bool TCPServer::Listen()
{
    if(!m_tcpServer) return;

    if(!m_tcpServer->isListening())
    {
        // 告诉服务器侦听地址和端口上的传入连接。如果端口为0，则会自动选择一个端口。
        // 如果地址是QHostAddress:：Any，服务器将监听所有网络接口。
        bool ret = m_tcpServer->listen(QHostAddress::Any, ui->spin_localPort->value());
        if(ret)
        {
            // ui->but_connect->setText("停止");
            qDebug() << "正在监听......";
        }
        else
        {
            qDebug() << QString("tcpServer绑定监听IP、端口失败：%1 %2").arg(m_tcpServer->errorString()).arg(m_tcpServer->serverError());
        }
    }
    else
    {
        m_tcpServer->close();
        ui->but_connect->setText("开始监听");
        for(int i = m_tcpClients.count() - 1; i >= 0 ; i--)          // 关闭所有连接的TCP Client
        {
            m_tcpClients.at(i)->abort();
        }
    }

    return ret;
}


void TCPServer::init()
{
    m_tcpServer = new QTcpServer(this);
    m_tcpServer->setMaxPendingConnections(30);     // 设置最大允许连接数，不设置的话默认为30(如果设置过大就需要考虑内存泄漏问题)
}

void TCPServer::connectSlots()
{
    connect(m_tcpServer, &QTcpServer::newConnection, this, &TCPServer::on_newConnection);    // 监听新的客户端连接
    connect(m_tcpServer, &QTcpServer::acceptError, this, &TCPServer::on_acceptError);        // 当接受新连接导致错误时，会发出此信号
}


void TCPServer::on_newConnection()
{
    while (m_tcpServer->hasPendingConnections())
    {
        QTcpSocket* tcpSocket = m_tcpServer->nextPendingConnection();      // 存在内存泄漏，最好使用时通过hasPendingConnections判断是否有未返回的连接
        if(tcpSocket)
        {
            m_tcpClients.append(tcpSocket);
        }
        connect(tcpSocket, &QTcpSocket::disconnected, this, &TCPServer::on_disconnected);        // 断开连接
        connect(tcpSocket, &QTcpSocket::readyRead, this, &TCPServer::on_readyRead);

        QString strPeer = QString("%1 %2").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());
        strPeer.remove("::ffff:");
        m_info.append(strPeer);
    }
}

/**
 * @brief               处理连接中的异常详细
 * @param socketError
 */
void TCPServer::on_acceptError(QAbstractSocket::SocketError socketError)
{
    qWarning() << QString("TcpServer异常：%1").arg(socketError);
}


/**
 * @brief Socket  已断开连接
 */
void TCPServer::on_disconnected()
{
    for(int i = 0; i < m_tcpClients.count(); i++)
    {
        if(m_tcpClients.at(i)->state() != QAbstractSocket::ConnectedState)       // 未连接
        {
            disconnect(m_tcpClients.at(i), &QTcpSocket::disconnected, this, &TCPServer::on_disconnected);
            disconnect(m_tcpClients.at(i), &QTcpSocket::readyRead, this, &TCPServer::on_readyRead);
            m_tcpClients.takeAt(i)->deleteLater();       // 移除已经断开连接的Client（注意这里不能使用delete，否则在vs中会报错）
            QListWidgetItem * item = ui->listWidget->item(i);
            ui->listWidget->removeItemWidget(item);
            delete item;                    // 不加这一行 listwidget的count不会变化
            item = nullptr;
        }
    }
}

/**
 * @brief 接收数据
 */
void TCPServer::on_readyRead()
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(m_tcpClients.at(i)->bytesAvailable() <= 0) continue;;       // 如果无可读数据则返回

        QByteArray arr = m_tcpClients.at(i)->readAll();                // 读取数据
        QCheckBox* checkBox = (QCheckBox*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        if(checkBox->isChecked())                                      // 勾选的已连接Client则显示接收的信息
        {
            if(arr.count() <= 0)
            {
                continue;
            }
            ui->spin_recv->setValue(ui->spin_recv->value() + arr.count());  // 统计接收的数据总大小
            QString strPeer = checkBox->text();
            if(ui->check_hexRecv->isChecked())
            {
                ui->text_recv->append(QString("[%1] ").arg(strPeer) + arr.toHex(' '));
            }
            else
            {
                ui->text_recv->append(QString("[%1] ").arg(strPeer) + arr);
            }
        }
    }
}

