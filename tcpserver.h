#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QThread>
#include <QEvent>


class TCPServer : public QTcpServer
{
    Q_OBJECT
public Q_SLOTS:
    void onNewConnection();
    void onReadyRead();
    void config(const QString &ipAddress,const QString &port);
    void unlisten();
    // here handle the event of thread changed. remember that event is not signal, therefore we should handle it
    bool event(QEvent *e) override;

Q_SIGNALS:
    void unlistened();
    \
public:
    TCPServer();
    void run();

private:
    QString ipAddress;
    int port;
};

#endif // TCPSERVER_H
