#include "countingprocess.h"

extern modbus_t *ctx;
extern QMutex   mutexModbus;

CountingProcess::CountingProcess(MainWidget *mw, SetupWidget *sw) : mw(mw), sw(sw)
{
    grainCnt = 0;
    oneBottleNum = mw->aBtlQtyFrame->value();
    cntSpeed = 0;
    fillBottleSpeed = 0;
    filledCnt = 0;
    showImageCnt = 0;
    showImageNum = 6;
    haveBottle = false;
    excessWarn = false;
    isFlaw = false;
    isBottleFull = false;
    isDoubleRemove = false;
    isCameraConnect = false;
    isCountStop = true;
    beginStudy = false;
    isModbusConnect = false;
    camera = new CameraObject();

    oneBottleNum = mw->aBtlQtyFrame->value();
    for(int i = 0; i != 8; ++i) tubeCnt[i] = 0;
    for(int i = 0; i != 9; ++i) tubeEdge[i] = 1640 / 8 * i;

//    下面俩会导致QObject::startTimer: Timers cannot be started from another thread
//    不知道为啥，放到mainwindow里，信号和槽不在一个类内可以，后面再研究
//    connect(this, &CountingProcess::SignalShowImage, this, &CountingProcess::SlotShowImage);
//    connect(this, &CountingProcess::SignalStudy, this, &CountingProcess::SlotStudy);

}

CountingProcess::~CountingProcess()
{
    camera->deleteLater();
}

void CountingProcess::Count()
{
    qDebug() << QThread::currentThreadId();
    timerSecond.start();
    timerMinute.start();
    while (!isCountStop){
        timerRun.start();
        XVImage mirrored_image;
        XVImage tiled_image;
        XVSplitRegionToBlobsOut blobs;
        if(mw->testMode->currentIndex() == 0){
            CFrameInfo frame;
            if(camera->frameQueue.get(frame, 50)){
                wid = frame.m_nWidth;
                hei = frame.m_nHeight;
                CreateXVImage(wid, hei, frame.m_pImageBuf, &_imageUp);
                free(frame.m_pImageBuf);
            }
            else{
                Sleep(2);
                continue;
            }
        }
        if(mw->testMode->currentIndex() == 1){
            static int image_cnt = 0;
            QDir imageDir = QDir("111-1");
            QStringList fileName = imageDir.entryList(QDir::Files);
            int image_num = fileName.count();
            QImage image("111-1/" + fileName.at(image_cnt));
            wid = image.width();
            hei = image.height();
            CreateXVImage(wid, hei, image.bits(), &_imageUp);
            ++image_cnt;
            if(image_cnt == image_num) image_cnt = 0;
            Sleep(5);//为什么不暂停，连续运行时内存会猛涨？
        }
        MirrorXVImage(_imageUp, &mirrored_image);
        if(_imageDown.width != wid || _imageDown.height != hei){
            CreateBlankXVImage(wid, hei, &_imageDown);
        }
        TileXVImage(mirrored_image, _imageDown, &tiled_image);
        ProcessTiledImage(tiled_image, &blobs);
        if(blobs.outRegions.size() > 0){
            DrawMainWindowImage();
            DealwithBlobs(blobs);
        }
        else free(_imageUp.data);
        Sleep(10);
    }
}

void CountingProcess::CreateXVImage(int width, int height, uchar *data, XVImage *img)
{
    img->width = width;
    img->height = height;
    img->type = UInt8;
    img->depth = 1;
    img->pitch = (width + 3) / 4 * 4;
    size_t size = width * height * sizeof(uchar);
    img->data = (uchar*)malloc(size);
    memcpy(img->data, data, size);
}

bool CountingProcess::QImgToXVImg(QImage &in, XVImage &out)
{
    if(in.bits() == nullptr)
        return false;
    out.depth = in.depth() / 8;
    out.width = in.width();
    out.height = in.height();
    size_t size = out.width * out.height * out.depth;
    out.type = UInt8;
    out.data = (uchar*)malloc(size);
    out.pitch = (out.width * out.depth * 1 + 3) / 4 * 4;
    memcpy(out.data, in.bits(), size);
    return true;
}

bool CountingProcess::XVImgToQImg(XVImage &in, QImage &out)
{
    QImage::Format format = QImage::Format_Invalid;
    if(in.depth == 1){
        format = QImage::Format_Grayscale8;
    }
    else if(in.depth == 3){
        format = QImage::Format_RGB888;
    }
    if(format  == QImage::Format_Invalid) return false;
    out = QImage(in.data,in.width,in.height,in.pitch,format);
    return true;
}

