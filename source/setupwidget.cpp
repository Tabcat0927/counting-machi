#include "setupwidget.h"

void promptMessage(const QString&);

SetupWidget::SetupWidget(MainWidget *mw, QWidget *parent) :
             QWidget(parent), mw(mw)
{
    _fontYahei15 = QFont("微软雅黑", 15);
    _recipeBtnQSS = "QPushButton{"
                    "min-width: 256px;"
                    "min-height: 40px;"
                    "background: #adb5bd;"
                    "font: 12pt '微软雅黑';"
                    "border-radius: 4px;}"
                    "QPushButton:pressed{"
                    "background-color: rgb(220, 220, 220);}";
    CreateUi();
    LoadRecipeName();
    LoadRecipeParameter();
    connect(btnNew, &QPushButton::clicked, this, &SetupWidget::SlotRecipeNew);
    connect(btnLoad, &QPushButton::clicked, this, &SetupWidget::SlotRecipeLoad);
    connect(btnSave, &QPushButton::clicked, this, &SetupWidget::SlotRecipeSave);
    connect(btnDelete, &QPushButton::clicked, this, &SetupWidget::SlotRecipeDel);
    connect(recipeList, &QListWidget::currentTextChanged, this, &SetupWidget::SlotSelectRecipe);


}

void SetupWidget::CreateUi()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    RecipeWidget();

    QTabWidget *setWidget = new QTabWidget();
    setWidget->setFont(QFont("微软雅黑", 15));
    IdentifyParaWidget();
    CameraParaWidget();
    MachineCtrlWidget();
    ElectricParaWidget();
    OtherParaWidget();
    setWidget->addTab(_identifyParaWidget, "识别参数");
    setWidget->addTab(_cameraParaWidget, "相机参数");
    setWidget->addTab(_machineCtrlWidget, "手动控制");
    setWidget->addTab(_electricParaWidget, "电气参数");
    setWidget->addTab(_otherParaWidget, "其他参数");

    mainLayout->addWidget(_recipeWidget, 1);
    mainLayout->addWidget(setWidget, 3);

}

void SetupWidget::RecipeWidget()
{
    _recipeWidget = new QWidget();
    QVBoxLayout *recipeLayout = new QVBoxLayout();

    recipeList = new QListWidget();
    recipeList->setAlternatingRowColors(true);
    recipeList->setSelectionBehavior(QAbstractItemView::SelectRows);
    recipeList->setStyleSheet("QListWidget{"
                              "background-color: rgb(220, 220, 220);"
                              "font: 14pt '微软雅黑';}"
                              "QListWidget::item{"
                              "height: 32px;}");

    recipeName = new QLabel("配方名称:");
    recipeName->setFont(QFont("微软雅黑", 12));
    newRecipe = new QLineEdit();
    newRecipe->setAlignment(Qt::AlignHCenter);
    newRecipe->setStyleSheet("border: 1px solid #1c7ed6; \
                              min-height: 40px; \
                              border-radius: 4px; \
                              background: white; \
                              font: 12pt '微软雅黑';");
    btnLoad = new QPushButton(QIcon(":/icon/ico/project/saveas.png"), "加载");
    btnLoad->setStyleSheet(_recipeBtnQSS);
    btnNew = new QPushButton(QIcon(":/icon/ico/project/new.png"), "新建");
    btnNew->setStyleSheet(_recipeBtnQSS);
    btnSave = new QPushButton(QIcon(":/icon/ico/project/save.png"), "保存");
    btnSave->setStyleSheet(_recipeBtnQSS);
    btnDelete = new QPushButton(QIcon(":/icon/ico/cancel1.png"), "删除");
    btnDelete->setStyleSheet(_recipeBtnQSS);

    recipeLayout->addWidget(recipeList);
    recipeLayout->addWidget(recipeName);
    recipeLayout->addWidget(newRecipe);
    recipeLayout->addWidget(btnLoad);
    recipeLayout->addWidget(btnNew);
    recipeLayout->addWidget(btnSave);
    recipeLayout->addWidget(btnDelete);

    _recipeWidget->setLayout(recipeLayout);
}

