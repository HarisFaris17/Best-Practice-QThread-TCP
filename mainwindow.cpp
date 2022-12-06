#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectPushButton = ui->connectPushButton;
    ipAddressLineEdit = ui ->ipAddressLineEdit;
    portLineEdit = ui->portLineEdit;

    qDebug()<<"mainwindow thread : "<<QThread::currentThread();
    connect(connectPushButton,&QPushButton::clicked,this,&MainWindow::connectDisconnectTCP);

}

void MainWindow::connectDisconnectTCP(){
    // it is important to notice when the object was moved to another thread. if there is connection between the object and a calling (signalling) object and the object moved before any Q_EMIT from the calling object , then the slot of the moved object will not be triggered (my theory is that the pointer of the object is not pointing to the moved object in memory
    thread1 = new QThread;
    TCPServer *tcpServer =  new TCPServer();
    connect(this,&MainWindow::config,tcpServer,&TCPServer::config);
    QString ipAddress = ipAddressLineEdit->text();
    QString port = portLineEdit->text();
    int portNumber = port.toInt();
    Q_EMIT config(ipAddress,port);

    qDebug()<<"before moved ptr"<<tcpServer;

    connect(thread1,&QThread::started,tcpServer,&TCPServer::run);
    connect(tcpServer,&TCPServer::unlistened,thread1,&QThread::quit);
    connect(thread1,&QThread::finished,thread1,&QThread::deleteLater);
    tcpServer->moveToThread(thread1);
    thread1->start();

    if(tcpServer==nullptr){
        qDebug()<<"the tcpServer is now null";
    }else{
        qDebug()<<"after moved : "<<tcpServer;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
