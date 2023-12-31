﻿#ifndef COUNTINGPROCESS_H
#define COUNTINGPROCESS_H

#include <QObject>
#include <QDir>
#include <QImage>
#include <QApplication>
#include <QDebug>
#include <QElapsedTimer>
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QMutexLocker>
#include <QMutex>

#include "BlobAnalysis.h"
#include "CountGrain.h"
#include "Preprocess.h"
#include "setupwidget.h"
#include "mainwidget.h"
#include "xvlogwidget.h"
#include "modbus.h"
#include "cameraobject.h"


using namespace XVL;

class CountingProcess : public QObject
{
    Q_OBJECT
public:
    explicit CountingProcess(MainWidget *mw, SetupWidget *sw);
    ~CountingProcess();

    void Sleep(int);
    int GetXVRegionArea(XVRegion&);
    float GetXVRegionRadius(XVRegion&);

public:

    MainWidget    *mw;
    SetupWidget   *sw;
    int           showImageNum;
    int           showImageCnt;
    int           grainCnt;
    int           oneBottleNum;
    int           cntSpeed;
    int           fillBottleSpeed;
    int           filledCnt;
    bool          haveBottle;
    bool          excessWarn;
    bool          isFlaw;
    bool          isBottleFull;
    bool          isDoubleRemove;
    bool          isCameraConnect;
    bool          isCountStop;
    bool          beginStudy;
    bool          isModbusConnect;
    int           tubeCnt[8];
    int           tubeEdge[9];

    QElapsedTimer timerSecond;
    QElapsedTimer timerMinute;
    QElapsedTimer timerRun;
    QVector<XVRegion> studyRegion;

    CameraObject  *camera;

public slots:
    void Count();
    void SlotShowImage(QImage&);
    void SlotStudy();

signals:
    void SignalShowImage(QImage);
    void SignalStudy(QVector<XVRegion>);
    void SignalCountChanged(int, int, int, int);

private:
    XVImage        _imageUp, _imageDown;
    int            wid, hei;
    QImage         in_img;
    vector<XVImage> _vecImage;


private:
    void CreateXVImage(int, int, uchar*, XVImage*);
    bool QImgToXVImg(QImage&, XVImage&);
    bool XVImgToQImg(XVImage&, QImage&);
    void CreateBlankXVImage(int, int, XVImage*);
    bool CopyXVImage(XVImage&, XVImage*);
    void PaintXVRegion(XVRegion&, XVImage&, int);
    void ProcessTiledImage(XVImage&, XVSplitRegionToBlobsOut*);
    void DealwithBlobs(XVSplitRegionToBlobsOut&);
    bool TestRegionIntersection(XVRegion&, XVRegion&);
    void KickoutDouble();
    void DrawMainWindowImage();
    XVImage CropXVImage(XVImage&);
    bool MirrorXVImage(XVImage&, XVImage*);
    void TileXVImage(XVImage&, XVImage&, XVImage*);
    XVRegion CreateRectXVRegion(int, int);
    void CountUndCommunication(XVRegion&);
    void CommunicateWithPLC();
    void HandleAbnormal(int, int);
    bool BolbInNormalRange(int, int);
    bool BolbInFlawRange(int, int);    

};

#endif // COUNTINGPROCESS_H
