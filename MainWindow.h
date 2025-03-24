#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTreeView>
#include <QTableView>
#include <QDebug>
#include <QTcpSocket>
#include <QTimer>
#include <QPlainTextEdit>
#include <QPushButton>

class MyWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(bool isMainWindow = true,QWidget *parent = nullptr);

private slots:
    // TCP控制按钮点击
    void onTcpButtonClicked();
    // 定时发送数据
    void sendTcpData();
    //这是组件的
    void openNewWindow();
    void reverseTable();
    void updateTreeValues();
    void filterTreeRows();
    void printAction1()
    {
        qDebug() << "1";
    }
    void printAction2()
    {
        qDebug() << "2";
    }
    void printAction3()
    {
        qDebug() << "3";
    }
    void printAction4()
    {
        qDebug() << "4";
    }
    void printAction5()
    {
        qDebug() << "5";
    }

private:
    void setupMenu();
    void setupToolbar();
    void setupStatusBar();
    void setupTable();
    void setupTree();
    void setupCustomWidget();
    //初始化TCP UI
    void setupTcpSection();

    QStandardItemModel *tableModel;
    QStandardItemModel *treeModel;
    QTableView *tableView;
    QTreeView *treeView;

    // 新增TCP组件
        QPlainTextEdit *tcpLogDisplay;
        QPushButton *tcpControlButton;
        QTimer *tcpTimer;
        QTcpSocket *tcpSocket;
        QString serverIP = "192.168.34.19";
        quint16 serverPort = 8080;

};

#endif // MAINWINDOW_H
