#include "mywidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);  // 允许样式背景
    setStyleSheet("Qt::yellow"); // 直接设置背景色
}

void MyWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制黄色圆形
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(rect().adjusted(10, 10, -10, -10)); // 边距10像素
}
