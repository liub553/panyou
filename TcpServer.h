#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class TcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private slots:
    void handleNewConnection();
    void handleReadyRead();
    void handleClientDisconnected();
    void clearLog();

private:
    QTcpServer *server;
    QList<QTcpSocket*> clientSockets;
    QPlainTextEdit *logDisplay;
    QPushButton *clearButton;
    
    void setupUi();
};

#endif // TCPSERVER_H 