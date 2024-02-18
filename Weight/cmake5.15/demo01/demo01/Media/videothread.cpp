#include "videothread.h"
#include <QDebug>
VideoThread::VideoThread()
{

}

VideoThread::~VideoThread()
{

}

bool VideoThread::RepaintPts(AVPacket *pkt, long long seekpts)
{
    vmux.lock();
    bool re = decode->Send(pkt);
    if (!re)
    {
        vmux.unlock();
        return true; //表示结束解码
    }
    AVFrame *frame = decode->Recv();
    if (!frame)
    {
        vmux.unlock();
        return false;
    }
    //到达位置
    if (decode->pts >= seekpts)
    {
        if(call)
            call->Repaint(frame);
        vmux.unlock();
        return true;
    }
    decode->XFreeFrame(&frame);
    vmux.unlock();
    return false;

}

bool VideoThread::Open(AVCodecParameters *para, VideoCall *call, int width, int height)
{
    if (!para)return false;
    Clear();

    vmux.lock();
    synpts = 0;
    //初始化显示窗口
    this->call = call;
    if (call)
    {
        call->Init(width, height);
    }
    vmux.unlock();
    int re = true;
    if (!decode->Open(para))
    {
        qDebug() << "video Decode open failed!";
        re = false;
    }

    qDebug() << "VideoThread::Open :" << re;
    return re;
}

void VideoThread::run()
{
    while (!isExit)
    {
        vmux.lock();
        if (this->isPause)
        {
            vmux.unlock();
            msleep(5);
            continue;
        }
        //cout << "synpts = " << synpts << " dpts =" << decode->pts << endl;
        //音视频同步
        if (synpts > 0 && synpts < decode->pts)
        {
            vmux.unlock();
            msleep(1);
            continue;
        }

        AVPacket *pkt = Pop();
        bool re = decode->Send(pkt);
        if (!re)
        {
            vmux.unlock();
            msleep(1);
            continue;
        }
        //一次send 多次recv
        while (!isExit)
        {
            AVFrame * frame = decode->Recv();
            if (!frame)break;
            //显示视频
            if (call)
            {
                call->Repaint(frame);
            }

        }
        vmux.unlock();
    }

}


void VideoThread::SetPause(bool isPause)
{
    vmux.lock();
    this->isPause = isPause;
    vmux.unlock();

}
