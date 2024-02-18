#include "audiothread.h"
#include <QDebug>

AudioThread::AudioThread()
{
    if (!res) res = new XResample();
    if (!ap) ap = AudioPlay::Get();

}

AudioThread::~AudioThread()
{
    //等待线程退出
    isExit = true;
    wait();

}

bool AudioThread::Open(AVCodecParameters *para, int sampleRate, int channels)
{
    if (!para)return false;
    Clear();

    amux.lock();
    pts = 0;
    bool re = true;
    if (!res->Open(para, false))
    {
        qDebug() << "XResample open failed!";
        re = false;
    }
    ap->sampleRate = sampleRate;
    ap->channels = channels;
    if (!ap->Open())
    {
        re = false;
        qDebug() << "XAudioPlay open failed!";
    }
    if (!decode->Open(para))
    {
        qDebug() << "audio XDecode open failed!";
        re = false;
    }
    amux.unlock();
    qDebug() << "XAudioThread::Open :" << re;
    return re;

}

void AudioThread::Close()
{
    DecodeThread::Close();
    if (res)
    {
        res->Close();
        amux.lock();
        delete res;
        res = NULL;
        amux.unlock();
    }
    if (ap)
    {
        ap->Close();
        amux.lock();
        ap = NULL;
        amux.unlock();
    }

}

void AudioThread::Clear()
{
    DecodeThread::Clear();
    mux.lock();
    if (ap) ap->Clear();
    mux.unlock();

}

void AudioThread::run()
{
    unsigned char *pcm = new unsigned char[1024 * 1024 * 10];
    while (!isExit)
    {
        amux.lock();
        if (isPause)
        {
            amux.unlock();
            msleep(5);
            continue;
        }

        //没有数据
        //if (packs.empty() || !decode || !res || !ap)
        //{
        //	mux.unlock();
        //	msleep(1);
        //	continue;
        //}

        //AVPacket *pkt = packs.front();
        //packs.pop_front();
        AVPacket *pkt = Pop();
        bool re = decode->Send(pkt);
        if (!re)
        {
            amux.unlock();
            msleep(1);
            continue;
        }
        //一次send 多次recv
        while (!isExit)
        {
            AVFrame * frame = decode->Recv();
            if (!frame) break;

            //减去缓冲中未播放的时间
            pts = decode->pts - ap->GetNoPlayMs();

            //cout << "audio pts = " << pts << endl;

            //重采样
            int size = res->Resample(frame, pcm);
            //播放音频
            while (!isExit)
            {
                if (size <= 0)break;
                //缓冲未播完，空间不够
                if (ap->GetFree() < size || isPause)
                {
                    msleep(1);
                    continue;
                }
                ap->Write(pcm, size);
                break;
            }
        }
        amux.unlock();
    }
    delete []pcm;

}

void AudioThread::SetPause(bool isPause)
{
    amux.lock();
    this->isPause = isPause;
    if (ap)
        ap->SetPause(isPause);
    amux.unlock();
}
