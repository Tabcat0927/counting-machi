#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    _fontYahei15 = QFont("微软雅黑", 15);
    isStudy = false;

    vgShowImage = new VisionGraph();
    vgShowImage->setBkImg(QImage(":/icon/ico/JianfengLogo.png"));
    vgShowImage->setGraphType(GraphType::graph_Info,item_NO);

    CreateUi();
    SetStyleSheet();
    ReadSysSettingFile("config/system/sys");

    connect(ctrlStudy, &QPushButton::toggled, this, &MainWidget::CtrlStudyToggled);
}

void MainWidget::CreateUi()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    _displayWidget = new QWidget();
    _statusWidget = new QGroupBox();
    _controlWidget = new QGroupBox();

    DisplayImages();
    RunStatusWidget();
    RunControlWidget();

    curRecipe = new QLabel("当前配方：");
    curRecipeVal = new QLabel();
    curRecipe->setFont(_fontYahei15);
    curRecipeVal->setFont(_fontYahei15);
    testMode = new QComboBox();
    QStringList mode;
    mode << "Normal" << "Test";
    testMode->addItems(mode);
    testMode->setCurrentIndex(1);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(curRecipe);
    hlayout->addWidget(curRecipeVal, 1);
    hlayout->addWidget(testMode);

    QVBoxLayout *rightLayout = new QVBoxLayout();

    rightLayout->addLayout(hlayout);
    rightLayout->addWidget(_statusWidget, 1);
    rightLayout->addWidget(_controlWidget, 1);

    mainLayout->addWidget(_displayWidget, 1);
    mainLayout->addLayout(rightLayout, 1);

    setLayout(mainLayout);
}

void MainWidget::DisplayImages()
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    companyName = new QLabel("南通剑烽机械有限公司");
    companyName->setFont(QFont("微软雅黑", 20));

    vLayout->addWidget(companyName, 0, Qt::AlignCenter);
    vLayout->addWidget(vgShowImage, 1);

    _displayWidget->setLayout(vLayout);
}

void MainWidget::RunStatusWidget()
{
    //当前数量current quantity
    curQtyText = new QLabel("当前数量");
    curQtyText->setFont(_fontYahei15);
    curQtyFrame = new DigitUnitFrame("粒", false, 0, 10000);
    curQtyFrame->setFont(_fontYahei15);
    curQtyFrame->setHeight(45);

    //单瓶数量single bottle quantity
    aBtlQtyText = new QLabel("单瓶数量");
    aBtlQtyText->setFont(_fontYahei15);
    aBtlQtyFrame = new DigitUnitFrame("粒/瓶", true, 0, 10000);
    aBtlQtyFrame->setFont(_fontYahei15);
    aBtlQtyFrame->setHeight(45);

    //计数速度
    cntSpdText = new QLabel("计数速度");
    cntSpdText->setFont(_fontYahei15);
    cntSpdFrame = new DigitUnitFrame("粒/秒", false, 0, 10000);
    cntSpdFrame->setFont(_fontYahei15);
    cntSpdFrame->setHeight(45);

    //装瓶速度
    fillSpdText = new QLabel("装瓶速度");
    fillSpdText->setFont(_fontYahei15);
    fillSpdFrame = new DigitUnitFrame("瓶/分", false, 0, 10000);
    fillSpdFrame->setFont(_fontYahei15);
    fillSpdFrame->setHeight(45);

    //已装瓶数量
    fillQtyText = new QLabel("已装瓶数量");
    fillQtyText->setFont(_fontYahei15);
    fillQtyFrame = new DigitUnitFrame("瓶", false, 0, 10000);
    fillQtyFrame->setFont(_fontYahei15);
    fillQtyFrame->setHeight(45);

    //进度条
    progBar = new QProgressBar();
    progBar->setMinimumHeight(45);

    //清零1
    clrBtn1 = new QPushButton("清零");

    //有瓶信号
    QFrame *haveBtlFrame = new QFrame();
    haveBtlFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QVBoxLayout *haveBtlLayout = new QVBoxLayout();
    haveBtlText = new QLabel("有瓶信号");
    haveBtlText->setFont(_fontYahei15);
    haveBtlLayout->addWidget(haveBtlText);
    haveBtlFrame->setLayout(haveBtlLayout);


    //过量警告excess warn
    QFrame *exsWarnFrame = new QFrame();
    exsWarnFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QVBoxLayout *exsWarnLayout = new QVBoxLayout();
    exsWarnText = new QLabel("过量警告");
    exsWarnText->setFont(_fontYahei15);
    exsWarnLayout->addWidget(exsWarnText);
    exsWarnFrame->setLayout(exsWarnLayout);

    //清零2
    clrBtn2 = new QPushButton("清零");

    QGridLayout *runStatLayout = new QGridLayout();
    runStatLayout->setColumnStretch(0, 1);
    runStatLayout->setColumnStretch(1, 1);

    runStatLayout->addWidget(curQtyText, 0, 0);
    runStatLayout->addWidget(curQtyFrame, 0, 1);
    runStatLayout->addWidget(clrBtn1, 0, 2);
    runStatLayout->addWidget(aBtlQtyText, 1, 0);
    runStatLayout->addWidget(aBtlQtyFrame, 1, 1);
    runStatLayout->addWidget(haveBtlFrame, 1, 2, 2, 1);
    runStatLayout->addWidget(progBar, 2, 0, 1, 2);
    runStatLayout->addWidget(cntSpdText, 3, 0);
    runStatLayout->addWidget(cntSpdFrame, 3, 1);
    runStatLayout->addWidget(exsWarnFrame, 3, 2, 2, 1);
    runStatLayout->addWidget(fillSpdText, 4, 0);
    runStatLayout->addWidget(fillSpdFrame, 4, 1);
    runStatLayout->addWidget(fillQtyText, 5, 0);
    runStatLayout->addWidget(fillQtyFrame, 5, 1);
    runStatLayout->addWidget(clrBtn2, 5, 2);

    _statusWidget->setLayout(runStatLayout);
}

