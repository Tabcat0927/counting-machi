#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QDebug>
#include <QIcon>
#include <QStackedWidget>
#include <QDialog>
#include <QTextCodec>
#include <QDebug>
#include <QThread>

#include "xvlog.h"
#include "xvlogwidget.h"
#include "countingprocess.h"
#include "CountGrain.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void CreateToolBar();
    void LoginWidget();

public:
    QToolBar    *toolBar;
    QAction     *userLogin;
    QAction     *setUp;
    QAction     *runProg;
    QAction     *mainWin;
    QAction     *logAction;
    QAction     *closeProg;
    QStackedWidget   *stackedWidget;
//    MainWidget    *mainWidget;
//    SetupWidget      *setupWidget;
    QDialog     *loginDialog;
    XVLogWidget   *logWidget;
    CountingProcess *cntProc;

private:
    QThread   countThread;

signals:


public slots:
    void userLoginToggled(bool);
    void setUpTriggerd();
    void runProgToggled(bool);
    void minWinTriggerd();
    void logActionTriggered();
    void SlotShowImage(QImage);
    void SlotStudy(QVector<XVRegion>);
    int GetXVRegionArea(XVRegion&);
    float GetXVRegionRadius(XVRegion&);

};
#endif // MAINWINDOW_H
