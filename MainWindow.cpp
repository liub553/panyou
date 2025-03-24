#include "mainwindow.h"
#include "mywidget.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDate>
#include <QtGlobal>
#include <QDateTime>
#include <QPlainTextEdit>
#include <QTime>
#include <QMessageBox>
using namespace std ;


MainWindow::MainWindow(bool isMainWindow,QWidget *parent) : QMainWindow(parent)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    setWindowTitle("界面程序-柳兵-2025-3-23");

    // 公共初始化
    setupMenu();
    setupToolbar();
    setupStatusBar();

    if (isMainWindow) {
        // 创建中央组件和主布局
        QWidget *central = new QWidget(this);
        QHBoxLayout *mainLayout = new QHBoxLayout(central);
        mainLayout->setSpacing(10); // 设置组件之间的间距
        mainLayout->setContentsMargins(10, 10, 10, 10); // 设置边距

        // 左侧表格区域
        QWidget *tableWidget = new QWidget(central);
        QVBoxLayout *tableLayout = new QVBoxLayout(tableWidget);
        tableView = new QTableView(tableWidget);
        tableModel = new QStandardItemModel(8, 5, this);
        QStringList headers = {"列1", "列2", "列3", "列4", "列5"};
        tableModel->setHorizontalHeaderLabels(headers);

        // 填充表格数据
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 5; ++col) {
                QStandardItem *item = new QStandardItem(QString("数据%1").arg(row * 5 + col));
                tableModel->setItem(row, col, item);
            }
        }
        tableView->setModel(tableModel);
        
        QPushButton *reverseBtn = new QPushButton("倒序表格", tableWidget);
        connect(reverseBtn, &QPushButton::clicked, this, &MainWindow::reverseTable);
        
        tableLayout->addWidget(tableView);
        tableLayout->addWidget(reverseBtn);
        mainLayout->addWidget(tableWidget, 4); // 占40%宽度

        // 中间树形图区域
        QWidget *treeWidget = new QWidget(central);
        QVBoxLayout *treeLayout = new QVBoxLayout(treeWidget);
        treeView = new QTreeView(treeWidget);
        treeModel = new QStandardItemModel(this);
        treeModel->setHorizontalHeaderLabels({"树形图标题"});

        for (int i = 0; i < 8; ++i) {
            QStandardItem *parentItem = new QStandardItem(QString("节点%1").arg(i));
            for (int j = 0; j < 5; ++j) {
                int num = qrand() % 50;
                QStandardItem *childItem = new QStandardItem(QString::number(num));
                parentItem->appendRow(childItem);
            }
            treeModel->appendRow(parentItem);
        }
        treeView->setModel(treeModel);
        treeView->expandAll();

        QPushButton *updateBtn = new QPushButton("清零<=25", treeWidget);
        QPushButton *filterBtn = new QPushButton("保留单数行", treeWidget);
        connect(updateBtn, &QPushButton::clicked, this, &MainWindow::updateTreeValues);
        connect(filterBtn, &QPushButton::clicked, this, &MainWindow::filterTreeRows);

        treeLayout->addWidget(treeView);
        treeLayout->addWidget(updateBtn);
        treeLayout->addWidget(filterBtn);
        mainLayout->addWidget(treeWidget, 4); // 占40%宽度

        // 右侧面板
        QWidget *rightPanel = new QWidget(central);
        QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
        
        // 添加自定义控件
        MyWidget *myWidget = new MyWidget(rightPanel);
        myWidget->setMinimumSize(200, 200);
        rightLayout->addWidget(myWidget);

        // 添加TCP组件
        tcpLogDisplay = new QPlainTextEdit(rightPanel);
        tcpLogDisplay->setReadOnly(true);
        tcpControlButton = new QPushButton("启动TCP发送", rightPanel);
        
        tcpSocket = new QTcpSocket(this);
        tcpTimer = new QTimer(this);
        tcpTimer->setInterval(500);

        connect(tcpControlButton, &QPushButton::clicked, this, &MainWindow::onTcpButtonClicked);
        connect(tcpTimer, &QTimer::timeout, this, &MainWindow::sendTcpData);

        rightLayout->addWidget(tcpLogDisplay);
        rightLayout->addWidget(tcpControlButton);
        
        mainLayout->addWidget(rightPanel, 2); // 占20%宽度

        setCentralWidget(central);
        resize(1200, 600);
    } else {
        resize(400, 300);
        setWindowTitle("空白页面");
    }
}

