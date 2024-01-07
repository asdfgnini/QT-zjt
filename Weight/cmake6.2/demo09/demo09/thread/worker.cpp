#include "worker.h"

#include <QDebug>
#include <QThread>

extern "C"{
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
}


Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::on_doSomething(Media *media,unsigned char* out_buffer)
{
    qDebug() << "I'm working in thread:" << QThread::currentThreadId();
    if(media->is_FormatNULL() == true)
    {
        qDebug() << "Please open video file first";
        return;
    }
    AVPacket *packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
     bool isfirst = true;
    int numbytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P,media->Get_VideoDecodec()->width,media->Get_VideoDecodec()->height,1);
    out_buffer = (unsigned char*)av_malloc(numbytes*sizeof(unsigned char));


    while(av_read_frame(media->Get_format(),packet) >= 0)
    {
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

                    if(isfirst)
                    {
                        isfirst = false;
                        emit resultReady(out_buffer,media->Get_VideoDecodec()->width,media->Get_VideoDecodec()->height);
                    }


                    int bytes = 0;
                    for(int i = 0;i < media->Get_VideoDecodec()->height;i++)
                    {
                        memcpy(out_buffer+bytes,frame->data[0]+frame->linesize[0]*i,media->Get_VideoDecodec()->width);
                        bytes += media->Get_VideoDecodec()->width;
                    }
                    int u = media->Get_VideoDecodec()->height >> 1;
                    for(int i = 0;i < u;i++)
                    {
                        memcpy(out_buffer + bytes,frame->data[1]+frame->linesize[1]*i,media->Get_VideoDecodec()->width/2);
                        bytes += media->Get_VideoDecodec()->width / 2;
                    }
                    for(int i = 0;i < u;i++)
                    {
                        memcpy(out_buffer+bytes,frame->data[2]+frame->linesize[2]*i,media->Get_VideoDecodec()->width/2);
                        bytes += media->Get_VideoDecodec()->width/2;
                    }
                    emit worker_new_frame();

                    QThread::msleep(24);
                }
            }
        }
        av_packet_unref(packet);
    }
    qDebug()<<"All video play done";
    av_packet_free(&packet);
    av_frame_free(&frame);
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
    connect(m_worker,&Worker::worker_new_frame,this,&Controller::on_newframe);
    m_workThread.start();
}

Controller::~Controller()
{
    m_workThread.quit();
    m_workThread.wait();
}

void Controller::start(Media *media)
{
    emit startRunning(media,out_buffer);
}

void Controller::on_receivResult(unsigned char* p,int w,int h)
{
    emit send_IMG(p,w,h);
}

void Controller::on_newframe()
{
    emit newframe();
}