void CountingProcess::CreateBlankXVImage(int width, int height, XVImage *img)
{
    size_t size = width * height * _imageUp.depth;
    img->data = (uchar*)malloc(size);
    memset(img->data, 255, size);
    img->width = width;
    img->height = height;
    img->type = _imageUp.type;
    img->depth = _imageUp.depth;
    img->pitch = _imageUp.pitch;
}

bool CountingProcess::CopyXVImage(XVImage &img1, XVImage *img2)
{
    if(img1.data == nullptr) return false;
    img2->width = img1.width;
    img2->height = img1.height;
    img2->type = img1.type;
    img2->pitch = img1.pitch;
    img2->depth = img1.depth;
    size_t  size = img1.width * img1.height * img1.depth;
    img2->data = (uchar *)malloc(size);
    if(img2->data){
        memcpy(img2->data, img1.data, size);
        return true;
    }
    return false;
}

void CountingProcess::PaintXVRegion(XVRegion &region, XVImage &image, int val)
{
    XVSetImagePixelsIn set_in;
    XVSetImagePixelsOut set_out;
    set_in.inRoi = region;
    set_in.inImage = &image;
    set_in.inPixel.ch1 = val;
    set_in.inPixel.ch2 = 0;
    set_in.inPixel.ch3 = 0;
    set_in.inPixel.ch4 = 0;

    if(XVSetImagePixels(set_in, set_out) == 0){
        free(image.data);
        XVImage out_image = set_out.outImage;
        CopyXVImage(out_image, &_imageDown);
        free(out_image.data);
    }
}

void CountingProcess::ProcessTiledImage(XVImage &tiled_image, XVSplitRegionToBlobsOut *blobs)
{
    XVRectangleRegionIn rect_in;
    XVRectangleRegionOut rect_out;
    rect_in.inRectangle.origin.x = 0;
    rect_in.inRectangle.origin.y = 0;
    rect_in.inRectangle.width = wid;
    rect_in.inRectangle.height = hei * 2;
    rect_in.inRectangle.angle = 0;
    rect_in.inAlignment.optional = XVOptionalType::NUL;
    rect_in.inFrameWidth = wid;
    rect_in.inFrameHeight = hei * 2;
    XVRectangleRegion(rect_in, rect_out);

    XVThresholdImageToRegionMonoIn thre_in;
    XVThresholdImageToRegionMonoOut thre_out;
    int minThreshold = sw->thresholdVal1->value();
    int maxThreshold = sw->thresholdVal2->value();
    thre_in.inImage = &tiled_image;
    thre_in.inMin = minThreshold;
    thre_in.inMax = maxThreshold;
    thre_in.inAlignment.optional = XVOptionalType::NUL;
    thre_in.inRegion = rect_out.outRegion;
    if(XVThresholdImageToRegionMono(thre_in, thre_out) == 0)
        free(tiled_image.data);

    XVRegionMorphIn morph_in;
    XVRegionMorphOut morph_out;
    morph_in.inRegion = thre_out.outRegion;
    morph_in.inRadiusX = 1;
    morph_in.inRadiusY = 1;
    int index = sw->preprocType->currentIndex();
    switch (index)
    {
    case 0:
        morph_in.inKernel = XVMorphShape::Rect;
        morph_in.inMorphType = XVMorphType::Open;
        XVRegionMorph(morph_in, morph_out);
        break;
    case 1:
        morph_in.inKernel = XVMorphShape::Rect;
        morph_in.inMorphType = XVMorphType::Close;
        XVRegionMorph(morph_in, morph_out);
        break;
    default:break;
    }

    XVFillRegionHolesIn fill_in;
    XVFillRegionHolesOut fill_out;
    fill_in.inRegion = morph_out.outRegion;
    XVFillRegionHoles(fill_in, fill_out);

    XVSplitRegionToBlobsIn split_in;
    split_in.inRegion = fill_out.outRegion;
    XVSplitRegionToBlobs(split_in, *blobs);
}

