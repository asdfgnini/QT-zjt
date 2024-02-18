#include "decode.h"
#include <QDebug>
Decode::Decode()
{

}

Decode::~Decode()
{

}

bool Decode::Open(AVCodecParameters *para)
{
    if (!para)
    {
        return false;
    }

    Close();

    // 根据传入的para->codec_id找到解码器
    const AVCodec *vcodec = avcodec_find_decoder(para->codec_id);
    if (!vcodec)
    {
        avcodec_parameters_free(&para);
        qDebug() << "can't find the codec id " << para->codec_id;
        return false;
    }
    qDebug() << "find the AVCodec " << para->codec_id;

    m_mutex.lock();
    // 创建解码器上下文
    m_VCodecCtx = avcodec_alloc_context3(vcodec);
    // 配置解码器上下文参数
    avcodec_parameters_to_context(m_VCodecCtx, para);
    // 清空编码器参数，避免内存泄漏（很重要）
    avcodec_parameters_free(&para);
    // 八线程解码
    m_VCodecCtx->thread_count = 8;

    // 打开解码器上下文
    int re = avcodec_open2(m_VCodecCtx, 0, 0);
    if (re != 0)
    {
        avcodec_free_context(&m_VCodecCtx);
        m_mutex.unlock();
        char buf[1024] = { 0 };
        av_strerror(re, buf, sizeof(buf) - 1);
        qDebug() << "avcodec_open2  failed! :" << buf;
        return false;
    }
    m_mutex.unlock();
    qDebug() << " avcodec_open2 success!";

    return true;

}

bool Decode::Send(AVPacket *pkt)
{
    // 容错处理
    if (!pkt || pkt->size <= 0 || !pkt->data)return false;
    m_mutex.lock();
    if (!m_VCodecCtx)
    {
        m_mutex.unlock();
        return false;
    }
    int re = avcodec_send_packet(m_VCodecCtx, pkt);
    m_mutex.unlock();

    // 无论成功与否，都清空AVPacket，避免内存泄漏（很重要）
    av_packet_free(&pkt);
    if (re != 0)return false;
    return true;

}

AVFrame *Decode::Recv()
{
    m_mutex.lock();
    if (!m_VCodecCtx)
    {
        m_mutex.unlock();
        return NULL;
    }
    AVFrame *frame = av_frame_alloc();
    int re = avcodec_receive_frame(m_VCodecCtx, frame);
    m_mutex.unlock();
    if (re != 0)
    {
        av_frame_free(&frame);
        return NULL;
    }
    //cout << "["<<frame->linesize[0] << "] " << flush;
    pts = frame->pts;
    return frame;

}

void Decode::Clear()
{
    m_mutex.lock();
    // 清理解码缓冲
    if (m_VCodecCtx)
        avcodec_flush_buffers(m_VCodecCtx);

    m_mutex.unlock();

}

void Decode::Close()
{
    m_mutex.lock();
    if (m_VCodecCtx)
    {
        avcodec_close(m_VCodecCtx);
        avcodec_free_context(&m_VCodecCtx);
    }
    pts = 0;
    m_mutex.unlock();

}

void Decode::XFreePacket(AVPacket **pkt)
{
    if (!pkt || !(*pkt))
    {
        return;
    }
    av_packet_free(pkt);
}

void Decode::XFreeFrame(AVFrame **frame)
{
    if (!frame || !(*frame))return;
    av_frame_free(frame);
}


