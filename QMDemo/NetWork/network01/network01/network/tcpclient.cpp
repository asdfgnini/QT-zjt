#include "tcpclient.h"
#include <QHostAddress>
#include <QDebug>
#include <QByteArray>
#include <QHostInfo>

TCPClient::TCPClient(QObject *parent) :
    QObject(parent)
{
    init();
    connectSlots();
}

TCPClient::~TCPClient()
{
#ifdef QT_DEBUG
    qDebug() <<"~TCPClient()";
#endif

    if(m_tcpClient->state() != QAbstractSocket::UnconnectedState)         // 判断连接状态
    {
        m_tcpClient->abort();
    }
}

/**
 * @brief TCP连接
 */
void TCPClient::Connect(QString ipadress,quint16 port)
{
    if(!m_tcpClient)
    {
        return;
    }
    if(m_tcpClient->state() == QAbstractSocket::UnconnectedState)//未连接
    {
         m_tcpClient->connectToHost(ipadress,port);
         state = QAbstractSocket::ConnectedState;
    }
    else
    {
        // 使用abort函数立即关闭套接字，丢弃写入缓冲区中的任何未取数据。
        m_tcpClient->abort();
        state = QAbstractSocket::UnconnectedState;
    }
}

qint64 TCPClient::Send(QString str,bool hexmode)
{
    if(!m_tcpClient) return -1;
    if(m_tcpClient->state() != QAbstractSocket::ConnectedState) return -1;
#if 0
    QByteArray arr = str.toLocal8Bit();              // 根据编译器编码或者 QTextCodec::setCodecForLocale(codec);指定的编码方式将QString转换为QBytearray，一般为utf-8或者GBK，支持中文
#else
    QByteArray arr = str.toUtf8();                   // 指定以utf-8编码
#endif
    if(hexmode)               // 如果是16进制显示则转换
    {
        arr = QByteArray::fromHex(arr);
    }
    qint64 len = m_tcpClient->write(arr);
    if(len < 0)
    {
        qWarning() <<"发送失败！";
    }
    return len;
}

std::shared_ptr<QByteArray> TCPClient::receive_message()
{
    return safe_que.wait_and_pop();
}

QAbstractSocket::SocketState TCPClient::Getstate()
{
    return state;
}

void TCPClient::setHexstate(bool state)
{
    hexstate = state;
}

bool TCPClient::getqueue_state()
{
    return safe_que.empty();
}

void TCPClient::init()
{
    m_tcpClient = new QTcpSocket(this);
}

void TCPClient::connectSlots()
{
    connect(m_tcpClient, &QTcpSocket::connected, this, &TCPClient::on_connected);
    connect(m_tcpClient, &QTcpSocket::disconnected, this, &TCPClient::on_disconnected);
    connect(m_tcpClient, &QTcpSocket::stateChanged, this, &TCPClient::on_stateChanged);
    connect(m_tcpClient, &QTcpSocket::readyRead, this, &TCPClient::on_readyRead);

#if (QT_VERSION <= QT_VERSION_CHECK(5,15,0))        // qt5.15 后error已经弃用，这里改用errorOccurred
    connect(m_tcpClient, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &TCPClient::on_errorOccurred);    // 由于QAbstractSocket中有两个error()，所以不能直接使用Qt5的信号槽绑定方式
#else
    connect(m_tcpClient, &QTcpSocket::errorOccurred, this, &TCPClient::on_errorOccurred);
#endif
}

/**
 * @brief 调用 connectToHost() 并成功建立连接。
 */
void TCPClient::on_connected()
{
    qInfo() << QString("成功连接：%1 %2").arg(m_tcpClient->peerName()).arg(m_tcpClient->peerPort());
}

/**
 * @brief Socket已断开连接
 */
void TCPClient::on_disconnected()
{
    qInfo() <<QString("断开连接：%1 %2").arg(m_tcpClient->peerName()).arg(m_tcpClient->peerPort());
}

