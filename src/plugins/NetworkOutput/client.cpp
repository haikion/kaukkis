#include <QDebug>
#include <QtNetwork/QAbstractSocket>
#include "client.h"

const QString Client::DEFAULT_IP = "127.0.0.1";
const unsigned Client::DEFAULT_PORT = 4385;
const unsigned Client::MAX_DELAY = 500;

static inline QByteArray IntToArray(qint32 source);

Client::Client(QObject* parent) :
    QObject(parent),
    ip_(DEFAULT_IP),
    port_(DEFAULT_PORT)
{
}

//Writes Message object into a socket
bool Client::sendMessage(Message& message)
{
    QByteArray serializedMessage = message.serialize();

    connectToHost();
    if (socket_.state() != QAbstractSocket::ConnectedState)
    {
        displayError(socket_.error());
        return false;
    }
    mutex_.lock();
    qDebug() << "Client: Sending" << QString::number(serializedMessage.size()).toStdString().c_str()
             << "bytes";
    socket_.write(serializedMessage);
    socket_.waitForBytesWritten(MAX_DELAY);
    mutex_.unlock();
    return true;
}

//Displays network related errors
void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the "
                 << "host name and port settings.";
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. "
                 << "Make sure the server is running, "
                 << "and check that the host name and port "
                 << "settings are correct.";
        break;
    default:
        qDebug() << "The following error occurred:"
                 << socket_.errorString();
    }
}

QString Client::ip() const
{
    return ip_;
}

void Client::setIp(const QString& ip)
{
    ip_ = ip;
}

bool Client::connectToHost()
{
    if (socket_.state() == QAbstractSocket::UnconnectedState)
    {
        qDebug().nospace() << "Connecting to the host: "
                           << ip_.toStdString().c_str()
                           << ":" <<  QString::number(port_).toStdString().c_str();
        socket_.connectToHost(ip_, port_);
        socket_.waitForConnected(MAX_DELAY);
    }
    return connected();
}
unsigned Client::port() const
{
    return port_;
}

void Client::setPort(const unsigned& port)
{
    port_ = port;
}

bool Client::connected() const
{
    return ( socket_.state() != QAbstractSocket::UnconnectedState );
}


QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