void CountingProcess::DealwithBlobs(XVSplitRegionToBlobsOut &blobs)
{
    int n_region = blobs.outRegions.size();
    bool is_top_intersection = false;

    for(int i = 0; i != n_region; ++i){
        XVRegion reg = blobs.outRegions.at(i);
        XVRegion rect_reg = CreateRectXVRegion(wid, 1);

        if(TestRegionIntersection(reg, rect_reg)){
            PaintXVRegion(reg, _imageDown, 20);
            is_top_intersection = true;
            continue;
        }
        if(mw->isStudy){
            beginStudy = true;
            studyRegion.append(reg);

            if(studyRegion.count() >= 1100){
                qDebug() << studyRegion.count();
                emit SignalStudy(studyRegion);
            }
        }
        else if(beginStudy && !mw->isStudy && studyRegion.count() < 1100){
            Log::Instance()->writeWarn("学习数据失败, 数据量太少");
            studyRegion.clear();
            beginStudy = false;
        }
        else{
            CountUndCommunication(reg);
            emit SignalCountChanged(grainCnt, cntSpeed, fillBottleSpeed, filledCnt);
            if(grainCnt >= oneBottleNum){
                isBottleFull = true;
                grainCnt = 0;
                ++fillBottleSpeed;
                ++filledCnt;
            }
        }
        if(timerSecond.elapsed() >= 1000){
            cntSpeed = 0;
            timerSecond.start();
        }
        if(timerMinute.elapsed() >= 60000){
            fillBottleSpeed = 0;
            timerMinute.start();
        }
    }
    if(!is_top_intersection){
        _imageDown.width = 0;
        free(_imageDown.data);
    }
    int run_time = sw->opRunTimeVal->value();
    int time = timerMinute.elapsed();
    if(run_time > time)
        Sleep(run_time - time);

}

void CountingProcess::CountUndCommunication(XVRegion &reg)
{
    int n_untop = 0;
    uint16_t row[20] = {0};
    uint16_t column[20] = {0};
    int area = GetXVRegionArea(reg);
    int rad = GetXVRegionRadius(reg);

    if(BolbInNormalRange(area,rad)){
        ++grainCnt;
        ++cntSpeed;
        qDebug() << "grainCnt::::::" << grainCnt;

        XVRegionBoundingRectIn bound_in;
        XVRegionBoundingRectOut bound_out;
        bound_in.inRegion = reg;
        XVRegionBoundingRect(bound_in, bound_out);
        row[n_untop] = bound_out.outCenter.x;
        column[n_untop] = bound_out.outRightDown.y;
        for (int i = 0; i < 8; ++i){
            if(row[n_untop] > tubeEdge[i] && row[n_untop] < tubeEdge[i + 1]){
                tubeCnt[i] ++;
            }
        }
        //n_untop is definitely incorrect,latter to deal with
        n_untop++;
    }
    else HandleAbnormal(area, rad);
    CommunicateWithPLC();
}

void CountingProcess::CommunicateWithPLC()
{
    QMutexLocker locker(&mutexModbus);
    if(!isModbusConnect) return;
    int coor_x = sw->coorXAddrVal->value();
    int coor_y = sw->coorYAddrVal->value();
    int cur_num = sw->rtQtyAddrVal->value();
    int full = sw->fullAddrVal->value();
    int flaw = sw->flawAddrVal->value();
//    modbus_write_registers(ctx, coor_x + n_untop, 1, &row[n_untop]);
//    modbus_write_registers(ctx, coor_y + n_untop, 1, &column[n_untop]);
//    modbus_write_registers(ctx, coor_x + n_untop + 1, 20 - n_untop, &clear[n_untop]);
//    modbus_write_registers(ctx, coor_y + n_untop + 1, 20 - n_untop, &clear[n_untop]);
//    modbus_write_register(ctx, 3, n_untop + 1);
    modbus_write_bit(ctx, 1000, 1);
    modbus_write_register(ctx, cur_num, grainCnt);

    if(isBottleFull) modbus_write_bit(ctx, full, isBottleFull);
    if(isFlaw) modbus_write_bit(ctx, flaw, isFlaw);
    if(isDoubleRemove) modbus_write_bit(ctx, 330, isDoubleRemove);
    //为什么装瓶速度要从PLC读取？
    uint16_t d62;
    modbus_read_registers(ctx, 62, 1, &d62);
    fillBottleSpeed = (int)d62;

    isFlaw = false;
    isBottleFull = false;
    isDoubleRemove =false;
}

