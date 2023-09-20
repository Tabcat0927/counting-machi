#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTabWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QSettings>
#include <QMessageBox>
#include <QDir>
#include <QTimer>

#include "digitunitframe.h"
#include "mainwidget.h"

#pragma execution_character_set("utf-8")

class SetupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetupWidget(MainWidget *mw, QWidget *parent = nullptr);

    void CreateUi();

public slots:
    void SlotRecipeLoad();
    void SlotRecipeNew();
    void SlotRecipeSave();
    void SlotRecipeDel();
    void SlotSelectRecipe(const QString&);

public:
    MainWidget *mw;
    //recipe
    QListWidget *recipeList;
    QLabel *recipeName;
    QLineEdit *newRecipe;
    QPushButton *btnLoad;
    QPushButton *btnNew;
    QPushButton *btnSave;
    QPushButton *btnDelete;
    //identify parameter
    QLabel *thresholdLabel;
    DigitUnitFrame *thresholdVal1;
    QLabel *signTo;
    DigitUnitFrame *thresholdVal2;
    QLabel *preprocLabel;
    QComboBox *preprocType;
    QLabel *operatorSize;
    DigitUnitFrame *operatorSizeVal;
    QLabel *areaSetLabel;
    DigitUnitFrame *areaSetVal1;
    QLabel *signTo1;
    DigitUnitFrame *areaSetVal2;
    QLabel *radSetLabel;
    DigitUnitFrame *radSetVal1;
    QLabel *signTo2;
    DigitUnitFrame *radSetVal2;
    QLabel *fillSetLabel;
    DigitUnitFrame *fillSetVal1;
    QLabel *signTo3;
    DigitUnitFrame *fillSetVal2;
    QLabel *flawAreaSetLabel;
    DigitUnitFrame *flawAreaSetVal1;
    QLabel *signTo4;
    DigitUnitFrame *flawAreaSetVal2;
    QLabel *flawRadSetLabel;
    DigitUnitFrame *flawRadSetVal1;
    QLabel *signTo5;
    DigitUnitFrame *flawRadSetVal2;
    QLabel *remnentAlertLabel;
    DigitUnitFrame *remnentAlertVal;
    //camera parameter
    QLabel *lineFreqLabel;
    QSpinBox *lineFreqVal;
    QLabel *gainLabel;
    QSpinBox *gainVal;
    QLabel *expoTimeLabel;
    QDoubleSpinBox *expoTimeVal;
    QLabel *plcIpLabel;
    DigitUnitFrame *plcIpVal;
    QLabel *rtQtyAddrLabel;
    QSpinBox *rtQtyAddrVal;
    QLabel *aQtyAddrLabel;
    QSpinBox *aQtyAddrVal;
    QLabel *coorXAddrLabel;
    QSpinBox *coorXAddrVal;
    QLabel *coorYAddrLabel;
    QSpinBox *coorYAddrVal;
    QLabel *fullAddrLabel;
    QSpinBox *fullAddrVal;
    QLabel *flawAddrLabel;
    QSpinBox *flawAddrVal;
    //machine control
    QPushButton *mcBelt;
    QPushButton *mcBlockBottle;
    QPushButton *mcKick;
    QPushButton *mcFunnel;
    QPushButton *mcBlockPlank;
    QPushButton *mcShaker;
    QPushButton *mcPlug1;
    QPushButton *mcPlug2;
    QPushButton *mcPlug3;
    QPushButton *mcPlug4;
    QPushButton *mcPlug5;
    QPushButton *mcPlug6;
    QPushButton *mcPlug7;
    QPushButton *mcPlug8;
    //electric parameter
    QLabel *epCutTime;
    DigitUnitFrame *epCutTimeVal;
    QLabel *epDropDelay;
    DigitUnitFrame *epDropDelayVal;
    QLabel *epFillTime;
    DigitUnitFrame *epFillTimeVal;
    QLabel *epChangeTime;
    DigitUnitFrame *epChangeTimeVal;
    QLabel *epFlawKickTime;
    DigitUnitFrame *epFlawKickTimeVal;
    QLabel *epFlawKickDelay;
    DigitUnitFrame *epFlawKickDelayVal;
    QLabel *epShakeTime;
    DigitUnitFrame *epShakeTimeVal;
    QLabel *epBlock2Time;
    DigitUnitFrame *epBlock2TimeVal;
    QLabel *epShaker1Volt;
    DigitUnitFrame *epShaker1VoltVal;
    QLabel *epShaker1Freq;
    DigitUnitFrame *epShaker1FreqVal;
    QLabel *epShaker2Volt;
    DigitUnitFrame *epShaker2VoltVal;
    QLabel *epShaker2Freq;
    DigitUnitFrame *epShaker2FreqVal;
    QLabel *epShaker3Volt;
    DigitUnitFrame *epShaker3VoltVal;
    QLabel *epShaker3Freq;
    DigitUnitFrame *epShaker3FreqVal;
    QLabel *epStopRatio;
    DigitUnitFrame *epStopRatioVal;
    QPushButton *motorUp;
    QPushButton *unLoadCylinder;
    QPushButton *motorDown;
    //other parameter
    QGroupBox *groupBox;
    QLabel *opRunTime;
    QSpinBox *opRunTimeVal;
    QLabel *opLanguage;
    QComboBox *opLanguageVal;
    QLabel *opImageSave;
    QPushButton *opImageSaveVal;
    QLabel *opSaveDir;
    QLineEdit *opSaveDirVal;
    QPushButton *opChoose;
    QLabel *opSaveDays;
    QLineEdit *opSaveDaysVal;


signals:


private:
    void RecipeWidget();
    void IdentifyParaWidget();
    void CameraParaWidget();
    void MachineCtrlWidget();
    void ElectricParaWidget();
    void OtherParaWidget();

    void ReadSettingFile(const QString&);
    void Write2SettingFile(const QString&);
    void LoadRecipeName();
    bool TestContainRecipe(const QString&);
    bool CheckRecipeName();
    void LoadRecipeParameter();


private:
    QString _recipeBtnQSS;
    QFont   _fontYahei15;

    QWidget *_recipeWidget;
    QWidget *_identifyParaWidget;
    QWidget *_cameraParaWidget;
    QWidget *_machineCtrlWidget;
    QWidget *_electricParaWidget;
    QWidget *_otherParaWidget;



};

#endif // SETUPWIDGET_H
