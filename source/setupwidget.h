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

class SetupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetupWidget(QWidget *parent = nullptr);

    void CreateUi();

public:
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
    QLineEdit *thresholdVal1;
    QLabel *signTo;
    QLineEdit *thresholdVal2;
    QLabel *preprocLabel;
    QComboBox *preprocType;
    QLabel *operatorSize;
    QLineEdit *operatorSizeVal;
    QLabel *areaSetLabel;
    QLineEdit *areaSetVal1;
    QLabel *signTo1;
    QLineEdit *areaSetVal2;
    QLabel *radSetLabel;
    QLineEdit *radSetVal1;
    QLabel *signTo2;
    QLineEdit *radSetVal2;
    QLabel *fillSetLabel;
    QLineEdit *fillSetVal1;
    QLabel *signTo3;
    QLineEdit *fillSetVal2;
    QLabel *brokenAreaSetLabel;
    QLineEdit *brokenAreaSetVal1;
    QLabel *signTo4;
    QLineEdit *brokenAreaSetVal2;
    QLabel *brokenRadSetLabel;
    QLineEdit *brokenRadSetVal1;
    QLabel *signTo5;
    QLineEdit *brokenRadSetVal2;
    QLabel *remnentAlertLabel;
    QLineEdit *remnentAlertVal;
    //camera parameter
    QLabel *lineFreqLabel;
    QSpinBox *lineFreqVal;
    QLabel *gainLabel;
    QSpinBox *gainVal;
    QLabel *expoTimeLabel;
    QDoubleSpinBox *expoTimeVal;
    QLabel *plcIpLabel;
    QLineEdit *plcIpVal;
    QLabel *rtQtyAddrLabel;
    QLabel *D1;
    QLineEdit *rtQtyAddrVal;
    QLabel *aQtyAddrLabel;
    QLabel *D2;
    QLineEdit *aQtyAddrVal;
    QLabel *coorXAddrLabel;
    QLabel *D3;
    QLineEdit *coorXAddrVal;
    QLabel *coorYAddrLabel;
    QLabel *D4;
    QLineEdit *coorYAddrVal;
    QLabel *fullAddrLabel;
    QLabel *M1;
    QLineEdit *fullAddrVal;
    QLabel *flawAddrLabel;
    QLabel *M2;
    QLineEdit *flawAddrVal;
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
    QLineEdit *epCutTimeVal;
    QLabel *epDropDelay;
    QLineEdit *epDropDelayVal;
    QLabel *epFillTime;
    QLineEdit *epFillTimeVal;
    QLabel *epChangeTime;
    QLineEdit *epChangeTimeVal;
    QLabel *epFlawKickTime;
    QLineEdit *epFlawKickTimeVal;
    QLabel *epFlawKickDelay;
    QLineEdit *epFlawKickDelayVal;
    QLabel *epShakeTime;
    QLineEdit *epShakeTimeVal;
    QLabel *epBlock2Time;
    QLineEdit *epBlock2TimeVal;
    QLabel *epShaker1Volt;
    QLineEdit *epShaker1VoltVal;
    QLabel *epShaker1Freq;
    QLineEdit *epShaker1FreqVal;
    QLabel *epShaker2Volt;
    QLineEdit *epShaker2VoltVal;
    QLabel *epShaker2Freq;
    QLineEdit *epShaker2FreqVal;
    QLabel *epShaker3Volt;
    QLineEdit *epShaker3VoltVal;
    QLabel *epShaker3Freq;
    QLineEdit *epShaker3FreqVal;
    QLabel *epShakerRadio;
    QLineEdit *epShakerRadioVal;
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


private:
    QString _recipeBtnQSS;

    QWidget *_recipeWidget;
    QWidget *_identifyParaWidget;
    QWidget *_cameraParaWidget;
    QWidget *_machineCtrlWidget;
    QWidget *_electricParaWidget;
    QWidget *_otherParaWidget;



};

#endif // SETUPWIDGET_H
