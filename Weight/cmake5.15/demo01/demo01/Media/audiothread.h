#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include "decodethread.h"
#include "resample.h"
#include "audioplay.h"

class AudioThread:public DecodeThread
{
public:
    AudioThread();
    virtual ~AudioThread();


    //打开，不管成功与否都清理
    virtual bool Open(AVCodecParameters *para,int sampleRate,int channels);

    //停止线程，清理资源
    virtual void Close();

    virtual void Clear();
    void run();

    void SetPause(bool isPause);
    bool isPause = false;
    //当前音频播放的pts
    long long pts = 0;
protected:
    std::mutex amux;
    AudioPlay *ap = 0;
    XResample *res = 0;
};

#endif // AUDIOTHREAD_H
