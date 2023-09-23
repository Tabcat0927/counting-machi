#include "mainwindow.h"

modbus_t *ctx;
QMutex   mutexModbus;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<QVector<XVRegion>>("QVector<XVRegion>");
    //ui
    setWindowIcon(QIcon(":/icon/ico/ivision.ico"));
    CreateToolBar();
    stackedWidget  = new QStackedWidget();
    mainWidget = new MainWidget(this);
    setupWidget = new SetupWidget(mainWidget, this);
    logWidget = new XVLogWidget(QString(), this);
    stackedWidget->addWidget(mainWidget);
    stackedWidget->addWidget(setupWidget);
    stackedWidget->addWidget(logWidget);
    setCentralWidget(stackedWidget);
    showMaximized();

    loginDialog = new QDialog(this);
    LoginWidget();

    //func
    countProc = new CountingProcess(mainWidget, setupWidget);
    countProc->moveToThread(&countThread);
    connect(&countThread, &QThread::started, countProc, &CountingProcess::Count);
    connect(countProc, &CountingProcess::SignalShowImage, this, &MainWindow::SlotShowImage);
    connect(countProc, &CountingProcess::SignalStudy, this, &MainWindow::SlotStudy);
    connect(countProc, &CountingProcess::SignalCountChanged, this, &MainWindow::SlotCountChanged);

    QTimer *timer = new QTimer(this);
    ctx = nullptr;
    connect(timer, &QTimer::timeout, this, &MainWindow::CreateUndCheckModbus);
    timer->start(10000);
}

MainWindow::~MainWindow()
{
    countThread.quit();
    countThread.wait();
    if(countProc->isModbusConnect) modbus_free(ctx);
    delete countProc;

}

void MainWindow::CreateToolBar()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(toolBar);

    //用户登录
    userLogin = new QAction(QIcon(":/icon/ico/project/login.png"), "用户登录");
    userLogin->setCheckable(true);
    connect(userLogin, &QAction::toggled, this, &MainWindow::userLoginToggled);

    //前往设置
    setUp = new QAction(QIcon(":/icon/ico/project/set.png"), "前往设置");
    connect(setUp, &QAction::triggered, this, &MainWindow::setUpTriggerd);
    //setUp->setEnabled(false);

    //运行按钮
    runProg = new QAction(QIcon(":/icon/ico/project/start.png"), "运行按钮");
    runProg->setCheckable(true);
    connect(runProg, &QAction::toggled, this, &MainWindow::runProgToggled);

    //主页面
    mainWin = new QAction(QIcon(":/icon/ico/project/camera.png"), "主页面");
    connect(mainWin, &QAction::triggered, this, &MainWindow::minWinTriggerd);

    //日志界面
    logAction = new QAction(QIcon(":/icon/ico/log.png"), "日志界面");
    connect(logAction, &QAction::triggered, this, &MainWindow::logActionTriggered);

    //退出系统
    closeProg = new QAction(QIcon(":/icon/ico/exit.png"), "退出系统");
    connect(closeProg, &QAction::triggered, this, &MainWindow::close);

    QFont font("微软雅黑", 12, -1, false);
    runProg->setFont(font);
    userLogin->setFont(font);
    setUp->setFont(font);
    mainWin->setFont(font);
    logAction->setFont(font);
    closeProg->setFont(font);

    toolBar->addAction(runProg);
    toolBar->addAction(userLogin);
    toolBar->addAction(setUp);
    toolBar->addAction(mainWin);
    toolBar->addAction(logAction);
    toolBar->addAction(closeProg);
}

void MainWindow::userLoginToggled(bool toggle)
{
    if(toggle){
        userLogin->setIcon(QIcon(":/icon/ico/project/logout.png"));
        userLogin->setText("用户登出");
        loginDialog->exec();

    }
    else{
        userLogin->setIcon(QIcon(":/icon/ico/project/login.png"));
        userLogin->setText("用户登录");
    }

}

