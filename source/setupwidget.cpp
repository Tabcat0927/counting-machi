#include "setupwidget.h"

SetupWidget::SetupWidget(QWidget *parent) : QWidget(parent)
{
    _recipeBtnQSS = "QPushButton{"
                    "min-width: 256px;"
                    "min-height: 40px;"
                    "background: #adb5bd;"
                    "border-radius: 4px;}"
                    "QPushButton:pressed{"
                    "background-color: rgb(220, 220, 220);}";
    CreateUi();

}

void SetupWidget::CreateUi()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    RecipeWidget();

    QTabWidget *setWidget = new QTabWidget();
    setWidget->setFont(QFont(QStringLiteral("微软雅黑"), 15));
    IdentifyParaWidget();
    CameraParaWidget();
    MachineCtrlWidget();
    ElectricParaWidget();
    OtherParaWidget();
    setWidget->addTab(_identifyParaWidget, QStringLiteral("识别参数"));
    setWidget->addTab(_cameraParaWidget, QStringLiteral("相机参数"));
    setWidget->addTab(_machineCtrlWidget, QStringLiteral("手动控制"));
    setWidget->addTab(_electricParaWidget, QStringLiteral("电气参数"));
    setWidget->addTab(_otherParaWidget, QStringLiteral("其他参数"));

    mainLayout->addWidget(_recipeWidget, 1);
    mainLayout->addWidget(setWidget, 3);

}

void SetupWidget::RecipeWidget()
{
    _recipeWidget = new QWidget();
    QVBoxLayout *recipeLayout = new QVBoxLayout();
    _recipeWidget->setLayout(recipeLayout);
    recipeList = new QListWidget();
    recipeList->setStyleSheet("QListWidget{"
                              "background-color: rgb(220, 220, 220);"
                              "font: 14pt '微软雅黑';}"
                              "QListWidget::item{"
                              "height: 30px;}");

    recipeName = new QLabel(QStringLiteral("配方名称:"));
    newRecipe = new QLineEdit();
    newRecipe->setStyleSheet("border: 1px solid #1c7ed6; \
                              min-height: 40px; \
                              border-radius: 4px; \
                              background: white;");
    btnLoad = new QPushButton(QIcon(":/icon/ico/project/saveas.png"),
                                    QStringLiteral("加载"));
    btnLoad->setStyleSheet(_recipeBtnQSS);
    btnNew = new QPushButton(QIcon(":/icon/ico/project/new.png"),
                                   QStringLiteral("新建"));
    btnNew->setStyleSheet(_recipeBtnQSS);
    btnSave = new QPushButton(QIcon(":/icon/ico/project/save.png"),
                                    QStringLiteral("保存"));
    btnSave->setStyleSheet(_recipeBtnQSS);
    btnDelete = new QPushButton(QIcon(":/icon/ico/cancel1.png"),
                                      QStringLiteral("删除"));
    btnDelete->setStyleSheet(_recipeBtnQSS);

    recipeLayout->addWidget(recipeList);
    recipeLayout->addWidget(recipeName);
    recipeLayout->addWidget(newRecipe);
    recipeLayout->addWidget(btnLoad);
    recipeLayout->addWidget(btnNew);
    recipeLayout->addWidget(btnSave);
    recipeLayout->addWidget(btnDelete);

}