void SetupWidget::IdentifyParaWidget()
{
    _identifyParaWidget = new QWidget();

    QGridLayout *identifyLayout = new QGridLayout();
    identifyLayout->setColumnStretch(0, 1);
    identifyLayout->setColumnStretch(1, 1);
    identifyLayout->setColumnStretch(2, 1);
    identifyLayout->setColumnStretch(3, 1);
    thresholdLabel = new QLabel(QString::fromUtf8("阈值设置"));
    thresholdLabel->setFixedHeight(35);
    thresholdVal1 = new DigitUnitFrame(QString(), true, 0, 10000);
    thresholdVal1->setFont(_fontYahei15);
    signTo = new QLabel("<->");
    thresholdVal2 = new DigitUnitFrame(QString(), true, 0, 10000);
    thresholdVal2->setFont(_fontYahei15);


    preprocLabel = new QLabel("预处理方法");
    preprocLabel->setFixedHeight(35);
    preprocType = new QComboBox();
    preprocType->addItem("开运算_方");
    preprocType->addItem("闭运算_方");
    operatorSize = new QLabel("算子尺寸");
    operatorSizeVal = new DigitUnitFrame(QString(), true, 0, 10000);
    operatorSizeVal->setFont(_fontYahei15);

    areaSetLabel = new QLabel("面积设置");
    areaSetLabel->setFixedHeight(35);
    areaSetVal1 = new DigitUnitFrame("Pixel", true, 0, 10000);
    areaSetVal1->setFont(_fontYahei15);
    signTo1 = new QLabel("<->");
    areaSetVal2 = new DigitUnitFrame("Pixel", true, 0, 10000);
    areaSetVal2->setFont(_fontYahei15);

    radSetLabel = new QLabel("半径设置");
    radSetLabel->setFixedHeight(35);
    radSetVal1 = new DigitUnitFrame("Pixel", true, 0, 10000);
    radSetVal1->setFont(_fontYahei15);
    signTo2 = new QLabel("<->");
    radSetVal2 = new DigitUnitFrame("Pixel", true, 0, 10000);
    radSetVal2->setFont(_fontYahei15);

    fillSetLabel = new QLabel("填充度设置");
    fillSetLabel->setFixedHeight(35);
    fillSetVal1 = new DigitUnitFrame(QString(), true, 0, 10000);
    fillSetVal1->setFont(_fontYahei15);
    signTo3 = new QLabel("<->");
    fillSetVal2 = new DigitUnitFrame(QString(), true, 0, 10000);
    fillSetVal2->setFont(_fontYahei15);

    flawAreaSetLabel = new QLabel("残料面积");
    flawAreaSetLabel->setFixedHeight(35);
    flawAreaSetVal1 = new DigitUnitFrame("Pixel", true, 0, 10000);
    flawAreaSetVal1->setFont(_fontYahei15);
    signTo4 = new QLabel("<->");
    flawAreaSetVal2 = new DigitUnitFrame("Pixel", true, 0, 10000);
    flawAreaSetVal2->setFont(_fontYahei15);

    flawRadSetLabel = new QLabel("残料半径");
    flawRadSetLabel->setFixedHeight(35);
    flawRadSetVal1 = new DigitUnitFrame("Pixel", true, 0, 10000);
    flawRadSetVal1->setFont(_fontYahei15);
    signTo5 = new QLabel("<->");
    flawRadSetVal2 = new DigitUnitFrame("Pixel", true, 0, 10000);
    flawRadSetVal2->setFont(_fontYahei15);

    remnentAlertLabel = new QLabel("余料警戒");
    remnentAlertLabel->setFixedHeight(35);
    remnentAlertVal = new DigitUnitFrame("粒", true, 0, 10000);
    remnentAlertVal->setFont(_fontYahei15);

    identifyLayout->addWidget(thresholdLabel, 0, 0);
    identifyLayout->addWidget(thresholdVal1, 0, 1);
    identifyLayout->addWidget(signTo, 0, 2, Qt::AlignHCenter);
    identifyLayout->addWidget(thresholdVal2, 0, 3);
    identifyLayout->addWidget(preprocLabel, 1, 0);
    identifyLayout->addWidget(preprocType, 1, 1);
    identifyLayout->addWidget(operatorSize, 1, 2, Qt::AlignHCenter );
    identifyLayout->addWidget(operatorSizeVal, 1, 3);
    identifyLayout->addWidget(areaSetLabel, 2, 0);
    identifyLayout->addWidget(areaSetVal1, 2, 1);
    identifyLayout->addWidget(signTo1, 2, 2, Qt::AlignHCenter );
    identifyLayout->addWidget(areaSetVal2, 2, 3);
    identifyLayout->addWidget(radSetLabel, 3, 0);
    identifyLayout->addWidget(radSetVal1, 3, 1);
    identifyLayout->addWidget(signTo2, 3, 2, Qt::AlignHCenter );
    identifyLayout->addWidget(radSetVal2, 3, 3);
    identifyLayout->addWidget(fillSetLabel, 4, 0);
    identifyLayout->addWidget(fillSetVal1, 4, 1);
    identifyLayout->addWidget(signTo3, 4, 2, Qt::AlignHCenter );
    identifyLayout->addWidget(fillSetVal2, 4, 3);
    identifyLayout->addWidget(flawAreaSetLabel, 5, 0);
    identifyLayout->addWidget(flawAreaSetVal1, 5, 1);
    identifyLayout->addWidget(signTo4, 5, 2, Qt::AlignHCenter );
    identifyLayout->addWidget(flawAreaSetVal2, 5, 3);
    identifyLayout->addWidget(flawRadSetLabel, 6, 0);
    identifyLayout->addWidget(flawRadSetVal1, 6, 1);
    identifyLayout->addWidget(signTo5, 6, 2, Qt::AlignHCenter );
    identifyLayout->addWidget(flawRadSetVal2, 6, 3);
    identifyLayout->addWidget(remnentAlertLabel, 7, 0);
    identifyLayout->addWidget(remnentAlertVal, 7, 1);
    _identifyParaWidget->setLayout(identifyLayout);

}

