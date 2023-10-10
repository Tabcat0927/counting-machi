#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QThread>

#include "GenICam/System.h"
#include "GenICam/Camera.h"
#include "GenICam/StreamSource.h"
#include "log.h"
#include "MessageQue.h"

using namespace Dahua::GenICam;
using namespace Dahua::Infra;

class CFrameInfo : public Dahua::Memory::CBlock
{
public:
    CFrameInfo()
    {
        m_pImageBuf = NULL;
        m_nBufferSize = 0;
        m_nWidth = 0;
        m_nHeight = 0;
        m_ePixelType = Dahua::GenICam::gvspPixelMono8;
        m_nPaddingX = 0;
        m_nPaddingY = 0;
        m_nTimeStamp = 0;
    }

    ~CFrameInfo()
    {
    }

public:
    BYTE		*m_pImageBuf;
    int			m_nBufferSize;
    int			m_nWidth;
    int			m_nHeight;
    Dahua::GenICam::EPixelType	m_ePixelType;
    int			m_nPaddingX;
    int			m_nPaddingY;
    uint64_t	m_nTimeStamp;
};

class CameraObject : public QObject
{
    Q_OBJECT
public:
    explicit CameraObject(QObject *parent = nullptr);

    void FrameCallback(const CFrame&);
    void AcquireImages();
    void StopAcquireImage();

signals:

public:
    TVector<ICameraPtr> cameraList;
    IStreamSourcePtr    streamSource;
    TMessageQue<CFrameInfo>		frameQueue;
    ICameraPtr          cameraPtr;
    bool                isConnected;

public slots:
    void CheckConnected();
};

#endif // CAMERA_H