/**
 * @brief       QAbstractSocket 的状态发生变化
 * @param state QAbstractSocket::SocketState 不是注册的元类型，因此对于Qt::QueuedConnection信号槽连接类型，
 *              必须使用 Q_DECLARE_METATYPE() 和 qRegisterMetaType() 注册它。
 *              QAbstractSocket::UnconnectedState	0	套接字未连接。
 *              QAbstractSocket::HostLookupState	1	套接字正在查询主机。
 *              QAbstractSocket::ConnectingState	2	套接字开始建立连接。
 *              QAbstractSocket::ConnectedState	    3	新的连接已建立。
 *              QAbstractSocket::BoundState	        4	套接字已绑定到一个地址和端口。
 *              QAbstractSocket::ClosingState	    6	套接字即将关闭（数据可能仍在等待写入）。
 *              QAbstractSocket::ListeningState	    5	套接字仅限内部使用。
 */

void TCPClient::on_stateChanged(QAbstractSocket::SocketState state)
{
    qInfo() << "状态改变："<< state;

}


bool TCPClient::on_readyRead()
{
    QByteArray arr = m_tcpClient->readAll();

    if(arr.length() <= 0)
    {
        return false;
    }

    qDebug() << arr.length();
    qDebug() << arr;
    qDebug() << arr.toHex();
    if(hexstate)
    {
        safe_que.push(std::move(arr.toHex()));
    }
    else
    {
        safe_que.push(std::move(arr));
    }

    // qDebug() << safe_que.empty();
    // ui->spin_recv->setValue(ui->spin_recv->value() + arr.count());
    // if(ui->check_hexRecv->isChecked())
    // {
    //     ui->text_recv->append(arr.toHex(' '));
    // }
    // else
    // {
    //     ui->text_recv->append(arr);
    // }

    return true;
}

/**
 * @brief        发生错误
 * @param error  错误异常信息，QAbstractSocket::SocketError 不是已注册的元类型，
 *               因此对于排队连接，您必须使用 Q_DECLARE_METATYPE() 和 qRegisterMetaType() 注册它。
 *               ConnectionRefusedError：连接被对等方拒绝（或超时）。
 *               RemoteHostClosedError：远程主机关闭了连接。请注意，客户端Socket将在发送远程关闭通知后关闭。
 *               HostNotFoundError：找不到主机地址。
 *               SocketAccessError：Socket操作失败，因为应用程序缺少所需的权限。
 *               SocketResourceError：本地系统资源不足（例如，Socket过多）。
 *               SocketTimeoutError：Socket操作超时。
 *               DatagramTooLargeError：数据报大于操作系统的限制。
 *               NetworkError：网络出现错误（例如，网现被拔出）。
 *               AddressInUseError：指定给 bind() 的地址已在使用中并设置为独占。
 *               SocketAddressNotAvailableError：指定给 bind() 的地址不属于主机。
 *               UnsupportedSocketOperationError：本地操作系统不支持请求的Socket操作（例如，缺乏 IPv6 支持）。
 *               ProxyAuthenticationRequiredError：Socket正在使用代理，并且代理需要身份验证。
 *               SslHandshakeFailedError：SSL/TLS 握手失败，因此连接被关闭（仅在 QSslSocket 中使用）
 *               UnfinishedSocketOperationError：上次尝试的操作尚未完成（仍在后台进行）。
 *               ProxyConnectionRefusedError：无法联系代理服务器，因为与该服务器的连接被拒绝
 *               ProxyConnectionClosedError：在与最终对等方的连接建立之前，与代理服务器的连接意外关闭
 *               ProxyConnectionTimeoutError：与代理服务器的连接超时或代理服务器在身份验证阶段停止响应。
 *               ProxyNotFoundError：未找到使用 setProxy()（或应用程序代理）设置的代理地址。
 *               ProxyProtocolError：与代理服务器的连接协商失败，因为无法理解来自代理服务器的响应。
 *               OperationError：当Socket处于不允许的状态时尝试进行操作。
 *               SslInternalError：正在使用的 SSL 库报告了一个内部错误。这可能是库安装错误或配置错误的结果。
 *               SslInvalidUserDataError：提供了无效数据（证书、密钥、密码等），其使用导致 SSL 库中出现错误。
 *               TemporaryError：发生临时错误（例如，操作会阻塞而Socket是非阻塞的）。
 *               UnknownSocketError：发生不明错误。
 */
void TCPClient::on_errorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "出现异常：" <<error;
}