void SetupWidget::CameraParaWidget()
{
    _cameraParaWidget = new QWidget();
    QVBoxLayout *camParaLayout = new QVBoxLayout();
    QGridLayout *gridLayout1 = new QGridLayout();
    lineFreqLabel = new QLabel("行频:");
    lineFreqVal = new QSpinBox();
    gainLabel = new QLabel("增益:");
    gainVal = new QSpinBox();
    expoTimeLabel = new QLabel("曝光时间:");
    expoTimeVal = new QDoubleSpinBox();

    gridLayout1->addWidget(lineFreqLabel, 0, 0);
    gridLayout1->addWidget(lineFreqVal, 0, 1);
    gridLayout1->addWidget(gainLabel, 1, 0);
    gridLayout1->addWidget(gainVal, 1, 1);
    gridLayout1->addWidget(expoTimeLabel, 2, 0);
    gridLayout1->addWidget(expoTimeVal, 2, 1);
    gridLayout1->setColumnStretch(0, 1);
    gridLayout1->setColumnStretch(1, 4);


    QHBoxLayout *layout1 = new QHBoxLayout();
    QHBoxLayout *layout2 = new QHBoxLayout();
    QHBoxLayout *layout3 = new QHBoxLayout();
    QHBoxLayout *layout4 = new QHBoxLayout();
    QHBoxLayout *layout5 = new QHBoxLayout();
    QHBoxLayout *layout6 = new QHBoxLayout();
    QHBoxLayout *layout7 = new QHBoxLayout();

    plcIpLabel = new QLabel("PLC IP");
    plcIpVal = new DigitUnitFrame(QString(), true, 0, 10000);
    layout1->addWidget(plcIpLabel);
    layout1->addWidget(plcIpVal);

    rtQtyAddrLabel = new QLabel("实时数量地址");
    QLabel *D1 = new QLabel("D");
    rtQtyAddrVal = new QSpinBox();
    layout2->addWidget(rtQtyAddrLabel);
    layout2->addWidget(D1);
    layout2->addWidget(rtQtyAddrVal);

    aQtyAddrLabel = new QLabel("单瓶数量地址");
    QLabel *D2 = new QLabel("D");
    aQtyAddrVal = new QSpinBox();
    layout3->addWidget(aQtyAddrLabel);
    layout3->addWidget(D2);
    layout3->addWidget(aQtyAddrVal);

    coorXAddrLabel = new QLabel("插料坐标X地址");
    QLabel *D3 = new QLabel("D");
    coorXAddrVal = new QSpinBox();
    layout4->addWidget(coorXAddrLabel);
    layout4->addWidget(D3);
    layout4->addWidget(coorXAddrVal);

    coorYAddrLabel = new QLabel("插料坐标Y地址");
    QLabel *D4 = new QLabel("D");
    coorYAddrVal = new QSpinBox();
    layout5->addWidget(coorYAddrLabel);
    layout5->addWidget(D4);
    layout5->addWidget(coorYAddrVal);

    fullAddrLabel = new QLabel("满瓶信号地址");
    QLabel *M1 = new QLabel("M");
    fullAddrVal = new QSpinBox();
    layout6->addWidget(fullAddrLabel);
    layout6->addWidget(M1);
    layout6->addWidget(fullAddrVal);

    flawAddrLabel = new QLabel("瑕疵信号地址");
    QLabel *M2 = new QLabel("M");
    flawAddrVal = new QSpinBox();
    layout7->addWidget(flawAddrLabel);
    layout7->addWidget(M2);
    layout7->addWidget(flawAddrVal);

    QGridLayout *gridLayout2 = new QGridLayout();
    gridLayout2->addLayout(layout1, 0, 0);
    gridLayout2->addLayout(layout2, 1, 0);
    gridLayout2->addLayout(layout3, 1, 1);
    gridLayout2->addLayout(layout4, 2, 0);
    gridLayout2->addLayout(layout5, 2, 1);
    gridLayout2->addLayout(layout6, 3, 0);
    gridLayout2->addLayout(layout7, 3, 1);


    camParaLayout->addLayout(gridLayout1);
    camParaLayout->addLayout(gridLayout2);
    _cameraParaWidget->setLayout(camParaLayout);

}

