#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include "mainwindow.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QImage image;
};

#endif // MYWIDGET_H
