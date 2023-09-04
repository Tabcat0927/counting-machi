#include "setupwidget.h"

SetupWidget::SetupWidget(QWidget *parent) : QWidget(parent)
{
    _recipeBtnQSS = "min-width: 256px;min-height: 40px;"
                    "background: #adb5bd;border-radius: 4px;";
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
    thresholdVal1 = new QLineEdit();
    signTo = new QLabel(QStringLiteral("<->"));
    thresholdVal2 = new QLineEdit();

    preprocLabel = new QLabel(QStringLiteral("预处理方法"));
    preprocType = new QComboBox();
    preprocType->addItem(QStringLiteral("开运算_圆"));
    preprocType->addItem(QStringLiteral("开运算_方"));
    operatorSize = new QLabel(QStringLiteral("算子尺寸"));
    operatorSizeVal = new QLineEdit();

    areaSetLabel = new QLabel(QStringLiteral("面积设置"));
    areaSetVal1 = new QLineEdit();
    signTo1 = new QLabel(QStringLiteral("<->"));
    areaSetVal2 = new QLineEdit();

    radSetLabel = new QLabel(QStringLiteral("半径设置"));
    radSetVal1 = new QLineEdit();
    signTo2 = new QLabel(QStringLiteral("<->"));
    radSetVal2 = new QLineEdit();

    fillSetLabel = new QLabel(QStringLiteral("填充度设置"));
    fillSetVal1 = new QLineEdit();
    signTo3 = new QLabel(QStringLiteral("<->"));
    fillSetVal2 = new QLineEdit();

    brokenAreaSetLabel = new QLabel(QStringLiteral("填充度设置"));
    brokenAreaSetVal1 = new QLineEdit();
    signTo4 = new QLabel(QStringLiteral("<->"));
    brokenAreaSetVal2 = new QLineEdit();

    brokenRadSetLabel = new QLabel(QStringLiteral("填充度设置"));
    brokenRadSetVal1 = new QLineEdit();
    signTo5 = new QLabel(QStringLiteral("<->"));
    brokenRadSetVal2 = new QLineEdit();

    remnentAlertLabel = new QLabel(QStringLiteral("填充度设置"));
    remnentAlertVal = new QLineEdit();

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
    QString mcBtnQSS = "min-width: 200px; \
                        min-height: 80px; \
                        background: #adb5bd; \
                        border-radius: 4px;";
    mcBelt = new QPushButton(QStringLiteral("传送带"));
    mcBelt->setStyleSheet(mcBtnQSS);
    mcBlockBottle = new QPushButton(QStringLiteral("挡瓶气缸"));
    mcBlockBottle->setStyleSheet(mcBtnQSS);
    mcKick = new QPushButton(QStringLiteral("剔除气缸"));
    mcKick->setStyleSheet(mcBtnQSS);
    mcFunnel = new QPushButton(QStringLiteral("漏斗气缸"));
    mcFunnel->setStyleSheet(mcBtnQSS);
    mcBlockPlank = new QPushButton(QStringLiteral("挡板气缸"));
    mcBlockPlank->setStyleSheet(mcBtnQSS);
    mcShaker = new QPushButton(QStringLiteral("振动盘"));
    mcShaker->setStyleSheet(mcBtnQSS);
    mcPlug1 = new QPushButton(QStringLiteral("插板1"));
    mcPlug1->setStyleSheet(mcBtnQSS);
    mcPlug2 = new QPushButton(QStringLiteral("插板2"));
    mcPlug2->setStyleSheet(mcBtnQSS);
    mcPlug3 = new QPushButton(QStringLiteral("插板3"));
    mcPlug3->setStyleSheet(mcBtnQSS);
    mcPlug4 = new QPushButton(QStringLiteral("插板4"));
    mcPlug4->setStyleSheet(mcBtnQSS);
    mcPlug5 = new QPushButton(QStringLiteral("插板5"));
    mcPlug5->setStyleSheet(mcBtnQSS);
    mcPlug6 = new QPushButton(QStringLiteral("插板6"));
    mcPlug6->setStyleSheet(mcBtnQSS);
    mcPlug7 = new QPushButton(QStringLiteral("插板7"));
    mcPlug7->setStyleSheet(mcBtnQSS);
    mcPlug8 = new QPushButton(QStringLiteral("插板8"));
    mcPlug8->setStyleSheet(mcBtnQSS);

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

    hLayout->addLayout(vLayout);
    hLayout->addWidget(mcShaker);
    hLayout->addLayout(gridLayout);

    _machineCtrlWidget->setLayout(hLayout);
}

void SetupWidget::ElectricParaWidget()
{
    _electricParaWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    QHBoxLayout *hLayout2 = new QHBoxLayout();
    QGridLayout *gLayout1 = new QGridLayout();
    QGridLayout *gLayout2 = new QGridLayout();
    epCutTime = new QLabel(QStringLiteral("卡料时间"));
    epCutTimeVal = new QLineEdit();
    epDropDelay = new QLabel(QStringLiteral("落料延时"));
    epDropDelayVal = new QLineEdit();
    epFillTime = new QLabel(QStringLiteral("装瓶时间"));
    epFillTimeVal = new QLineEdit();
    epChangeTime = new QLabel(QStringLiteral("换瓶时间"));
    epChangeTimeVal = new QLineEdit();
    epFlawKickTime = new QLabel(QStringLiteral("瑕疵剔除时间"));
    epFlawKickTimeVal = new QLineEdit();
    epFlawKickDelay = new QLabel(QStringLiteral("瑕疵剔除延时"));
    epFlawKickDelayVal = new QLineEdit();
    epShakeTime = new QLabel(QStringLiteral("抖动时间"));
    epShakeTimeVal = new QLineEdit();
    epBlock2Time = new QLabel(QStringLiteral("2号挡瓶时间"));
    epBlock2TimeVal = new QLineEdit();
    epShaker1Volt = new QLabel(QStringLiteral("振动盘1电压设定"));
    epShaker1VoltVal = new QLineEdit();
    epShaker1Freq = new QLabel(QStringLiteral("振动盘1频率设定"));
    epShaker1FreqVal = new QLineEdit();
    epShaker2Volt = new QLabel(QStringLiteral("振动盘2电压设定"));
    epShaker2VoltVal = new QLineEdit();
    epShaker2Freq = new QLabel(QStringLiteral("振动盘2频率设定"));
    epShaker2FreqVal = new QLineEdit();
    epShaker3Volt = new QLabel(QStringLiteral("振动盘3电压设定"));
    epShaker3VoltVal = new QLineEdit();
    epShaker3Freq = new QLabel(QStringLiteral("振动盘3频率设定"));
    epShaker3FreqVal = new QLineEdit();
    epShakerRadio = new QLabel(QStringLiteral("振动盘停止百分比"));
    epShakerRadioVal = new QLineEdit();
    motorUp = new QPushButton(QStringLiteral("电机上升"));
    unLoadCylinder = new QPushButton(QStringLiteral("脱卸气缸"));
    motorDown = new QPushButton(QStringLiteral("电机下降"));

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