void SetupWidget::MachineCtrlWidget()
{
    _machineCtrlWidget = new QWidget();
    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QGridLayout *gridLayout = new QGridLayout();
    QString mcBtnQSS = "QPushButton{ \
                            min-width: 200px; \
                            min-height: 80px; \
                            background: #adb5bd; \
                            border-radius: 4px; \
                            font: 14pt '微软雅黑';} \
                        QPushButton:pressed{ \
                            background-color: rgb(211, 211, 211);}";
    mcBelt = new QPushButton("传送带");
    mcBlockBottle = new QPushButton("挡瓶气缸");
    mcKick = new QPushButton("剔除气缸");
    mcFunnel = new QPushButton("漏斗气缸");
    mcBlockPlank = new QPushButton("挡板气缸");
    mcShaker = new QPushButton("振动盘");
    mcPlug1 = new QPushButton("插板1");
    mcPlug2 = new QPushButton("插板2");
    mcPlug3 = new QPushButton("插板3");
    mcPlug4 = new QPushButton("插板4");
    mcPlug5 = new QPushButton("插板5");
    mcPlug6 = new QPushButton("插板6");
    mcPlug7 = new QPushButton("插板7");
    mcPlug8 = new QPushButton("插板8");

    vLayout->addWidget(mcBelt);
    vLayout->addWidget(mcBlockBottle);
    vLayout->addWidget(mcKick);
    vLayout->addWidget(mcFunnel);
    vLayout->addWidget(mcBlockPlank);
    gridLayout->addWidget(mcPlug1, 0, 0);
    gridLayout->addWidget(mcPlug2, 0, 1);
    gridLayout->addWidget(mcPlug3, 1, 0);
    gridLayout->addWidget(mcPlug4, 1, 1);
    gridLayout->addWidget(mcPlug5, 2, 0);
    gridLayout->addWidget(mcPlug6, 2, 1);
    gridLayout->addWidget(mcPlug7, 3, 0);
    gridLayout->addWidget(mcPlug8, 3, 1);

    hLayout->addLayout(vLayout, 1);
    hLayout->addWidget(mcShaker, 1);
    hLayout->addLayout(gridLayout, 2);

    _machineCtrlWidget->setLayout(hLayout);
    _machineCtrlWidget->setStyleSheet(mcBtnQSS);
}

