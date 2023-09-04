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

#include "visiongraph.h"

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
    VisionGraph *vgShowImage;
    QLabel *companyName;
    QLabel *curQtyText;
    QLabel *curQtyVal;
    QLabel *curQtyUnit;
    QLabel *aBtlQtyText;
    QLabel *aBtlQtyVal;
    QLabel *aBtlQtyUnit;
    QLabel *cntSpdText;
    QLabel *cntSpdVal;
    QLabel *cntSpdUnit;
    QLabel *fillSpdText;
    QLabel *fillSpdVal;
    QLabel *fillSpdUnit;
    QLabel *fillQtyText;
    QLabel *fillQtyVal;
    QLabel *fillQtyUnit;
    QPushButton *clrBtn1;
    QLabel *haveBtlText;
    QLabel *exsWarnText;

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
    QLabel *shaker1Val;
    QLabel *shaker2Val;
    QLabel *shaker3Val;


private:
    QFont       _fontYahei15;
    QString     _shakerQSS;
    QWidget     *_displayWidget;
    QGroupBox     *_statusWidget;
    QGroupBox     *_controlWidget;


signals:

};

#endif // CENTRALWIDGET_H
