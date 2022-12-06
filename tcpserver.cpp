#include "tcpserver.h"

TCPServer::TCPServer()
{
    qDebug()<<"init thread tcpserver : "<<QThread::currentThread();
}

void TCPServer::run(){
    qDebug()<<"current thread tcpserver : "<<QThread::currentThread();
    if(!isListening()){
        listen(QHostAddress(ipAddress),port);
        if(isListening()){
            qDebug()<<tr("Listening on : %1:%2").arg(ipAddress).arg(port);
            qDebug()<<"listening thread tcpserver : "<<QThread::currentThread();
            connect(this,&QTcpServer::newConnection,this,&TCPServer::onNewConnection);
        }else{
            qDebug()<<tr("Can't listen");
            // this will move the thread to main thread
            this->moveToThread(QApplication::instance()->thread());
            Q_EMIT unlistened();
        }
    }
    else{
        qDebug()<<"this TCPServer object already listening";
    }
}

void TCPServer::onNewConnection(){
    qDebug()<<"new connection thread tcpserver : "<<QThread::currentThread();
    QTcpSocket *client = this->nextPendingConnection();
    connect(client,&QTcpSocket::readyRead,this,&TCPServer::onReadyRead);
}

void TCPServer::onReadyRead(){
    qDebug()<<"on ready read thread tcpserver : "<<QThread::currentThread();
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    QString message = client->readAll();
    qDebug()<<message;
}

void TCPServer::config(const QString &ipAddress, const QString &port){
    qDebug()<<"config thread tcpserver : "<<QThread::currentThread();
    this->ipAddress = ipAddress;
    this->port = port.toInt();
    qDebug()<<"IP Address config : "<<ipAddress;
    qDebug()<<"port config : "<<port;
}

void TCPServer::unlisten(){
    close();
    // this will move the thread to main thread
    this->moveToThread(QApplication::instance()->thread());
    Q_EMIT unlistened();
}