void SetupWidget::ElectricParaWidget()
{
    QString btnQSS = "QPushButton{ \
                         min-width: 200px; \
                         min-height: 80px; \
                         background: #adb5bd; \
                         border-radius: 4px; \
                         font: 14pt '微软雅黑';} \
                     QPushButton:pressed{ \
                         background-color: rgb(211, 211, 211);}";

    _electricParaWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    QHBoxLayout *hLayout2 = new QHBoxLayout();
    QGridLayout *gLayout1 = new QGridLayout();
    QGridLayout *gLayout2 = new QGridLayout();
    epCutTime = new QLabel("卡料时间");
    epCutTime->setFixedHeight(40);
    epCutTimeVal = new DigitUnitFrame("ms", true, 0, 10000);
    epCutTimeVal->setFont(_fontYahei15);
    epDropDelay = new QLabel("落料延时");
    epDropDelay->setFixedHeight(40);
    epDropDelayVal = new DigitUnitFrame("ms", true, 0, 10000);
    epDropDelayVal->setFont(_fontYahei15);

    epFillTime = new QLabel("装瓶时间");
    epFillTime->setFixedHeight(40);
    epFillTimeVal = new DigitUnitFrame("ms", true, 0, 10000);
    epFillTimeVal->setFont(_fontYahei15);

    epChangeTime = new QLabel("换瓶时间");
    epChangeTime->setFixedHeight(40);
    epChangeTimeVal = new DigitUnitFrame("ms", true, 0, 10000);
    epChangeTimeVal->setFont(_fontYahei15);

    epFlawKickTime = new QLabel("瑕疵剔除时间");
    epFlawKickTime->setFixedHeight(40);
    epFlawKickTimeVal = new DigitUnitFrame("ms", true, 0, 10000);
    epFlawKickTimeVal->setFont(_fontYahei15);

    epFlawKickDelay = new QLabel("瑕疵剔除延时");
    epFlawKickDelay->setFixedHeight(40);
    epFlawKickDelayVal = new DigitUnitFrame("ms", true, 0, 10000);
    epFlawKickDelayVal->setFont(_fontYahei15);

    epShakeTime = new QLabel("抖动时间");
    epShakeTime->setFixedHeight(40);
    epShakeTimeVal = new DigitUnitFrame("ms", true, 0, 10000);
    epShakeTimeVal->setFont(_fontYahei15);

    epBlock2Time = new QLabel("2号挡瓶时间");
    epBlock2Time->setFixedHeight(40);
    epBlock2TimeVal = new DigitUnitFrame("ms", true, 0, 10000);
    epBlock2TimeVal->setFont(_fontYahei15);

    epShaker1Volt = new QLabel("振动盘1电压设定");
    epShaker1Volt->setFixedHeight(40);
    epShaker1VoltVal = new DigitUnitFrame("V", true, 0, 10000);
    epShaker1VoltVal->setFont(_fontYahei15);

    epShaker1Freq = new QLabel("振动盘1频率设定");
    epShaker1Freq->setFixedHeight(40);
    epShaker1FreqVal = new DigitUnitFrame("Hz", true, 0, 10000);
    epShaker1FreqVal->setFont(_fontYahei15);

    epShaker2Volt = new QLabel("振动盘2电压设定");
    epShaker2Volt->setFixedHeight(40);
    epShaker2VoltVal = new DigitUnitFrame("V", true, 0, 10000);
    epShaker2VoltVal->setFont(_fontYahei15);

    epShaker2Freq = new QLabel("振动盘2频率设定");
    epShaker2Freq->setFixedHeight(40);
    epShaker2FreqVal = new DigitUnitFrame("Hz", true, 0, 10000);
    epShaker2FreqVal->setFont(_fontYahei15);

    epShaker3Volt = new QLabel("振动盘3电压设定");
    epShaker3Volt->setFixedHeight(40);
    epShaker3VoltVal = new DigitUnitFrame("V", true, 0, 10000);
    epShaker3VoltVal->setFont(_fontYahei15);

    epShaker3Freq = new QLabel("振动盘3频率设定");
    epShaker3Freq->setFixedHeight(40);
    epShaker3FreqVal = new DigitUnitFrame("Hz", true, 0, 10000);
    epShaker3FreqVal->setFont(_fontYahei15);

    epStopRatio = new QLabel("振动盘停止百分比");
    epStopRatio->setFixedHeight(40);
    epStopRatioVal = new DigitUnitFrame("%", true, 0, 10000);
    epStopRatioVal->setFont(_fontYahei15);

    motorUp = new QPushButton("电机上升");
    unLoadCylinder = new QPushButton("脱卸气缸");
    motorDown = new QPushButton("电机下降");

    motorUp->setStyleSheet(btnQSS);
    unLoadCylinder->setStyleSheet(btnQSS);
    motorDown->setStyleSheet(btnQSS);

    gLayout1->addWidget(epCutTime, 0, 0);
    gLayout1->addWidget(epCutTimeVal, 0, 1);
    gLayout1->addWidget(epDropDelay, 1, 0);
    gLayout1->addWidget(epDropDelayVal, 1, 1);
    gLayout1->addWidget(epFillTime, 2, 0);
    gLayout1->addWidget(epFillTimeVal, 2, 1);
    gLayout1->addWidget(epChangeTime, 3, 0);
    gLayout1->addWidget(epChangeTimeVal, 3, 1);
    gLayout1->addWidget(epFlawKickTime, 4, 0);
    gLayout1->addWidget(epFlawKickTimeVal, 4, 1);
    gLayout1->addWidget(epFlawKickDelay, 5, 0);
    gLayout1->addWidget(epFlawKickDelayVal, 5, 1);
    gLayout1->addWidget(epShakeTime, 6, 0);
    gLayout1->addWidget(epShakeTimeVal, 6, 1);
    gLayout1->addWidget(epBlock2Time, 7, 0);
    gLayout1->addWidget(epBlock2TimeVal, 7, 1);

    gLayout2->addWidget(epShaker1Volt, 0, 0);
    gLayout2->addWidget(epShaker1VoltVal, 0, 1);
    gLayout2->addWidget(epShaker1Freq, 1, 0);
    gLayout2->addWidget(epShaker1FreqVal, 1, 1);
    gLayout2->addWidget(epShaker2Volt, 2, 0);
    gLayout2->addWidget(epShaker2VoltVal, 2, 1);
    gLayout2->addWidget(epShaker2Freq, 3, 0);
    gLayout2->addWidget(epShaker2FreqVal, 3, 1);
    gLayout2->addWidget(epShaker3Volt, 4, 0);
    gLayout2->addWidget(epShaker3VoltVal, 4, 1);
    gLayout2->addWidget(epShaker3Freq, 5, 0);
    gLayout2->addWidget(epShaker3FreqVal, 5, 1);
    gLayout2->addWidget(epStopRatio, 6, 0);
    gLayout2->addWidget(epStopRatioVal, 6, 1);

    hLayout1->addLayout(gLayout1);
    hLayout1->addLayout(gLayout2);
    hLayout2->addWidget(motorUp);
    hLayout2->addWidget(unLoadCylinder);
    hLayout2->addWidget(motorDown);

    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    _electricParaWidget->setLayout(vLayout);

}