void SetupWidget::IdentifyParaWidget()
{
    _identifyParaWidget = new QWidget();
    QGridLayout *identifyLayout = new QGridLayout();
    identifyLayout->setColumnStretch(0, 1);
    identifyLayout->setColumnStretch(1, 1);
    identifyLayout->setColumnStretch(2, 1);
    identifyLayout->setColumnStretch(3, 1);
    thresholdLabel = new QLabel(QStringLiteral("阈值设置"));
    thresholdLabel->setFixedHeight(35);
    thresholdVal1 = new DigitUnitFrame(QString(), true);
    signTo = new QLabel(QStringLiteral("<->"));
    thresholdVal2 = new DigitUnitFrame(QString(), true);


    preprocLabel = new QLabel(QStringLiteral("预处理方法"));
    preprocLabel->setFixedHeight(35);
    preprocType = new QComboBox();
    preprocType->addItem(QStringLiteral("开运算_圆"));
    preprocType->addItem(QStringLiteral("开运算_方"));
    operatorSize = new QLabel(QStringLiteral("算子尺寸"));
    operatorSizeVal = new DigitUnitFrame(QString(), true);

    areaSetLabel = new QLabel(QStringLiteral("面积设置"));
    areaSetLabel->setFixedHeight(35);
    areaSetVal1 = new DigitUnitFrame(QStringLiteral("Pixel"), true);
    signTo1 = new QLabel(QStringLiteral("<->"));
    areaSetVal2 = new DigitUnitFrame(QStringLiteral("Pixel"), true);

    radSetLabel = new QLabel(QStringLiteral("半径设置"));
    radSetLabel->setFixedHeight(35);
    radSetVal1 = new DigitUnitFrame(QStringLiteral("Pixel"), true);
    signTo2 = new QLabel(QStringLiteral("<->"));
    radSetVal2 = new DigitUnitFrame(QStringLiteral("Pixel"), true);

    fillSetLabel = new QLabel(QStringLiteral("填充度设置"));
    fillSetLabel->setFixedHeight(35);
    fillSetVal1 = new DigitUnitFrame(QString(), true);
    signTo3 = new QLabel(QStringLiteral("<->"));
    fillSetVal2 = new DigitUnitFrame(QString(), true);

    brokenAreaSetLabel = new QLabel(QStringLiteral("残料面积"));
    brokenAreaSetLabel->setFixedHeight(35);
    brokenAreaSetVal1 = new DigitUnitFrame(QStringLiteral("Pixel"), true);
    signTo4 = new QLabel(QStringLiteral("<->"));
    brokenAreaSetVal2 = new DigitUnitFrame(QStringLiteral("Pixel"), true);

    brokenRadSetLabel = new QLabel(QStringLiteral("残料半径"));
    brokenRadSetLabel->setFixedHeight(35);
    brokenRadSetVal1 = new DigitUnitFrame(QStringLiteral("Pixel"), true);
    signTo5 = new QLabel(QStringLiteral("<->"));
    brokenRadSetVal2 = new DigitUnitFrame(QStringLiteral("Pixel"), true);

    remnentAlertLabel = new QLabel(QStringLiteral("余料警戒"));
    remnentAlertLabel->setFixedHeight(35);
    remnentAlertVal = new DigitUnitFrame(QStringLiteral("粒"), true);

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
    identifyLayout->addWidget(brokenAreaSetLabel, 5, 0);
    identifyLayout->addWidget(brokenAreaSetVal1, 5, 1);
    identifyLayout->addWidget(signTo4, 5, 2, Qt::AlignHCenter );
    identifyLayout->addWidget(brokenAreaSetVal2, 5, 3);
    identifyLayout->addWidget(brokenRadSetLabel, 6, 0);
    identifyLayout->addWidget(brokenRadSetVal1, 6, 1);
    identifyLayout->addWidget(signTo5, 6, 2, Qt::AlignHCenter );
    identifyLayout->addWidget(brokenRadSetVal2, 6, 3);
    identifyLayout->addWidget(remnentAlertLabel, 7, 0);
    identifyLayout->addWidget(remnentAlertVal, 7, 1);
    _identifyParaWidget->setLayout(identifyLayout);

}