void MainWidget::RunControlWidget()
{
    //振动盘，启动，停止，学习数据，传送带，保存图片，清瓶
    shaker1Inc = new QPushButton("1级振动盘++");
    shaker1Dec = new QPushButton("1级振动盘--");
    shaker2Inc = new QPushButton("2级振动盘++");
    shaker2Dec = new QPushButton("2级振动盘--");
    shaker3Inc = new QPushButton("3级振动盘++");
    shaker3Dec = new QPushButton("3级振动盘--");
    ctrlStart = new QPushButton("启动");
    ctrlStop = new QPushButton("停止");
    ctrlClr = new QPushButton("清瓶");
    ctrlStudy = new QPushButton("学习数据");
    ctrlStudy->setCheckable(true);
    ctrlSave = new QPushButton("保存图片");
    ctrlBelt = new QPushButton("传送带");

    shaker1Val = new DigitUnitFrame("V", true, 0, 10000);
    shaker1Val->setFixedHeight(40);
    shaker1Val->setFont(_fontYahei15);
    shaker2Val = new DigitUnitFrame("V", true, 0, 10000);
    shaker2Val->setFixedHeight(40);
    shaker2Val->setFont(_fontYahei15);
    shaker3Val = new DigitUnitFrame("V", true, 0, 10000);
    shaker3Val->setFixedHeight(40);
    shaker3Val->setFont(_fontYahei15);


    QGridLayout *ctrlLayout = new QGridLayout();
    ctrlLayout->addWidget(shaker1Inc, 0, 0);
    ctrlLayout->addWidget(shaker1Dec, 2, 0);
    ctrlLayout->addWidget(shaker2Inc, 0, 2);
    ctrlLayout->addWidget(shaker2Dec, 2, 2);
    ctrlLayout->addWidget(shaker3Inc, 0, 4);
    ctrlLayout->addWidget(shaker3Dec, 2, 4);
    ctrlLayout->addWidget(shaker1Val, 1, 0);
    ctrlLayout->addWidget(shaker2Val, 1, 2);
    ctrlLayout->addWidget(shaker3Val, 1, 4);
    ctrlLayout->addWidget(ctrlStart, 4, 0);
    ctrlLayout->addWidget(ctrlStop, 4, 2);
    ctrlLayout->addWidget(ctrlClr, 4, 4);
    ctrlLayout->addWidget(ctrlStudy, 6, 0);
    ctrlLayout->addWidget(ctrlSave, 6, 2);
    ctrlLayout->addWidget(ctrlBelt, 6, 4);
    ctrlLayout->setColumnStretch(0, 3);
    ctrlLayout->setColumnStretch(1, 2);
    ctrlLayout->setColumnStretch(2, 3);
    ctrlLayout->setColumnStretch(3, 2);
    ctrlLayout->setColumnStretch(4, 3);
    ctrlLayout->setRowStretch(0, 2);
    ctrlLayout->setRowStretch(1, 2);
    ctrlLayout->setRowStretch(2, 2);
    ctrlLayout->setRowStretch(3, 1);
    ctrlLayout->setRowStretch(4, 4);
    ctrlLayout->setRowStretch(5, 1);
    ctrlLayout->setRowStretch(6, 2);

    _controlWidget->setLayout(ctrlLayout);

}

