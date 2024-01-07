#include "worker.h"

#include <QDebug>
#include <QThread>

extern "C"{
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}


Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::on_doSomething(Media *media)
{
    qDebug() << "I'm working in thread:" << QThread::currentThreadId();
    if(media->is_FormatNULL() == true)
    {
        qDebug() << "Please open video file first";
        return;
    }
    AVPacket *packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    AVFrame *rgbframe = av_frame_alloc();
    struct SwsContext* img_ctx;
    img_ctx = sws_getContext(media->Get_VideoDecodec()->width,
                             media->Get_VideoDecodec()->height,
                             media->Get_VideoDecodec()->pix_fmt,
                             media->Get_VideoDecodec()->width,
                             media->Get_VideoDecodec()->height,
                             AV_PIX_FMT_RGB32,
                             SWS_BICUBIC,NULL,NULL,NULL);
    int numbytes = av_image_get_buffer_size(AV_PIX_FMT_RGB32,media->Get_VideoDecodec()->width,media->Get_VideoDecodec()->height,1);
    unsigned char* out_buffer = (unsigned char*)av_malloc(numbytes*sizeof(unsigned char));
    int res = av_image_fill_arrays(rgbframe->data,
                                   rgbframe->linesize,
                                   out_buffer,AV_PIX_FMT_RGB32,
                                   media->Get_VideoDecodec()->width,
                                   media->Get_VideoDecodec()->height,1);
    if(res < 0)
    {
        qDebug() << "Fill arrays filed";
        return;
    }

    while(av_read_frame(media->Get_format(),packet) >= 0)
    {
        if (QThread::currentThread()->isInterruptionRequested())
        {
            media->Close();
            av_packet_free(&packet);
            av_frame_free(&frame);
            av_frame_free(&rgbframe);
            qDebug() << "OK1";
            return;
        }
        if(packet->stream_index == media->Get_Videonum())
        {
            if(avcodec_send_packet(media->Get_VideoDecodec(),packet) >= 0)
            {
                int ret = 0;
                while((ret = avcodec_receive_frame(media->Get_VideoDecodec(),frame)) >= 0)
                {
                    if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                    {
                        return;
                    }
                    else if(ret < 0)
                    {
                        qDebug() << "ERROR furing Decoding";
                        exit(-1);
                    }
                    sws_scale(img_ctx,
                              frame->data,frame->linesize,
                              0,media->Get_VideoDecodec()->height,
                              rgbframe->data,rgbframe->linesize);
                    QImage img(out_buffer,
                               media->Get_VideoDecodec()->width,media->Get_VideoDecodec()->height,
                               QImage::Format_RGB32);
                    emit resultReady(img);
                    QThread::msleep(24);
                }
            }
        }
        av_packet_unref(packet);
    }
    qDebug()<<"All video play done";
    av_packet_free(&packet);
    av_frame_free(&frame);
    av_frame_free(&rgbframe);
    // emit resultReady();

}




/******************************************************************/
/******************************************************************/
/******************************************************************/

Controller::Controller(QObject *parent) : QObject(parent)
{
    qDebug() << "Controller's thread is :" << QThread::currentThreadId();

    m_worker = new Worker();
    m_worker->moveToThread(&m_workThread);

    connect(this, &Controller::startRunning, m_worker, &Worker::on_doSomething);
    connect(&m_workThread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(m_worker, &Worker::resultReady, this, &Controller::on_receivResult);

    m_workThread.start();
}

Controller::~Controller()
{
    m_workThread.quit();
    m_workThread.wait();
}

void Controller::start(Media *media)
{
    emit startRunning(media);
}

void Controller::stop()
{
    if(m_workThread.isRunning())
    {
        m_workThread.requestInterruption();
        m_workThread.quit();
        m_workThread.wait(100);
    }
    img.fill(Qt::black);

    emit send_IMG(img);
}

void Controller::on_receivResult(const QImage &img)
{
    emit send_IMG(img);
}