void SetupWidget::OtherParaWidget()
{
    _otherParaWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QVBoxLayout *vLayout1 = new QVBoxLayout();
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    QHBoxLayout *hLayout2 = new QHBoxLayout();
    QHBoxLayout *hLayout3 = new QHBoxLayout();
    QHBoxLayout *hLayout4 = new QHBoxLayout();
    QHBoxLayout *hLayout5 = new QHBoxLayout();
    QFrame *frame1 = new QFrame();
    QFrame *frame2 = new QFrame();
    groupBox = new QGroupBox("图片保存");
    opRunTime = new QLabel("运行时间");
    opRunTimeVal = new QSpinBox();
    opLanguage = new QLabel("语言选择");
    opLanguageVal = new QComboBox();
    opImageSave = new QLabel("是否保存");
    opImageSaveVal = new QPushButton();
    opSaveDir = new QLabel("保存路径");
    opSaveDirVal = new QLineEdit();
    opChoose = new QPushButton("选择");
    opSaveDays = new QLabel("保存天数");
    opSaveDaysVal = new QLineEdit();

    hLayout1->addWidget(opRunTime);
    hLayout1->addWidget(opRunTimeVal);
    hLayout2->addWidget(opLanguage);
    hLayout2->addWidget(opLanguageVal);
    hLayout3->addWidget(opImageSave);
    hLayout3->addWidget(opImageSaveVal);
    hLayout4->addWidget(opSaveDir);
    hLayout4->addWidget(opSaveDirVal);
    hLayout4->addWidget(opChoose);
    hLayout5->addWidget(opSaveDays);
    hLayout5->addWidget(opSaveDaysVal);

    frame1->setLayout(hLayout1);
    frame2->setLayout(hLayout2);
    vLayout1->addLayout(hLayout3);
    vLayout1->addLayout(hLayout4);
    vLayout1->addLayout(hLayout5);

    groupBox->setLayout(vLayout1);

    vLayout->addWidget(frame1, 1);
    vLayout->addWidget(frame2, 1);
    vLayout->addWidget(groupBox, 2);

    _otherParaWidget->setLayout(vLayout);
}

void promptMessage(const QString &str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    QTimer::singleShot(600, &msgBox, &QMessageBox::close);
    msgBox.exec();
}

void SetupWidget::SlotRecipeLoad()
{
    if(!CheckRecipeName()) return;
    QString filename = "config/recipe/" + newRecipe->text();
    ReadSettingFile(filename);
    mw->curRecipeVal->setText(newRecipe->text());

    promptMessage("加载完成");
}

void SetupWidget::SlotRecipeNew()
{
    if(newRecipe->text().isEmpty()){
        QMessageBox::warning(this, "名称错误", "无配方名");
        return;
    }
    QString str = newRecipe->text();
    if(TestContainRecipe(str)){
        QMessageBox msg;
        msg.setText("配方名重复,点击ok覆盖,cancel取消");
        msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = msg.exec();
        if(ret == QMessageBox::Cancel) return;
        QString filename = "config/recipe/" + str;
        Write2SettingFile(filename);
        newRecipe->setText(QString());
        return;
    }
    QString filename = "config/recipe/" + str;
    Write2SettingFile(filename);
    recipeList->addItem(newRecipe->text());
    //newRecipe->setText(QString());
}

