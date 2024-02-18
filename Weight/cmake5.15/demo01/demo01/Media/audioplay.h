#ifndef AUDIOPLAY_H
#define AUDIOPLAY_H


class AudioPlay
{

public:
    AudioPlay();
    virtual ~AudioPlay();

    virtual bool Open() = 0; // 打开音频播放
    virtual void Close() = 0;
    virtual void Clear() = 0;
    virtual long long GetNoPlayMs() = 0; // 返回缓冲中还没有播放的时间（毫秒）
    virtual bool Write(const unsigned char *data, int datasize) = 0; // 播放音频
    virtual int GetFree() = 0;
    virtual void SetPause(bool isPause) = 0;
    static AudioPlay* Get();

    int sampleRate = 44100;
    int sampleSize = 16;
    int channels = 2;
};






















#endif // AUDIOPLAY_H