void SetupWidget::CameraParaWidget()
{
    _cameraParaWidget = new QWidget();
    QVBoxLayout *camParaLayout = new QVBoxLayout();
    QGridLayout *gridLayout1 = new QGridLayout();
    lineFreqLabel = new QLabel(QStringLiteral("行频:"));
    lineFreqVal = new QSpinBox();
    gainLabel = new QLabel(QStringLiteral("增益:"));
    gainVal = new QSpinBox();
    expoTimeLabel = new QLabel(QStringLiteral("曝光时间:"));
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

    QLabel *plcIpLabel = new QLabel("PLC IP");
    QLineEdit *plcIpVal = new QLineEdit();
    layout1->addWidget(plcIpLabel);
    layout1->addWidget(plcIpVal);

    QLabel *rtQtyAddrLabel = new QLabel(QStringLiteral("实时数量地址"));
    QLabel *D1 = new QLabel("D");
    QLineEdit *rtQtyAddrVal = new QLineEdit();
    layout2->addWidget(rtQtyAddrLabel);
    layout2->addWidget(D1);
    layout2->addWidget(rtQtyAddrVal);

    QLabel *aQtyAddrLabel = new QLabel(QStringLiteral("单瓶数量地址"));
    QLabel *D2 = new QLabel("D");
    QLineEdit *aQtyAddrVal = new QLineEdit();
    layout3->addWidget(aQtyAddrLabel);
    layout3->addWidget(D2);
    layout3->addWidget(aQtyAddrVal);

    QLabel *coorXAddrLabel = new QLabel(QStringLiteral("插料坐标X地址"));
    QLabel *D3 = new QLabel("D");
    QLineEdit *coorXAddrVal = new QLineEdit();
    layout4->addWidget(coorXAddrLabel);
    layout4->addWidget(D3);
    layout4->addWidget(coorXAddrVal);

    QLabel *coorYAddrLabel = new QLabel(QStringLiteral("插料坐标Y地址"));
    QLabel *D4 = new QLabel("D");
    QLineEdit *coorYAddrVal = new QLineEdit();
    layout5->addWidget(coorYAddrLabel);
    layout5->addWidget(D4);
    layout5->addWidget(coorYAddrVal);

    QLabel *fullAddrLabel = new QLabel(QStringLiteral("满瓶信号地址"));
    QLabel *M1 = new QLabel("M");
    QLineEdit *fullAddrVal = new QLineEdit();
    layout6->addWidget(fullAddrLabel);
    layout6->addWidget(M1);
    layout6->addWidget(fullAddrVal);

    QLabel *flawAddrLabel = new QLabel(QStringLiteral("瑕疵信号地址"));
    QLabel *M2 = new QLabel("M");
    QLineEdit *flawAddrVal = new QLineEdit();
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
    mcBelt = new QPushButton(QStringLiteral("传送带"));
    mcBlockBottle = new QPushButton(QStringLiteral("挡瓶气缸"));
    mcKick = new QPushButton(QStringLiteral("剔除气缸"));
    mcFunnel = new QPushButton(QStringLiteral("漏斗气缸"));
    mcBlockPlank = new QPushButton(QStringLiteral("挡板气缸"));
    mcShaker = new QPushButton(QStringLiteral("振动盘"));
    mcPlug1 = new QPushButton(QStringLiteral("插板1"));
    mcPlug2 = new QPushButton(QStringLiteral("插板2"));
    mcPlug3 = new QPushButton(QStringLiteral("插板3"));
    mcPlug4 = new QPushButton(QStringLiteral("插板4"));
    mcPlug5 = new QPushButton(QStringLiteral("插板5"));
    mcPlug6 = new QPushButton(QStringLiteral("插板6"));
    mcPlug7 = new QPushButton(QStringLiteral("插板7"));
    mcPlug8 = new QPushButton(QStringLiteral("插板8"));

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
    epCutTime = new QLabel(QStringLiteral("卡料时间"));
    epCutTime->setFixedHeight(40);
    epCutTimeVal = new DigitUnitFrame(QStringLiteral("ms"), true);
    epDropDelay = new QLabel(QStringLiteral("落料延时"));
    epDropDelay->setFixedHeight(40);
    epDropDelayVal = new DigitUnitFrame(QStringLiteral("ms"), true);
    epFillTime = new QLabel(QStringLiteral("装瓶时间"));
    epFillTime->setFixedHeight(40);
    epFillTimeVal = new DigitUnitFrame(QStringLiteral("ms"), true);
    epChangeTime = new QLabel(QStringLiteral("换瓶时间"));
    epChangeTime->setFixedHeight(40);
    epChangeTimeVal = new DigitUnitFrame(QStringLiteral("ms"), true);
    epFlawKickTime = new QLabel(QStringLiteral("瑕疵剔除时间"));
    epFlawKickTime->setFixedHeight(40);
    epFlawKickTimeVal = new DigitUnitFrame(QStringLiteral("ms"), true);
    epFlawKickDelay = new QLabel(QStringLiteral("瑕疵剔除延时"));
    epFlawKickDelay->setFixedHeight(40);
    epFlawKickDelayVal = new DigitUnitFrame(QStringLiteral("ms"), true);
    epShakeTime = new QLabel(QStringLiteral("抖动时间"));
    epShakeTime->setFixedHeight(40);
    epShakeTimeVal = new DigitUnitFrame(QStringLiteral("ms"), true);
    epBlock2Time = new QLabel(QStringLiteral("2号挡瓶时间"));
    epBlock2Time->setFixedHeight(40);
    epBlock2TimeVal = new DigitUnitFrame(QStringLiteral("ms"), true);
    epShaker1Volt = new QLabel(QStringLiteral("振动盘1电压设定"));
    epShaker1Volt->setFixedHeight(40);
    epShaker1VoltVal = new DigitUnitFrame(QStringLiteral("V"), true);
    epShaker1Freq = new QLabel(QStringLiteral("振动盘1频率设定"));
    epShaker1Freq->setFixedHeight(40);
    epShaker1FreqVal = new DigitUnitFrame(QStringLiteral("Hz"), true);
    epShaker2Volt = new QLabel(QStringLiteral("振动盘2电压设定"));
    epShaker2Volt->setFixedHeight(40);
    epShaker2VoltVal = new DigitUnitFrame(QStringLiteral("V"), true);
    epShaker2Freq = new QLabel(QStringLiteral("振动盘2频率设定"));
    epShaker2Freq->setFixedHeight(40);
    epShaker2FreqVal = new DigitUnitFrame(QStringLiteral("Hz"), true);
    epShaker3Volt = new QLabel(QStringLiteral("振动盘3电压设定"));
    epShaker3Volt->setFixedHeight(40);
    epShaker3VoltVal = new DigitUnitFrame(QStringLiteral("V"), true);
    epShaker3Freq = new QLabel(QStringLiteral("振动盘3频率设定"));
    epShaker3Freq->setFixedHeight(40);
    epShaker3FreqVal = new DigitUnitFrame(QStringLiteral("Hz"), true);
    epShakerRadio = new QLabel(QStringLiteral("振动盘停止百分比"));
    epShakerRadio->setFixedHeight(40);
    epShakerRadioVal = new DigitUnitFrame(QStringLiteral("%"), true);
    motorUp = new QPushButton(QStringLiteral("电机上升"));
    unLoadCylinder = new QPushButton(QStringLiteral("脱卸气缸"));
    motorDown = new QPushButton(QStringLiteral("电机下降"));

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
    gLayout2->addWidget(epShakerRadio, 6, 0);
    gLayout2->addWidget(epShakerRadioVal, 6, 1);

    hLayout1->addLayout(gLayout1);
    hLayout1->addLayout(gLayout2);
    hLayout2->addWidget(motorUp);
    hLayout2->addWidget(unLoadCylinder);
    hLayout2->addWidget(motorDown);

    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    _electricParaWidget->setLayout(vLayout);
    //_electricParaWidget->setStyleSheet(btnQSS);

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
    groupBox = new QGroupBox(QStringLiteral("图片保存"));
    opRunTime = new QLabel(QStringLiteral("运行时间"));
    opRunTimeVal = new QSpinBox();
    opLanguage = new QLabel(QStringLiteral("语言选择"));
    opLanguageVal = new QComboBox();
    opImageSave = new QLabel(QStringLiteral("是否保存"));
    opImageSaveVal = new QPushButton();
    opSaveDir = new QLabel(QStringLiteral("保存路径"));
    opSaveDirVal = new QLineEdit();
    opChoose = new QPushButton(QStringLiteral("选择"));
    opSaveDays = new QLabel(QStringLiteral("保存天数"));
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