void SetupWidget::SlotRecipeSave()
{
    if(!CheckRecipeName()) return;
    QString filename = "config/recipe/" + newRecipe->text();
    Write2SettingFile(filename);

    promptMessage("保存完成");
}

void SetupWidget::SlotRecipeDel()
{
    if(!CheckRecipeName()) return;
    QString filename = "config/recipe/" + newRecipe->text();
    QFile file(filename);
    if(file.remove()){
        QListWidgetItem *item = recipeList->currentItem();
        recipeList->removeItemWidget(item);
        delete item;
        newRecipe->setText(QString());

        promptMessage("删除成功");
    }
}

void SetupWidget::ReadSettingFile(const QString &filename)
{
    QSettings setting(filename, QSettings::IniFormat);
    setting.setFallbacksEnabled(false);

    mw->aBtlQtyFrame->setValue(setting.value("aBtlQty").toInt());
    mw->shaker1Val->setValue(setting.value("shaker1").toInt());
    mw->shaker2Val->setValue(setting.value("shaker2").toInt());
    mw->shaker3Val->setValue(setting.value("shaker3").toInt());
    setting.beginGroup("identify parameter");
    thresholdVal1->setValue(setting.value("threshold_min").toInt());
    thresholdVal2->setValue(setting.value("threshold_max").toInt());
    preprocType->setCurrentIndex(setting.value("preprocess_index").toInt());
    operatorSizeVal->setValue(setting.value("operator_size").toInt());
    areaSetVal1->setValue(setting.value("area_min").toInt());
    areaSetVal2->setValue(setting.value("area_max").toInt());
    radSetVal1->setValue(setting.value("radius_min").toInt());
    radSetVal2->setValue(setting.value("radius_max").toInt());
    fillSetVal1->setValue(setting.value("fill_min").toInt());
    fillSetVal2->setValue(setting.value("fill_max").toInt());
    flawAreaSetVal1->setValue(setting.value("flaw_area_min").toInt());
    flawAreaSetVal2->setValue(setting.value("flaw_area_max").toInt());
    flawRadSetVal1->setValue(setting.value("flaw_radius_min").toInt());
    flawRadSetVal2->setValue(setting.value("flaw_radius_max").toInt());
    remnentAlertVal->setValue(setting.value("remnent_alert").toInt());
    setting.endGroup();
    setting.beginGroup("camera parameter");
    lineFreqVal->setValue(setting.value("line_frequency").toInt());
    gainVal->setValue(setting.value("gain").toInt());
    expoTimeVal->setValue(setting.value("exposure_time").toInt());
    plcIpVal->setValue(setting.value("plc_ip").toInt());
    rtQtyAddrVal->setValue(setting.value("rt_quantity").toInt());
    aQtyAddrVal->setValue(setting.value("one_bottle_quantity").toInt());
    coorXAddrVal->setValue(setting.value("coordinate_x").toInt());
    coorYAddrVal->setValue(setting.value("coordinate_y").toInt());
    fullAddrVal->setValue(setting.value("bottle_full_signal").toInt());
    flawAddrVal->setValue(setting.value("flaw_signal").toInt());
    setting.endGroup();
    setting.beginGroup("electric parameter");
    epCutTimeVal->setValue(setting.value("cut_time").toInt());
    epDropDelayVal->setValue(setting.value("drop_delay").toInt());
    epFillTimeVal->setValue(setting.value("fill_time").toInt());
    epChangeTimeVal->setValue(setting.value("change_time").toInt());
    epFlawKickTimeVal->setValue(setting.value("flaw_kick_time").toInt());
    epFlawKickDelayVal->setValue(setting.value("flaw_kick_delay").toInt());
    epShakeTimeVal->setValue(setting.value("shake_time").toInt());
    epBlock2TimeVal->setValue(setting.value("block2_time").toInt());
    epShaker1VoltVal->setValue(setting.value("shaker1_vol").toInt());
    epShaker1VoltVal->setValue(setting.value("shaker1_freq").toInt());
    epShaker2VoltVal->setValue(setting.value("shaker2_vol").toInt());
    epShaker2VoltVal->setValue(setting.value("shaker2_freq").toInt());
    epShaker3VoltVal->setValue(setting.value("shaker3_vol").toInt());
    epShaker3VoltVal->setValue(setting.value("shaker3_freq").toInt());
    epStopRatioVal->setValue(setting.value("stop_ratio").toInt());
    setting.endGroup();



}

