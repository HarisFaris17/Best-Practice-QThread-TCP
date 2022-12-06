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
            qDebug()<<"listening thread this : "<<this->thread();
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
    qDebug()<<"on ready read thread this : "<<this->thread();
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
    qDebug()<<"unlisten called";
    // this will move the thread to main thread
    this->moveToThread(QApplication::instance()->thread());
    qDebug()<<"current tcpserver thread : "<<QThread::currentThread();
//    Q_EMIT unlistened();
}

bool TCPServer::event(QEvent *e){
//    qDebug()<<*e->;
    // this is not useful since the ThreadChanged will be passed to this object just before the thread of this object changed, therefore the currentThread will return the same thread as the main thread
    if(e->type()==QEvent::ThreadChange){
        qDebug()<<"just before TCPSERVER thread CHANGED : "<<QThread::currentThread();
    }

}
