#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/icon/ico/ivision.ico"));
    CreateToolBar();

    loginDialog = new QDialog(this);
    LoginWidget();

    stackedWidget  = new QStackedWidget();
    mainWidget = new MainWidget();
    stackedWidget->addWidget(mainWidget);
    setupWidget = new SetupWidget();
    stackedWidget->addWidget(setupWidget);
    setCentralWidget(stackedWidget);

    showMaximized();

}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateToolBar()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(toolBar);

    //用户登录
    userLogin = new QAction(QIcon(":/icon/ico/project/login.png"), QStringLiteral("用户登录"));
    userLogin->setCheckable(true);
    connect(userLogin, &QAction::toggled, this, &MainWindow::userLoginToggled);

    //设置按钮
    setUp = new QAction(QIcon(":/icon/ico/project/set.png"), QStringLiteral("前往设置"));
    connect(setUp, &QAction::triggered, this, &MainWindow::setUpTriggerd);
    //setUp->setEnabled(false);

    //运行按钮
    runProg = new QAction(QIcon(":/icon/ico/project/start.png"), QStringLiteral("开始运行"));
    runProg->setCheckable(true);
    connect(runProg, &QAction::toggled, this, &MainWindow::runProgToggled);

    //主页面
    minWin = new QAction(QIcon(":/icon/ico/project/camera.png"), QStringLiteral("主页面"));
    connect(minWin, &QAction::triggered, this, &MainWindow::minWinTriggerd);

    //退出系统
    closeProg = new QAction(QIcon(":/icon/ico/exit.png"), QStringLiteral("退出系统"));
    connect(closeProg, &QAction::triggered, this, &MainWindow::close);

    QFont font(QStringLiteral("微软雅黑"), 12, -1, false);
    runProg->setFont(font);
    userLogin->setFont(font);
    setUp->setFont(font);
    minWin->setFont(font);
    closeProg->setFont(font);

    toolBar->addAction(runProg);
    toolBar->addAction(userLogin);
    toolBar->addAction(setUp);
    toolBar->addAction(minWin);
    toolBar->addAction(closeProg);
}

void MainWindow::userLoginToggled(bool toggle)
{
    if(toggle){
        userLogin->setIcon(QIcon(":/icon/ico/project/logout.png"));
        userLogin->setText(QStringLiteral("用户登出"));
        loginDialog->exec();

    }
    else{
        userLogin->setIcon(QIcon(":/icon/ico/project/login.png"));
        userLogin->setText(QStringLiteral("用户登录"));
    }

}

void MainWindow::setUpTriggerd()
{
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::runProgToggled(bool toggle)
{
    if(toggle){
        runProg->setIcon(QIcon(":/icon/ico/project/stop.png"));
        runProg->setText(QStringLiteral("停止运行"));
    }
    else{
        runProg->setIcon(QIcon(":/icon/ico/project/start.png"));
        runProg->setText(QStringLiteral("开始运行"));
    }
}

void MainWindow::minWinTriggerd()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::LoginWidget()
{
    QVBoxLayout *vlayout = new QVBoxLayout();
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    QHBoxLayout *hlayout3 = new QHBoxLayout();

    QLabel *userLabel = new QLabel(QStringLiteral("用户"));
    QComboBox *userName = new QComboBox();
    userName->addItem(QStringLiteral("管理员"));
    QLabel *pswdLabel = new QLabel(QStringLiteral("密码"));
    QLineEdit *pswdVal = new QLineEdit();
    QPushButton *confirmBtn = new QPushButton(QStringLiteral("确定"));
    QPushButton *cancelBtn = new QPushButton(QStringLiteral("取消"));
    hlayout1->addWidget(userLabel);
    hlayout1->addWidget(userName);
    hlayout2->addWidget(pswdLabel);
    hlayout2->addWidget(pswdVal);
    hlayout3->addWidget(confirmBtn);
    hlayout3->addWidget(cancelBtn);

    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);

    loginDialog->setLayout(vlayout);
    loginDialog->resize(300, 200);
}
