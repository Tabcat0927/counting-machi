#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    _fontYahei15 = QFont(QStringLiteral("微软雅黑"), 15);
    _shakerQSS = "min-width: 150px; \
                min-height: 40px; \
                background: rgb(85, 0, 255); \
                border-radius: 4px; \
                font: 14pt '微软雅黑'; \
                color:rgb(255, 255, 255);";
    vgShowImage = new VisionGraph();
    vgShowImage->setBkImg(QImage(":/icon/ico/JianfengLogo.png"));

    CreateUi();
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

    QVBoxLayout *rightLayout = new QVBoxLayout();
    QLabel *curRecipe = new QLabel(QStringLiteral("当前配方："));
    curRecipe->setFont(_fontYahei15);
    rightLayout->addWidget(curRecipe);
    rightLayout->addWidget(_statusWidget, 1);
    rightLayout->addWidget(_controlWidget, 1);

    mainLayout->addWidget(_displayWidget, 1);
    mainLayout->addLayout(rightLayout, 1);

    setLayout(mainLayout);
}

void MainWidget::DisplayImages()
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    companyName = new QLabel(QStringLiteral("南通剑烽机械有限公司"));
    companyName->setFont(QFont(QStringLiteral("微软雅黑"), 20));

    vLayout->addWidget(companyName, 0, Qt::AlignCenter);
    vLayout->addWidget(vgShowImage, 1);

    _displayWidget->setLayout(vLayout);
}

