#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("界面程序-吴晓宇-23/10/12");
    setWindowIcon(QIcon(":/icon/wo.png"));

    setMenubar();
    setToolbar();
    setStatusBar();

    addTable();
    addTree();
    //addWidget();
    tcp_test();

    layoutWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMenubar()
{
    this->menuBar()->addMenu("文件");
    this->menuBar()->addMenu("编辑");
    QMenu *menuView  = this->menuBar()->addMenu("视图");
    this->menuBar()->addMenu("帮助");
    menuView->addAction("打开新页面");
    connect(menuView->actions().at(0), &QAction::triggered, this, [=](){
        QMainWindow *new_window = new QMainWindow;
        new_window->show();
        QTimer::singleShot(2000, new_window, &QMainWindow::close);
    });
}

void MainWindow::setToolbar()
{
    QToolButton *welButton = new QToolButton(this);
    welButton->setText("欢迎");
    welButton->setIcon(QIcon(":/icon/welcome.png"));
    //只显示图标
    welButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(welButton, &QToolButton::clicked, this, [=](){
        qDebug() << "欢迎";
    });
    QToolButton *editButton = new QToolButton(this);
    editButton->setText("编辑");
    editButton->setIcon(QIcon(":/icon/editor.png"));
    editButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(editButton, &QToolButton::clicked, this, [=](){
        qDebug() << "编辑";
    });
    QToolButton *debugButton = new QToolButton(this);
    debugButton->setText("调试");
    debugButton->setIcon(QIcon(":/icon/debug.png"));
    debugButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(debugButton, &QToolButton::clicked, this, [=](){
        qDebug() << "调试";
    });
    QToolButton *projectButton = new QToolButton(this);
    projectButton->setText("项目");
    projectButton->setIcon(QIcon(":/icon/project.png"));
    projectButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(projectButton, &QToolButton::clicked, this, [=](){
        qDebug() << "项目";
    });
    QToolButton *helpButton = new QToolButton(this);
    helpButton->setText("帮助");
    helpButton->setIcon(QIcon(":/icon/help.png"));
    helpButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(helpButton, &QToolButton::clicked, this, [=](){
        qDebug() << "帮助";
    });

    ui->toolbar->addWidget(welButton);
    ui->toolbar->addWidget(editButton);
    ui->toolbar->addWidget(debugButton);
    ui->toolbar->addWidget(projectButton);
    ui->toolbar->addWidget(helpButton);
    ui->toolbar->setMovable(false);
    ui->toolbar->addSeparator();
}

void MainWindow::setStatusBar()
{
    // 第一个显示区域内容左对齐
    QLabel *label1 = new QLabel("第一个显示区", this);
    label1->setAlignment(Qt::AlignLeft);
    ui->statusbar->addWidget(label1);
    // 第二，三个显示区域内容右对齐
    QLabel *label2 = new QLabel("第二个显示区",this);
    label2->setAlignment(Qt::AlignRight);
    ui->statusbar->addPermanentWidget(label2);
    QLabel *label3 = new QLabel("第三个显示区",this);
    label3->setAlignment(Qt::AlignRight);
    ui->statusbar->addPermanentWidget(label3);
}

void MainWindow::addTable()
{
    table = new QTableWidget(8, 5, this);
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            int randomValue = QRandomGenerator::global()->bounded(50); // 生成0到49的随机数
            table->setItem(i, j, new QTableWidgetItem(QString::number(randomValue)));
        }
    }

    sortButton = new QPushButton("排序");
    connect(sortButton, &QPushButton::clicked, table, [=](){
        static bool flag = false;
        if (flag)
        {
            table->sortItems(0, Qt::AscendingOrder);
            flag = false;
        }
        else
        {
            table->sortItems(0, Qt::DescendingOrder);
            flag = true;
        }
    });
}

void MainWindow::addTree()
{
    QStandardItemModel *model = new QStandardItemModel(8, 5, this);
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 5; col++){
            int randomValue = QRandomGenerator::global()->bounded(50); // 生成0到49的随机数
            QStandardItem *item = new QStandardItem(QString::number(randomValue));
            model->setItem(row, col, item);
        }
    }

    view = new QTableView(this);
    view->setModel(model);
    view->show();

    zeroButton = new QPushButton("将<=25的数置为0", this);
    connect(zeroButton, &QPushButton::clicked, this,[=](){
        // 获取模型中的数据
        for(int row = 0; row < 8; row++){
            for(int col = 0; col < 5; col++){
                QStandardItem *item = model->item(row, col);
                int value = item->text().toInt();
                if(value <= 25){
                    item->setText("0");
                }
            }
        }
    });
    filterButton = new QPushButton("过滤单数行号", this);
    connect(filterButton, &QPushButton::clicked, this,[=](){
        // 获取模型中的数据
        for(int row = 0; row < 4; row++){
            // 删除偶数行
            model->removeRow(row);
        }
    });   
}

void MainWindow::addWidget()
{
    myWidget = new MyWidget(this);
    myWidget->setFixedSize(record->width(), record->height());
}

void MainWindow::tcp_test()
{
    auto port = 8899;
    auto ip = QHostAddress("127.0.0.1");
    socket = new QTcpSocket(this);
    sendButton = new QPushButton("发送", this);
    record = new QTextEdit(this);

    QTimer *timer = new QTimer(this);
    connect(sendButton, &QPushButton::clicked, this, [=](){
        socket->connectToHost(ip, port);
        static int index = 0;
        connect(timer, &QTimer::timeout, this, [=](){
            QString str = QString("hello world %1").arg(index++);
            socket->write(str.toUtf8());
            record->append(str);
            if (index == 100)
            {
                timer->stop();
                socket->close();
            }
        });
        timer->start(500);
    });
}

void MainWindow::layoutWidget()
{
    QVBoxLayout *v1 = new QVBoxLayout;
    v1->addWidget(sortButton);
    v1->addWidget(zeroButton);
    v1->addWidget(filterButton);
    QWidget *w1 = new QWidget(this);
    w1->setLayout(v1);

    QVBoxLayout *v2 = new QVBoxLayout;
    v2->addWidget(table);
    v2->addWidget(w1);
    v2->addWidget(view);
    QWidget *w2 = new QWidget(this);
    w2->setLayout(v2);

    QVBoxLayout *v3 = new QVBoxLayout;
    v3->addWidget(record);
    v3->addWidget(sendButton);
    v3->addWidget(ui->subWidget);
    QWidget *w3 = new QWidget(this);
    w3->setLayout(v3);

    QHBoxLayout *all = new QHBoxLayout;
    all->addWidget(w2);
    all->addWidget(w3);

    ui->centralwidget->setLayout(all);
}
