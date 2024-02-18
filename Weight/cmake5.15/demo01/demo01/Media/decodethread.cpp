#include "decodethread.h"

DecodeThread::DecodeThread(QObject *parent)
    : QThread{parent}
{
    // 打开解码器
    if (!decode) decode = new Decode();
}

DecodeThread::~DecodeThread()
{
    // 等待线程退出
    isExit = true;
    wait();
}

void DecodeThread::Push(AVPacket *pkt)
{
    if (!pkt)return;
    // 阻塞
    while (!isExit)
    {
        mux.lock();
        if (packs.size() < maxList)
        {
            packs.push_back(pkt);
            mux.unlock();
            break;
        }
        mux.unlock();
        msleep(1);
    }
}

void DecodeThread::Clear()
{
    mux.lock();
    decode->Clear();
    while (!packs.empty())
    {
        AVPacket *pkt = packs.front();
        decode->XFreePacket(&pkt);
        packs.pop_front();
    }

    mux.unlock();

}

void DecodeThread::Close()
{
    Clear();

    // 等待线程退出
    isExit = true;
    wait();
    decode->Close();

    mux.lock();
    delete decode;
    decode = NULL;
    mux.unlock();
}

AVPacket *DecodeThread::Pop()
{
    mux.lock();
    if (packs.empty())
    {
        mux.unlock();
        return NULL;
    }
    AVPacket *pkt = packs.front();
    packs.pop_front();
    mux.unlock();
    return pkt;
}
