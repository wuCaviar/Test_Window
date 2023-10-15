#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
{
    qDebug() << "MyWidget";
    image = QImage(":/icon/wo.png");
    // 设置自定义控件类的大小
    setFixedSize(200,200);
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent";
    QPainter painter(this);
    // 自适应控件大小
    painter.drawImage(rect(), image);
}