void MainWindow::setUpTriggerd()
{
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::runProgToggled(bool checked)
{
    if(checked){
        runProg->setIcon(QIcon(":/icon/ico/project/stop.png"));
        runProg->setText("停止运行");
        countProc->isCountStop = false;
        countThread.start(QThread::HighestPriority);
    }
    else{
        runProg->setIcon(QIcon(":/icon/ico/project/start.png"));
        runProg->setText("开始运行");
        countProc->isCountStop = true;
        countThread.quit();
        countThread.wait();
    }
}

void MainWindow::minWinTriggerd()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::logActionTriggered()
{
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::LoginWidget()
{
    QVBoxLayout *vlayout = new QVBoxLayout();
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    QHBoxLayout *hlayout3 = new QHBoxLayout();

    QLabel *userLabel = new QLabel("用户");
    QComboBox *userName = new QComboBox();
    userName->addItem("管理员");
    QLabel *pswdLabel = new QLabel("密码");
    QLineEdit *pswdVal = new QLineEdit();
    QPushButton *confirmBtn = new QPushButton("确定");
    QPushButton *cancelBtn = new QPushButton("取消");
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

void MainWindow::SlotShowImage(QImage img)
{
    VisionGraph *vg = mainWidget->vgShowImage;
    vg->clearPainter();
    vg->setBkImg(img);
    vg->setViewSize_Fit();

}

void MainWindow::SlotStudy(QVector<XVRegion> studyRegion)
{
    GrainDataLearnIn learnAreaInArea, learnAreaInRadius;
    GrainDataLearnOut learnAreaOut;
    XVRegion region;
    float radius;
    int area;

    for(int i = 0; i < studyRegion.count(); i++){
        region = studyRegion.at(i);
        area = GetXVRegionArea(region);
        radius = GetXVRegionRadius(region);
        double aadd = static_cast<double>(area);
        learnAreaInArea.data.push_back(aadd);
        learnAreaInRadius.data.push_back(radius);
    }

    grainDataLearn(learnAreaInArea, learnAreaOut);
    if(learnAreaOut.GrainDataLearnResult == 1){
        setupWidget->areaSetVal1->setValue((int)learnAreaOut.minThreshold);
        setupWidget->areaSetVal2->setValue((int)learnAreaOut.maxThreshold);
        Log::Instance()->writeInfo("学习算法结果面积最大值 = " + QString("%1").arg(learnAreaOut.maxThreshold));
        Log::Instance()->writeInfo("学习算法结果面积最小值 = " + QString("%1").arg(learnAreaOut.minThreshold));
    }
    else Log::Instance()->writeWarn("学习数据失败");

    grainDataLearn(learnAreaInRadius, learnAreaOut);
    if(learnAreaOut.GrainDataLearnResult == 1){
        setupWidget->radSetVal1->setValue((int)learnAreaOut.minThreshold);
        setupWidget->radSetVal1->setValue((int)learnAreaOut.maxThreshold);
        Log::Instance()->writeInfo("学习算法结果半径最大值 = " + QString("%1").arg(learnAreaOut.minThreshold));
        Log::Instance()->writeInfo("学习算法结果半径最小值 = " + QString("%1").arg(learnAreaOut.maxThreshold));
        Log::Instance()->writeInfo("***********学习成功***********");
    }
    else Log::Instance()->writeWarn("学习数据失败");
    studyRegion.clear();
    mainWidget->ctrlStudy->setChecked(false);
    countProc->beginStudy = false;
    countProc->isCountStop = true;
}

int MainWindow::GetXVRegionArea(XVRegion &region)
{
    XVRegionAreaIn area_in;
    XVRegionAreaOut area_out;
    area_in.inRegion = region;
    XVRegionArea(area_in, area_out);

    return area_out.outArea;
}

float MainWindow::GetXVRegionRadius(XVRegion &region)
{
    XVRegionBoundingCircleIn circle_in;
    XVRegionBoundingCircleOut circle_out;
    circle_in.inRegion = region;
    XVRegionBoundingCircle(circle_in, circle_out);

    return circle_out.outCircle.radius;
}

void MainWindow::Write2SysSettingFile(const QString &filename)
{
    QSettings setting(filename, QSettings::IniFormat);
    setting.setValue("curRecipe", mainWidget->curRecipeVal->text());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    countProc->isCountStop = true;
    Write2SysSettingFile("config/system/sys");
    event->accept();
}

void MainWindow::SlotCountChanged(int val1, int val2, int val3, int val4)
{
    mainWidget->curQtyFrame->setValue(val1);
    mainWidget->cntSpdFrame->setValue(val2);
    mainWidget->fillSpdFrame->setValue(val3);
    mainWidget->fillQtyFrame->setValue(val4);
    mainWidget->progBar->setValue(val1 * 100 / mainWidget->aBtlQtyFrame->value());
}

void MainWindow::CreateUndCheckModbus()
{
    uint16_t hd110;

    if(ctx == nullptr)
        ctx = modbus_new_tcp(setupWidget->plcIpVal->text().toLatin1().data(), 502);
    if(!countProc->isModbusConnect && modbus_connect(ctx) == -1){
        Log::Instance()->writeWarn("PLC连接失败");
        modbus_free(ctx);
        ctx = nullptr;
        return;
    }
    countProc->isModbusConnect = true;
    QMutexLocker locker(&mutexModbus);
    if(modbus_read_registers(ctx, 41198, 1, &hd110) == -1){
        countProc->isModbusConnect = false;
        Log::Instance()->writeWarn("PLC失去连接");
    }
}
