#ifndef MYWIDGET
#define MYWIDGET

#include <QWidget>

class MyWidget : public QWidget {
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MYWIDGET

