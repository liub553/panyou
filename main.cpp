#include "mainwindow.h"
#include "tcpserver.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    // 创建并显示主窗口（客户端）
    MainWindow w(true);
    w.show();
    
    // 创建并显示服务器窗口
    TcpServer server;
    server.show();
    
    return a.exec();
}
