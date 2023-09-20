#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QFrame>
#include <QGroupBox>
#include <QProgressBar>
#include <QSettings>

#include "visiongraph.h"
#include "digitunitframe.h"

#pragma execution_character_set("utf-8")

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

    void CreateUi();
    void DisplayImages();
    void RunStatusWidget();
    void RunControlWidget();

public:
    QLabel *curRecipe;
    QLabel *curRecipeVal;
    VisionGraph *vgShowImage;
    QLabel *companyName;
    QLabel *curQtyText;
    DigitUnitFrame *curQtyFrame;
    QLabel *aBtlQtyText;
    DigitUnitFrame *aBtlQtyFrame;
    QLabel *cntSpdText;
    DigitUnitFrame *cntSpdFrame;
    QLabel *fillSpdText;
    DigitUnitFrame *fillSpdFrame;
    QLabel *fillQtyText;
    DigitUnitFrame *fillQtyFrame;
    QPushButton *clrBtn1;
    QPushButton *clrBtn2;
    QLabel *haveBtlText;
    QLabel *exsWarnText;
    QProgressBar *progBar;

    QPushButton *shaker1Inc;
    QPushButton *shaker1Dec;
    QPushButton *shaker2Inc;
    QPushButton *shaker2Dec;
    QPushButton *shaker3Inc;
    QPushButton *shaker3Dec;
    QPushButton *ctrlStart;
    QPushButton *ctrlStop;
    QPushButton *ctrlClr;
    QPushButton *ctrlStudy;
    QPushButton *ctrlSave;
    QPushButton *ctrlBelt;
    DigitUnitFrame *shaker1Val;
    DigitUnitFrame *shaker2Val;
    DigitUnitFrame *shaker3Val;

    bool        isStudy;


private:
    QFont       _fontYahei15;
    QString     _shakerQSS;
    QWidget     *_displayWidget;
    QGroupBox     *_statusWidget;
    QGroupBox     *_controlWidget;

private:
    void SetStyleSheet();
    void ReadSysSettingFile(const QString&);

signals:

public slots:
    void CtrlStudyToggled(bool);
};

#endif // CENTRALWIDGET_H
