#include "demuxthread.h"
#include <QDebug>


DemuxThread::DemuxThread()
{

}

DemuxThread::~DemuxThread()
{
    isExit = true;
    wait();
}

void DemuxThread::run()
{
    while (!isExit)
    {
        mux.lock();
        if (isPause)
        {
            mux.unlock();
            msleep(5);
            continue;
        }
        if (!demux)
        {
            mux.unlock();
            msleep(5);
            continue;
        }


        //音视频同步
        if (vt && at)
        {
            pts = at->pts;
            vt->synpts = at->pts;
        }


        AVPacket *pkt = demux->read();
        if (!pkt)
        {
            mux.unlock();
            msleep(5);
            continue;
        }
        //判断数据是音频
        if (demux->isAudio(pkt))
        {
            //while (at->IsFull())
            {
            //	vt->synpts = at->pts;
            }
            if(at)at->Push(pkt);
        }
        else //视频
        {
            //while (vt->IsFull())
            //{
            //	vt->synpts = at->pts;
            //}
            if (vt)vt->Push(pkt);
        }
        mux.unlock();
        msleep(1);
    }

}

bool DemuxThread::Open(const char *url, VideoCall *call)
{
    if (url == 0 || url[0] == '\0')
        return false;

    mux.lock();
    if (!demux) demux = new Demux();
    if (!vt) vt = new VideoThread();
    if (!at) at = new AudioThread();

    //打开解封装
    bool re = demux->open(url);
    if (!re)
    {
        mux.unlock();
        qDebug() << "demux->Open(url) failed!";
        return false;
    }
    //打开视频解码器和处理线程
    if (!vt->Open(demux->copyVPara(), call, demux->width, demux->height))
    {
        re = false;
        qDebug() << "vt->Open failed!";
    }
    //打开音频解码器和处理线程
    if (!at->Open(demux->copyAPara(), demux->sampleRate, demux->channels))
    {
        re = false;
        qDebug() << "at->Open failed!";
    }
    totalMs = demux->totalMs;
    mux.unlock();

    qDebug() << "XDemuxThread::Open " << re;
    return re;

}

void DemuxThread::Start()
{
    mux.lock();
    if (!demux) demux = new Demux();
    if (!vt) vt = new VideoThread();
    if (!at) at = new AudioThread();
    //启动当前线程
    QThread::start();
    if (vt)vt->start();
    if (at)at->start();
    mux.unlock();

}

void DemuxThread::Close()
{
    isExit = true;
    wait();
    if (vt) vt->Close();
    if (at) at->Close();
    mux.lock();
    delete vt;
    delete at;
    vt = NULL;
    at = NULL;
    mux.unlock();

}

void DemuxThread::Clear()
{
    mux.lock();
    if (demux)demux->clear();
    if (vt) vt->Clear();
    if (at) at->Clear();
    mux.unlock();
}

void DemuxThread::Seek(double pos)
{
    //清理缓存
    Clear();

    mux.lock();
    bool status = this->isPause;
    mux.unlock();
    //暂停
    SetPause(true);

    mux.lock();
    if (demux)
        demux->seek(pos);
    //实际要显示的位置pts
    long long seekPts = pos*demux->totalMs;
    while (!isExit)
    {
        AVPacket *pkt = demux->readVideo();
        if (!pkt) break;
        //如果解码到seekPts
        if (vt->RepaintPts(pkt, seekPts))
        {
            this->pts = seekPts;
            break;
        }
        //bool re = vt->decode->Send(pkt);
        //if (!re) break;
        //AVFrame *frame = vt->decode->Recv();
        //if (!frame) continue;
        ////到达位置
        //if (frame->pts >= seekPts)
        //{
        //	this->pts = frame->pts;
        //	vt->call->Repaint(frame);
        //	break;
        //}
        //av_frame_free(&frame);
    }

    mux.unlock();

    //seek是非暂停状态
    if(!status)
        SetPause(false);

}

void DemuxThread::SetPause(bool isPause)
{
    mux.lock();
    this->isPause = isPause;
    if (at) at->SetPause(isPause);
    if (vt) vt->SetPause(isPause);
    mux.unlock();
}