void MainWindow::setupMenu()
{
    // 创建菜单栏
    QMenu *fileMenu = menuBar()->addMenu("文件");
    QMenu *viewMenu = menuBar()->addMenu("视图");
    QMenu *settingsMenu = menuBar()->addMenu("设置");
    QMenu *helpMenu = menuBar()->addMenu("帮助");

    // 添加"打开新页面"动作
    QAction *newWindowAction = new QAction("打开新页面", this);
    connect(newWindowAction, &QAction::triggered, this, &MainWindow::openNewWindow);
    viewMenu->addAction(newWindowAction);
}

void MainWindow::setupToolbar()
{
    // 创建工具栏并添加5个带图标的动作
    QToolBar *toolBar = addToolBar("工具栏");
    QAction *actions[5];
    // 创建带图标的动作
    QAction *playAction = new QAction(QIcon(":/icon/play.png"), "播放", this);
    QAction *pauseAction = new QAction(QIcon(":/icon/pause.png"), "暂停", this);
    QAction *nextAction = new QAction(QIcon(":/icon/next.png"), "下一曲", this);
    QAction *prevAction = new QAction(QIcon(":/icon/previous.png"), "上一曲", this);
    QAction *shezhi = new QAction(QIcon(":/icon/OIP-C.jpg"), "设置", this);

        toolBar->addAction(prevAction);
        toolBar->addAction(playAction);
        toolBar->addAction(pauseAction);
        toolBar->addAction(nextAction);
        toolBar->addAction(shezhi);
    // 连接信号槽
    connect(playAction, &QAction::triggered, this, &MainWindow::printAction1);
    connect(pauseAction, &QAction::triggered, this, &MainWindow::printAction2);
    connect(nextAction, &QAction::triggered, this, &MainWindow::printAction3);
    connect(prevAction, &QAction::triggered, this, &MainWindow::printAction4);
    connect(shezhi, &QAction::triggered, this, &MainWindow::printAction5);
}

void MainWindow::setupStatusBar()
{
    // 状态栏三个区域
    statusBar()->addWidget(new QLabel("左对齐区域", this)); // 左对齐
    statusBar()->addPermanentWidget(new QLabel("右侧区域1", this)); // 右对齐
    statusBar()->addPermanentWidget(new QLabel("右侧区域2", this)); // 右对齐
}

void MainWindow::openNewWindow()
{
    MainWindow *newWindow = new MainWindow(false);
    newWindow->show();
}

void MainWindow::reverseTable()
{
    // 倒序表格行
    QList<QList<QStandardItem*>> rows;
    for (int i = 0; i < tableModel->rowCount(); ++i) {
        QList<QStandardItem*> rowItems;
        for (int j = 0; j < tableModel->columnCount(); ++j) {
            rowItems.append(tableModel->takeItem(i, j));
        }
        rows.prepend(rowItems);
    }

    tableModel->removeRows(0, tableModel->rowCount());
    for (const auto &row : rows) {
        tableModel->appendRow(row);
    }
}

void MainWindow::updateTreeValues()
{
    // 将<=25的值设为0
    for (int i = 0; i < treeModel->rowCount(); ++i) {
        QStandardItem *parent = treeModel->item(i);
        for (int j = 0; j < parent->rowCount(); ++j) {
            QStandardItem *item = parent->child(j);
            if (item->text().toInt() <= 25) {
                item->setText("0");
            }
        }
    }
}

void MainWindow::filterTreeRows()
{
    // 保留单数行（索引从0开始）
    for (int i = treeModel->rowCount() - 1; i >= 0; --i) {
        if (i % 2 == 0) { // 删除偶数索引行
            treeModel->removeRow(i);
        }
    }
}

void MainWindow::onTcpButtonClicked() {
    if (tcpTimer->isActive()) {
        tcpTimer->stop();
        tcpControlButton->setText("启动TCP发送");
        tcpLogDisplay->appendPlainText("已停止发送");
    } else {
        tcpTimer->start();
        tcpControlButton->setText("停止TCP发送");
        tcpLogDisplay->appendPlainText("开始定时发送...");
    }
}

void MainWindow::sendTcpData() {
    QString message = QString("[%1] 数据包").arg(QTime::currentTime().toString("hh:mm:ss.zzz"));
    QByteArray data = message.toUtf8();

    tcpSocket->connectToHost("127.0.0.1", 8080);  // 连接到本地服务器的8080端口
    if (tcpSocket->waitForConnected(1000)) {
        tcpSocket->write(data);
        tcpLogDisplay->appendPlainText("发送: " + message);
    } else {
        tcpLogDisplay->appendPlainText("连接失败: 检查服务器是否运行");
    }
    tcpSocket->disconnectFromHost();
}
