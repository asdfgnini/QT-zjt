#ifndef DECODE_H
#define DECODE_H

#include <mutex>

extern "C"{
#include "libavcodec/avcodec.h"
}



class Decode
{
public:
    Decode();
    virtual ~Decode();

    bool Open(AVCodecParameters* para); // 打开解码器
    bool Send(AVPacket* pkt); // 发送到解码线程
    AVFrame* Recv(); // 获取解码数据
    void Clear(); // 清理
    void Close(); // 关闭
    void XFreePacket(AVPacket **pkt);
    void XFreeFrame(AVFrame **frame);


    bool m_isAudio = false; // 是否为音频的标志位
    long long pts = 0; // 当前解码到的pts（新添加，为了音视频同步）


private:

    AVCodecContext *m_VCodecCtx = 0;
    std::mutex m_mutex;

};

#endif // DECODE_H
