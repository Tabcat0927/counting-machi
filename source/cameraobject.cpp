#include "cameraobject.h"

CameraObject::CameraObject(QObject *parent) : QObject(parent)
{
    isConnected = false;
    CSystem &systemObj = CSystem::getInstance();

    if(!systemObj.discovery(cameraList)){
        Log::Instance()->writeWarn("discovery function failed");
    }
    else{
        if(cameraList.size() < 1){
            Log::Instance()->writeWarn("无可连接相机");
        }
        else{
            cameraPtr = cameraList[0];
            if(!cameraPtr->connect()){
                Log::Instance()->writeWarn("相机连接失败");
            }
            else isConnected = true;
            qDebug() << "connectedskdkjdf";
            qDebug() << isConnected;
        }
    }

    QTimer *timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &CameraObject::CheckConnected);
    timer1->start(3000);
}

void CameraObject::FrameCallback(const CFrame& frame)
{
    CFrameInfo frameInfo;
    frameInfo.m_nWidth = frame.getImageWidth();
    frameInfo.m_nHeight = frame.getImageHeight();
    frameInfo.m_nBufferSize = frame.getImageSize();
    frameInfo.m_nPaddingX = frame.getImagePadddingX();
    frameInfo.m_nPaddingY = frame.getImagePadddingY();
    frameInfo.m_ePixelType = frame.getImagePixelFormat();
    frameInfo.m_pImageBuf = (BYTE *)malloc(sizeof(BYTE) * frameInfo.m_nBufferSize);
    frameInfo.m_nTimeStamp = frame.getImageTimeStamp();

    if(frameInfo.m_pImageBuf == nullptr) return;
    memcpy(frameInfo.m_pImageBuf, frame.getImage(), frame.getImageSize());
    if (frameQueue.size() > 16){
        CFrameInfo frameOld;
        frameQueue.get(frameOld);
        free(frameOld.m_pImageBuf);
        qDebug() << "images more than 16";
    }
    frameQueue.push_back(frameInfo);
}

void CameraObject::CheckConnected()
{
    qDebug() << "camera";
    if(isConnected && cameraPtr->isConnected()) return;

    CSystem &systemObj = CSystem::getInstance();
    if(!systemObj.discovery(cameraList)){
        Log::Instance()->writeWarn("未发现相机");
        isConnected = false;
        return;
    }
    cameraPtr = cameraList[0];
    if(!cameraPtr->connect()){
        Log::Instance()->writeWarn("相机连接失败");
        isConnected = false;
        return;
    }
    if(cameraPtr->isConnected()){
        Log::Instance()->writeWarn("相机连接成功");
        isConnected = true;
    }
}

void CameraObject::AcquireImages()
{
    qDebug() << "acquire images";
    if(streamSource == nullptr){
        streamSource = CSystem::getInstance().createStreamSource(cameraPtr);
    }
    if(streamSource == nullptr){
        Log::Instance()->writeWarn("create camera stream failure");
        return;
    }
    if(streamSource->isGrabbing()) return;
    if(!streamSource->attachGrabbing(IStreamSource::Proc(&CameraObject::FrameCallback, this))){
        Log::Instance()->writeWarn("register grab callback failure");
        return;
    }
    if(!streamSource->startGrabbing()){
        Log::Instance()->writeWarn("camera取图失败");
        return;
    }
}

void CameraObject::StopAcquireImage()
{
    if(streamSource == nullptr) return;
    if(streamSource->isGrabbing()){
        streamSource->stopGrabbing();
    }

}
