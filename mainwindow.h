#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcpserver.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public Q_SLOTS:
    void connectDisconnectTCP();

Q_SIGNALS:
    void config(const QString &ipAddress,const QString &port);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLineEdit *ipAddressLineEdit;
    QLineEdit *portLineEdit;
    QPushButton *connectPushButton;
    QThread *thread1;
};

#endif // MAINWINDOW_H
