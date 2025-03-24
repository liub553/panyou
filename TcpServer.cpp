#include "TcpServer.h"
#include <QDateTime>
#include <QMessageBox>

TcpServer::TcpServer(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    
    // 创建TCP服务器
    server = new QTcpServer(this);
    
    // 尝试在8080端口启动服务器
    if (!server->listen(QHostAddress::Any, 8080)) {
        QMessageBox::critical(this, "错误", "无法启动服务器: " + server->errorString());
        return;
    }
    
    // 连接新客户端连接的信号
    connect(server, &QTcpServer::newConnection, this, &TcpServer::handleNewConnection);
    
    logDisplay->appendPlainText("服务器已启动，正在监听端口 8080...");
    setWindowTitle("TCP服务器 - 监听端口 8080");
}

TcpServer::~TcpServer()
{
    // 关闭所有客户端连接
    for (QTcpSocket* socket : clientSockets) {
        socket->close();
        socket->deleteLater();
    }
    
    // 关闭服务器
    server->close();
}

void TcpServer::setupUi()
{
    // 创建中央部件和布局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    // 创建日志显示区域
    logDisplay = new QPlainTextEdit(this);
    logDisplay->setReadOnly(true);
    layout->addWidget(logDisplay);
    
    // 创建清除按钮
    clearButton = new QPushButton("清除日志", this);
    connect(clearButton, &QPushButton::clicked, this, &TcpServer::clearLog);
    layout->addWidget(clearButton);
    
    setCentralWidget(centralWidget);
    resize(600, 400);
}

void TcpServer::handleNewConnection()
{
    // 获取新的客户端连接
    QTcpSocket *clientSocket = server->nextPendingConnection();
    
    // 连接客户端socket的信号
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServer::handleReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &TcpServer::handleClientDisconnected);
    
    // 添加到客户端列表
    clientSockets.append(clientSocket);
    
    // 记录连接信息
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString clientInfo = QString("%1 - 新客户端连接: %2:%3")
                            .arg(time)
                            .arg(clientSocket->peerAddress().toString())
                            .arg(clientSocket->peerPort());
    logDisplay->appendPlainText(clientInfo);
}

void TcpServer::handleReadyRead()
{
    // 获取发送数据的客户端socket
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;
    
    // 读取数据
    QByteArray data = clientSocket->readAll();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString message = QString("%1 - 收到来自 %2:%3 的数据: %4")
                        .arg(time)
                        .arg(clientSocket->peerAddress().toString())
                        .arg(clientSocket->peerPort())
                        .arg(QString::fromUtf8(data));
    
    logDisplay->appendPlainText(message);
}

void TcpServer::handleClientDisconnected()
{
    // 获取断开连接的客户端socket
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;
    
    // 从客户端列表中移除
    clientSockets.removeOne(clientSocket);
    
    // 记录断开连接信息
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString clientInfo = QString("%1 - 客户端断开连接: %2:%3")
                            .arg(time)
                            .arg(clientSocket->peerAddress().toString())
                            .arg(clientSocket->peerPort());
    logDisplay->appendPlainText(clientInfo);
    
    // 清理socket
    clientSocket->deleteLater();
}

void TcpServer::clearLog()
{
    logDisplay->clear();
    logDisplay->appendPlainText("服务器正在运行，监听端口 8080...");
} 