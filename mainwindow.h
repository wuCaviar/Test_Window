#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTableWidget>
#include <QTreeWidget>
#include <QTimer>
#include <QToolButton>
#include <QLabel>
#include <QRandomGenerator>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTextEdit>

#include "mywidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void setMenubar();
    void setToolbar();
    void setStatusBar();
    void addTable();
    void addTree();
    void addWidget();
    void tcp_test();
    void layoutWidget();
private:
    Ui::MainWindow *ui;

    QTableWidget *table;
    QPushButton *sortButton;

    QTableView *view;
    QPushButton *zeroButton;
    QPushButton *filterButton;

    QWidget *myWidget;

    QTextEdit *record;
    QPushButton *sendButton;
    QTcpSocket *socket;
};
#endif // MAINWINDOW_H