void SetupWidget::Write2SettingFile(const QString &filename)
{
    QSettings setting(filename, QSettings::IniFormat);

    setting.setValue("aBtlQty", mw->aBtlQtyFrame->value());
    setting.setValue("shaker1", mw->shaker1Val->value());
    setting.setValue("shaker2", mw->shaker2Val->value());
    setting.setValue("shaker3", mw->shaker3Val->value());
    setting.beginGroup("identify parameter");
    setting.setValue("threshold_min", thresholdVal1->value());
    setting.setValue("threshold_max", thresholdVal2->value());
    setting.setValue("preprocess_index", preprocType->currentIndex());
    setting.setValue("operator_size", operatorSizeVal->value());
    setting.setValue("area_min", areaSetVal1->value());
    setting.setValue("area_max", areaSetVal2->value());
    setting.setValue("radius_min", radSetVal1->value());
    setting.setValue("radius_max", radSetVal2->value());
    setting.setValue("fill_min", fillSetVal1->value());
    setting.setValue("fill_max", fillSetVal2->value());
    setting.setValue("flaw_area_min", flawAreaSetVal1->value());
    setting.setValue("flaw_area_max", flawAreaSetVal2->value());
    setting.setValue("flaw_radius_min", flawRadSetVal1->value());
    setting.setValue("flaw_radius_max", flawRadSetVal2->value());
    setting.setValue("remnent_alert", remnentAlertVal->value());
    setting.endGroup();
    setting.beginGroup("camera parameter");
    setting.setValue("line_frequency", lineFreqVal->value());
    setting.setValue("gain", gainVal->value());
    setting.setValue("exposure_time", expoTimeVal->value());
    setting.setValue("plc_ip", plcIpVal->value());
    setting.setValue("rt_quantity", rtQtyAddrVal->value());
    setting.setValue("one_bottle_quantity", aQtyAddrVal->value());
    setting.setValue("coordinate_x", coorXAddrVal->value());
    setting.setValue("coordinate_y", coorYAddrVal->value());
    setting.setValue("bottle_full_signal", fullAddrVal->value());
    setting.setValue("flaw_signal", flawAddrVal->value());
    setting.endGroup();
    setting.beginGroup("electric parameter");
    setting.setValue("cut_time", epCutTimeVal->value());
    setting.setValue("drop_delay", epDropDelayVal->value());
    setting.setValue("fill_time", epFillTimeVal->value());
    setting.setValue("change_time", epChangeTimeVal->value());
    setting.setValue("flaw_kick_time", epFlawKickTimeVal->value());
    setting.setValue("flaw_kick_delay", epFlawKickDelayVal->value());
    setting.setValue("shake_time", epShakeTimeVal->value());
    setting.setValue("block2_time", epBlock2TimeVal->value());
    setting.setValue("shaker1_vol", epShaker1VoltVal->value());
    setting.setValue("shaker1_freq", epShaker1VoltVal->value());
    setting.setValue("shaker2_vol", epShaker2VoltVal->value());
    setting.setValue("shaker2_freq", epShaker2VoltVal->value());
    setting.setValue("shaker3_vol", epShaker3VoltVal->value());
    setting.setValue("shaker3_freq", epShaker3VoltVal->value());
    setting.setValue("stop_ratio", epStopRatioVal->value());
    setting.endGroup();

}

void SetupWidget::LoadRecipeName()
{
    QDir dir("config/recipe");
    QStringList list = dir.entryList(QDir::Files);
//    QStringList name_list;
//    QString suffix = ".ini";
//    for(int i = 0; i != list.count(); ++i){
//        QString s = list[i].replace(suffix, "");
//        name_list << s;
//    }

    recipeList->addItems(list);
}

void SetupWidget::SlotSelectRecipe(const QString &s)
{
    newRecipe->setText(s);
}

bool SetupWidget::TestContainRecipe(const QString& s)
{
    QDir dir("config/recipe/");
    QStringList list = dir.entryList(QDir::Files);
    for(QString &str : list){
        if(s == str) return true;
    }
    return false;
}

bool SetupWidget::CheckRecipeName()
{
    QString str = newRecipe->text();
    if(str.isEmpty()){
        QMessageBox::warning(this, "名称错误", "无配方名");
        return false;
    }
    if(!TestContainRecipe(str)){
        QMessageBox::warning(this, "文件名错误", "配方文件夹中无此配方");
        return false;
    }
    return true;
}

void SetupWidget::LoadRecipeParameter()
{
    ReadSettingFile("config/recipe/" + mw->curRecipeVal->text());
}