void MainWidget::SetStyleSheet()
{
    _shakerQSS = "QPushButton{min-width: 150px; \
                 min-height: 40px; \
                 background: rgb(85, 0, 255); \
                 border-radius: 4px; \
                 font: 14pt '微软雅黑'; \
                 color:rgb(255, 255, 255);} \
                 QPushButton:pressed{ \
                 background-color: rgb(85, 85, 255);}";

    clrBtn1->setStyleSheet("QPushButton{ \
                       min-width: 100px; \
                       min-height: 45px; \
                       background: rgb(85, 0, 255); \
                       border-radius: 4px; \
                       font: 14pt '微软雅黑'; \
                       color:rgb(255, 255, 255);} \
                       QPushButton:pressed{ \
                       background-color: rgb(85, 85, 255);}");

    clrBtn2->setStyleSheet("QPushButton{ \
                           min-width: 100px; \
                           min-height: 45px; \
                           background: rgb(85, 0, 255); \
                           border-radius: 4px; \
                           font: 14pt '微软雅黑'; \
                           color:rgb(255, 255, 255);} \
                           QPushButton:pressed{ \
                           background-color: rgb(85, 85, 255);}");
    shaker1Inc->setStyleSheet(_shakerQSS);
    shaker1Dec->setStyleSheet(_shakerQSS);
    shaker2Dec->setStyleSheet(_shakerQSS);
    shaker2Inc->setStyleSheet(_shakerQSS);
    shaker3Inc->setStyleSheet(_shakerQSS);
    shaker3Dec->setStyleSheet(_shakerQSS);
    ctrlStart->setStyleSheet("QPushButton{"
                            "min-width: 150px;"
                            "min-height: 80px;"
                            "background: rgb(85, 255, 0);"
                            "border-radius: 4px;"
                            "font: 14pt '微软雅黑';}"
                            "QPushButton:pressed{ \
                            background-color: rgb(218, 165, 32);}");
    ctrlStop->setStyleSheet("QPushButton{min-width: 150px; \
                            min-height: 80px; \
                            background:rgb(255, 0, 0); \
                            border-radius: 4px; \
                            font: 14pt '微软雅黑';} \
                            QPushButton:pressed{ \
                            background-color: rgb(255, 165, 0);}");
    ctrlClr->setStyleSheet("min-width: 150px; \
                            min-height: 80px; \
                            background: rgb(255, 255, 0); \
                            border-radius: 4px; \
                            font: 14pt '微软雅黑'; \
                            color:rgb(50, 50, 50);}"
                            "QPushButton:pressed{ \
                            background-color: rgb(218, 165, 32);}");
    ctrlStudy->setStyleSheet("QPushButton{min-width: 150px; \
                              min-height: 80px; \
                              background: rgb(85, 0, 255); \
                              border-radius: 4px; \
                              font: 14pt '微软雅黑'; \
                              color:rgb(255, 255, 255);} \
                              QPushButton:pressed{ \
                              background-color: rgb(85, 85, 255);}");
    ctrlSave->setStyleSheet("QPushButton{min-width: 150px; \
                             min-height: 80px; \
                             background: rgb(85, 0, 255); \
                             border-radius: 4px; \
                             font: 14pt '微软雅黑'; \
                             color:rgb(255, 255, 255);} \
                             QPushButton:pressed{ \
                             background-color: rgb(85, 85, 255);}");
    ctrlBelt->setStyleSheet("QPushButton{min-width: 150px; \
                             min-height: 80px; \
                             background: rgb(85, 0, 255); \
                             border-radius: 4px; \
                             font: 14pt '微软雅黑'; \
                             color:rgb(255, 255, 255);} \
                             QPushButton:pressed{ \
                             background-color: rgb(85, 85, 255);}");
}

void MainWidget::CtrlStudyToggled(bool checked)
{
    isStudy = checked;
}

void MainWidget::ReadSysSettingFile(const QString& filename)
{
    QSettings setting(filename, QSettings::IniFormat);
    setting.setFallbacksEnabled(false);
    curRecipeVal->setText(setting.value("curRecipe").toString());
}