void CountingProcess::HandleAbnormal(int area, int rad)
{
    KickoutDouble();
    if(BolbInFlawRange(area, rad)){
        isFlaw = true;
        Log::Instance()->writeWarn("残料警告,面积= " +
        QString::number(area) + "(" +
        QString::number(sw->flawAreaSetVal1->value()) + "," +
        QString::number(sw->flawAreaSetVal2->value())  + ")" + "，半径= " +
        QString::number(rad) + "(" +
        QString::number(sw->flawRadSetVal1->value()) + "," +
        QString::number(sw->flawRadSetVal2->value()) + ")");
    }
    else Log::Instance()->writeWarn("出现未计入数据的阴影，面积= " +
        QString::number(area)+ "(" +
        QString::number(sw->areaSetVal1->value()) + "," +
        QString::number(sw->areaSetVal2->value()) + ")" + "，半径= " +
        QString::number(rad) + "(" +
        QString::number(sw->radSetVal1->value()) + "," +
        QString::number(sw->radSetVal2->value()) + ")");
}

void CountingProcess::KickoutDouble()
{
    int restWarn = sw->remnentAlertVal->value();
    for (int i = 0; i < 9; ++i){
        if(oneBottleNum - grainCnt <= restWarn && tubeCnt[i] > 1){
            isDoubleRemove = true;
            Log::Instance()->writeWarn("剔除警告：第" + QString::number(i + 1) +
                                       "料道出现叠料,数目为：" +
                                       QString::number(tubeCnt[i]) + "粒");
            tubeCnt[i] = 0;
        }
    }
}

bool CountingProcess::BolbInNormalRange(int area, int rad)
{
    if(area < sw->areaSetVal1->value()) return false;
    if(area > sw->areaSetVal2->value()) return false;
    if(rad < sw->radSetVal1->value()) return false;
    if(rad > sw->radSetVal2->value()) return false;
    return true;
}

bool CountingProcess::BolbInFlawRange(int area, int rad)
{
    if(area < sw->flawAreaSetVal1->value()) return false;
    if(area > sw->flawAreaSetVal2->value()) return false;
    if(rad < sw->flawRadSetVal1->value()) return false;
    if(rad > sw->flawRadSetVal2->value()) return false;
    return true;
}

bool CountingProcess::TestRegionIntersection(XVRegion &reg1, XVRegion &reg2)
{
    XVRegionIntersectionIn in;
    XVRegionIntersectionOut out;
    in.inRegion1 = reg1;
    in.inRegion2 = reg2;
    XVRegionIntersection(in, out);

    return out.outRegion.frameWidth > 0 ? true : false;
}

void CountingProcess::DrawMainWindowImage()
{
    XVImgToQImg(_imageUp, in_img);
    static QImage largeImage = QImage(wid, showImageNum * hei, in_img.format());
    QPainter painter(&largeImage);
    if(showImageCnt < showImageNum){
        painter.drawImage(QPoint(0, hei * showImageCnt), in_img);
        free(_imageUp.data);
        ++showImageCnt;
    }
    if(showImageCnt >= showImageNum){
        emit SignalShowImage(largeImage);
        showImageCnt = 0;
    }
}

XVImage CountingProcess::CropXVImage(XVImage &image)
{
    XVRectangleRegionIn crop_region_in;
    XVRectangleRegionOut crop_region_out;
    crop_region_in.inRectangle.origin.x = 0;
    crop_region_in.inRectangle.origin.y = 0;
    crop_region_in.inRectangle.width = wid;
    crop_region_in.inRectangle.height = hei;
    crop_region_in.inRectangle.angle = 0;
    crop_region_in.inAlignment.optional = XVOptionalType::NUL;
    crop_region_in.inFrameWidth = wid;
    crop_region_in.inFrameHeight = hei;
    XVRectangleRegion(crop_region_in, crop_region_out);

    XVCopyAndFillIn copy_in;
    XVCopyAndFillOut copy_out;
    copy_in.inImage = image;
    copy_in.inRoi = crop_region_out.outRegion;
    copy_in.inCopyAndFillType = CopyAndFillType::Copy;
    copy_in.alignment.optional = XVOptionalType::NUL;
    XVCopyAndFill(copy_in, copy_out);
    return copy_out.outImage;
}

