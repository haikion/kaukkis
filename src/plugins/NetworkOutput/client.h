#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QMutex>
#include "mainwindow.h"
#include "message.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    bool sendMessage(Message& message);
    QString ip() const;
    void setIp(const QString& ip);
    bool connectToHost();

    unsigned port() const;
    void setPort(const unsigned& port);

    bool connected() const;
private:
    static const QString DEFAULT_IP;
    static const unsigned DEFAULT_PORT;
    static const unsigned MAX_DELAY;

    QTcpSocket socket_;
    QString ip_;
    unsigned port_;
    QMutex mutex_;

    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // CLIENT_H
