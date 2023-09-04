#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QDebug>
#include <QIcon>
#include <QStackedWidget>
#include <QDialog>

#include "mainwidget.h"
#include "setupwidget.h"

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
    QAction     *minWin;
    QAction     *closeProg;
    QStackedWidget   *stackedWidget;
    MainWidget    *mainWidget;
    SetupWidget      *setupWidget;
    QDialog     *loginDialog;


public slots:
    void userLoginToggled(bool);
    void setUpTriggerd();
    void runProgToggled(bool);
    void minWinTriggerd();


};
#endif // MAINWINDOW_H