bool CountingProcess::MirrorXVImage(XVImage &in, XVImage *out)
{
    XVGeometricTransformationIn tran_in;
    XVGeometricTransformationOut tran_out;
    tran_in.inImage = &in;
    tran_in.inMirrorType = XVMirrorType::VerticalMirror;
    tran_in.inTransformationType = XVTransformationType::Mirror;
    if(XVGeometricTransformation(tran_in, tran_out) == 0){
        *out = tran_out.outImage;
        return true;
    }
    return false;
}

void CountingProcess::TileXVImage(XVImage &in1, XVImage &in2, XVImage *out)
{
    XVTileImageOffsetIn tile_in;
    XVTileImageOffsetOut tile_out;
    tile_in.inImgs.push_back(in1);
    tile_in.inImgs.push_back(in2);
    if(XVTileImageOffset(tile_in, tile_out) == 0){
        *out = tile_out.outImage;
        free(in1.data);
    }
}

XVRegion CountingProcess::CreateRectXVRegion(int width, int height)
{
    XVRectangleRegionIn rect_in;
    XVRectangleRegionOut rect_out;
    rect_in.inRectangle.origin.x = 0;
    rect_in.inRectangle.origin.y = 0;
    rect_in.inRectangle.width = width;
    rect_in.inRectangle.height = height;
    rect_in.inRectangle.angle = 0;
    rect_in.inAlignment.optional = XVOptionalType::NUL;
    rect_in.inFrameWidth = width;
    rect_in.inFrameHeight = height;
    XVRectangleRegion(rect_in, rect_out);

    return rect_out.outRegion;
}

int CountingProcess::GetXVRegionArea(XVRegion &region)
{
    XVRegionAreaIn area_in;
    XVRegionAreaOut area_out;
    area_in.inRegion = region;
    XVRegionArea(area_in, area_out);

    return area_out.outArea;
}

float CountingProcess::GetXVRegionRadius(XVRegion &region)
{
    XVRegionBoundingCircleIn circle_in;
    XVRegionBoundingCircleOut circle_out;
    circle_in.inRegion = region;
    XVRegionBoundingCircle(circle_in, circle_out);

    return circle_out.outCircle.radius;
}

void CountingProcess::Sleep(int t)
{//延时时长实际会多1ms
    QElapsedTimer *timer = new QElapsedTimer();
    timer->start();
    while(!timer->hasExpired(t)){};

}

void CountingProcess::SlotShowImage(QImage &img)
{
    VisionGraph *vg = mw->vgShowImage;
    vg->clearPainter();
    vg->setBkImg(img);
    vg->setViewSize_Fit();
}

void CountingProcess::SlotStudy()
{
    GrainDataLearnIn learnAreaInArea, learnAreaInRadius;
    GrainDataLearnOut learnAreaOut;
    XVRegion region;
    float radius;
    int area;

    for(int i = 0; i < studyRegion.count(); i++){
        region = studyRegion.at(i);
        area = GetXVRegionArea(region);
        radius = GetXVRegionRadius(region);
        double aadd = static_cast<double>(area);
        learnAreaInArea.data.push_back(aadd);
        learnAreaInRadius.data.push_back(radius);
    }

    grainDataLearn(learnAreaInArea, learnAreaOut);
    if(learnAreaOut.GrainDataLearnResult == 1){
        sw->areaSetVal1->setValue((int)learnAreaOut.minThreshold);
        sw->areaSetVal2->setValue((int)learnAreaOut.maxThreshold);
        Log::Instance()->writeInfo("学习算法结果面积最大值 = " + QString("%1").arg(learnAreaOut.maxThreshold));
        Log::Instance()->writeInfo("学习算法结果面积最小值 = " + QString("%1").arg(learnAreaOut.minThreshold));
    }
    else Log::Instance()->writeWarn("学习数据失败");

    grainDataLearn(learnAreaInRadius, learnAreaOut);
    if(learnAreaOut.GrainDataLearnResult == 1){
        sw->radSetVal1->setValue((int)learnAreaOut.minThreshold);
        sw->radSetVal1->setValue((int)learnAreaOut.maxThreshold);
        Log::Instance()->writeInfo("学习算法结果半径最大值 = " + QString("%1").arg(learnAreaOut.minThreshold));
        Log::Instance()->writeInfo("学习算法结果半径最小值 = " + QString("%1").arg(learnAreaOut.maxThreshold));
        Log::Instance()->writeInfo("***********学习成功***********");
    }
    else Log::Instance()->writeWarn("学习数据失败");
    studyRegion.clear();
    mw->ctrlStudy->setChecked(false);
    beginStudy = false;
}