void MainWidget::RunStatusWidget()
{
    //当前数量current quantity
    curQtyText = new QLabel(QStringLiteral("当前数量"));
    curQtyText->setFont(_fontYahei15);
    curQtyVal = new QLabel();
    curQtyUnit = new QLabel(QStringLiteral("粒"));
    curQtyUnit->setFont(_fontYahei15);
    QFrame *curQtyFrame = new QFrame();
    curQtyFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QHBoxLayout *curQtyLayout = new QHBoxLayout();
    curQtyLayout->addWidget(curQtyVal);
    curQtyLayout->addWidget(curQtyUnit);
    curQtyLayout->setStretch(0, 1);
    curQtyFrame->setLayout(curQtyLayout);

    //单瓶数量single bottle quantity
    aBtlQtyText = new QLabel(QStringLiteral("单瓶数量"));
    aBtlQtyText->setFont(_fontYahei15);
    aBtlQtyVal = new QLabel();
    aBtlQtyUnit = new QLabel(QStringLiteral("粒/瓶"));
    aBtlQtyUnit->setFont(_fontYahei15);
    QFrame *aBtlQtyFrame = new QFrame();
    aBtlQtyFrame->setFixedHeight(50);
    aBtlQtyFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QHBoxLayout *aBtlQtyLayout = new QHBoxLayout();
    aBtlQtyLayout->addWidget(aBtlQtyVal);
    aBtlQtyLayout->addWidget(aBtlQtyUnit);
    aBtlQtyLayout->setStretch(0, 1);
    aBtlQtyFrame->setLayout(aBtlQtyLayout);

    //计数速度
    cntSpdText = new QLabel(QStringLiteral("计数速度"));
    cntSpdText->setFont(_fontYahei15);
    cntSpdVal = new QLabel();
    cntSpdUnit = new QLabel(QStringLiteral("粒/秒"));
    cntSpdUnit->setFont(_fontYahei15);
    QFrame *cntSpdFrame = new QFrame();
    cntSpdFrame->setFixedHeight(50);
    cntSpdFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QHBoxLayout *cntSpdLayout = new QHBoxLayout();
    cntSpdLayout->addWidget(cntSpdVal);
    cntSpdLayout->addWidget(cntSpdUnit);
    cntSpdLayout->setStretch(0, 1);
    cntSpdFrame->setLayout(cntSpdLayout);

    //装瓶速度
    fillSpdText = new QLabel(QStringLiteral("装瓶速度"));
    fillSpdText->setFont(_fontYahei15);
    fillSpdVal = new QLabel();
    fillSpdUnit = new QLabel(QStringLiteral("瓶/分"));
    fillSpdUnit->setFont(_fontYahei15);
    QFrame *fillSpdFrame = new QFrame();
    fillSpdFrame->setFixedHeight(50);
    fillSpdFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QHBoxLayout *fillSpdLayout = new QHBoxLayout();
    fillSpdLayout->addWidget(fillSpdVal);
    fillSpdLayout->addWidget(fillSpdUnit);
    fillSpdLayout->setStretch(0, 1);
    fillSpdFrame->setLayout(fillSpdLayout);

    //已装瓶数量
    fillQtyText = new QLabel(QStringLiteral("已装瓶数量"));
    fillQtyText->setFont(_fontYahei15);
    fillQtyVal = new QLabel();
    fillQtyUnit = new QLabel(QStringLiteral("瓶"));
    fillQtyUnit->setFont(_fontYahei15);
    QFrame *fillQtyFrame = new QFrame();
    fillQtyFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QHBoxLayout *fillQtyLayout = new QHBoxLayout();
    fillQtyLayout->addWidget(fillQtyVal);
    fillQtyLayout->addWidget(fillQtyUnit);
    fillQtyLayout->setStretch(0, 1);
    fillQtyFrame->setLayout(fillQtyLayout);

    //进度条
    QProgressBar *progBar = new QProgressBar();
    progBar->setFixedHeight(50);

    //清零1
    clrBtn1 = new QPushButton(QStringLiteral("清零"));
    clrBtn1->setStyleSheet("min-width: 100px; \
                            min-height: 50px; \
                            background: rgb(85, 0, 255); \
                            border-radius: 4px; \
                            font: 14pt '微软雅黑'; \
                            color:rgb(255, 255, 255);");

    //有瓶信号
    QFrame *haveBtlFrame = new QFrame();
    haveBtlFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QVBoxLayout *haveBtlLayout = new QVBoxLayout();
    haveBtlText = new QLabel(QStringLiteral("有瓶信号"));
    haveBtlText->setFont(_fontYahei15);
    haveBtlLayout->addWidget(haveBtlText);
    haveBtlFrame->setLayout(haveBtlLayout);


    //过量警告excess warn
    QFrame *exsWarnFrame = new QFrame();
    exsWarnFrame->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    QVBoxLayout *exsWarnLayout = new QVBoxLayout();
    exsWarnText = new QLabel(QStringLiteral("过量警告"));
    exsWarnText->setFont(_fontYahei15);
    exsWarnLayout->addWidget(exsWarnText);
    exsWarnFrame->setLayout(exsWarnLayout);

    //清零2
    QPushButton *clrBtn2 = new QPushButton(QStringLiteral("清零"));
    clrBtn2->setStyleSheet("min-width: 100px; \
                            min-height: 50px; \
                            background: rgb(85, 0, 255); \
                            border-radius: 4px; \
                            font: 14pt '微软雅黑'; \
                            color:rgb(255, 255, 255);");

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
    shaker1Inc = new QPushButton(QStringLiteral("1级振动盘++"));
    shaker1Inc->setStyleSheet(_shakerQSS);
    shaker1Dec = new QPushButton(QStringLiteral("1级振动盘--"));
    shaker1Dec->setStyleSheet(_shakerQSS);
    shaker2Inc = new QPushButton(QStringLiteral("2级振动盘++"));
    shaker2Inc->setStyleSheet(_shakerQSS);
    shaker2Dec = new QPushButton(QStringLiteral("2级振动盘--"));
    shaker2Dec->setStyleSheet(_shakerQSS);
    shaker3Inc = new QPushButton(QStringLiteral("3级振动盘++"));
    shaker3Inc->setStyleSheet(_shakerQSS);
    shaker3Dec = new QPushButton(QStringLiteral("3级振动盘--"));
    shaker3Dec->setStyleSheet(_shakerQSS);
    ctrlStart = new QPushButton(QStringLiteral("启动"));
    ctrlStart->setStyleSheet("QPushButton#ctrlStart { "
                             "min-width: 150px;"
                             "min-height: 80px;"
                             "background: rgb(85, 255, 0);"
                             "border-radius: 4px;"
                             "font: 14pt '微软雅黑';}");
    ctrlStop = new QPushButton(QStringLiteral("停止"));
    ctrlStop->setStyleSheet("min-width: 150px; \
                             min-height: 80px; \
                             background:rgb(255, 0, 0); \
                             border-radius: 4px; \
                             font: 14pt '微软雅黑';");
    ctrlClr = new QPushButton(QStringLiteral("清瓶"));
    ctrlClr->setStyleSheet("min-width: 150px; \
                            min-height: 80px; \
                            background: rgb(255, 255, 0); \
                            border-radius: 4px; \
                            font: 14pt '微软雅黑'; \
                            color:rgb(50, 50, 50);}");
    ctrlStudy = new QPushButton(QStringLiteral("学习数据"));
    ctrlStudy->setStyleSheet("min-width: 150px; \
                              min-height: 80px; \
                              background: rgb(85, 0, 255); \
                              border-radius: 4px; \
                              font: 14pt '微软雅黑'; \
                              color:rgb(255, 255, 255);");
    ctrlSave = new QPushButton(QStringLiteral("保存图片"));
    ctrlSave->setStyleSheet("min-width: 150px; \
                             min-height: 80px; \
                             background: rgb(85, 0, 255); \
                             border-radius: 4px; \
                             font: 14pt '微软雅黑'; \
                             color:rgb(255, 255, 255);");
    ctrlBelt = new QPushButton(QStringLiteral("传送带"));
    ctrlBelt->setStyleSheet("min-width: 150px; \
                             min-height: 80px; \
                             background: rgb(85, 0, 255); \
                             border-radius: 4px; \
                             font: 14pt '微软雅黑'; \
                             color:rgb(255, 255, 255);");
    shaker1Val = new QLabel();
    shaker1Val->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    shaker1Val->setFixedHeight(40);
    shaker2Val = new QLabel();
    shaker2Val->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);
    shaker3Val = new QLabel();
    shaker3Val->setFrameStyle(QFrame::Plain | QFrame::StyledPanel);

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
