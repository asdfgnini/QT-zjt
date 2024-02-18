#include "demux.h"
#include <QDebug>

static double r2d(AVRational r)
{
    return r.den == 0 ? 0 : (double)r.num / (double)r.den;
}

Demux::Demux()
{
    static bool isFirst = true;
    static std::mutex dmux;
    dmux.lock();
    if (isFirst)
    {
        // 初始化网络库 （可以打开rtsp rtmp http 协议的流媒体视频）
        avformat_network_init();
        isFirst = false;
    }
    dmux.unlock();
}

Demux::~Demux()
{

}

bool Demux::open(const char *filename)
{
    //参数设置
    AVDictionary* opts = nullptr;
    //设置rtsp流已tcp协议打开
    av_dict_set(&opts,"rtsp_transport","tcp",0);
    //网络延时时间
    av_dict_set(&opts,"max_delay","500",0);

    m_mutex.lock();

    //解封装
    int ret = avformat_open_input(&pFormatCtx,
                        filename,
                        0,  //表示自动选择解封器
                        &opts);//参数设置，比如rtsp的延时时间
    if(ret != 0)
    {
        char buf[1024] = {0};
        av_strerror(ret,buf,sizeof(buf) - 1);
        qDebug() << "open " << filename << "failed! :" << buf;
        return false;
    }
    qDebug() << "open " << filename << " success!";

    //探测获取流信息
    avformat_find_stream_info(pFormatCtx,0);
    //获取媒体总时长,单位为毫秒
    totalMs  = static_cast<int>(pFormatCtx->duration / (AV_TIME_BASE / 1000));
    qDebug() << "totalMs = " << totalMs << "ms";
    //打印视频流详细信息
    av_dump_format(pFormatCtx,0,filename,0);


    nVStreamIndex = av_find_best_stream(pFormatCtx,AVMEDIA_TYPE_VIDEO,-1,-1,NULL,0);

    if(nVStreamIndex == -1)
    {
        qDebug() << "find videoStream failed";
        return false;
    }
    // 打印视频信息（这个pStream只是指向pFormatCtx的成员，未申请内存，为栈指针无需释放，下面同理）
    AVStream* pVStream = pFormatCtx->streams[nVStreamIndex];
    width = pVStream->codecpar->width;
    height = pVStream->codecpar->height;

    qDebug() << "=======================================================";
    qDebug() << "VideoInfo: " << nVStreamIndex;
    qDebug() << "codec_id = " << pVStream->codecpar->codec_id;
    qDebug() << "format = " << pVStream->codecpar->format;
    qDebug() << "width=" << pVStream->codecpar->width;
    qDebug() << "height=" << pVStream->codecpar->height;
    //帧率fps 分数转换
    qDebug() << "video_fps = " <<  r2d(pVStream->avg_frame_rate);

    qDebug() << "=======================================================";
    qDebug() << nAStreamIndex << "音频信息";

    //获取音频流索引
    nAStreamIndex = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if (nVStreamIndex == -1)
    {
        qDebug() << "find audioStream failed!";
        return false;
    }

    // 打印音频信息
    AVStream* pAStream = pFormatCtx->streams[nAStreamIndex];

    sampleRate = pAStream->codecpar->sample_rate;
    channels = pAStream->codecpar->ch_layout.nb_channels;

    qDebug() << "=======================================================";
    qDebug() << "AudioInfo: " << nAStreamIndex;
    qDebug() << "codec_id = " << pAStream->codecpar->codec_id;
    qDebug() << "format = " << pAStream->codecpar->format;
    qDebug() << "sample_rate = " << pAStream->codecpar->sample_rate;
    // AVSampleFormat;
    qDebug() << "channels = " << pAStream->codecpar->ch_layout.nb_channels;
    // 一帧数据？？ 单通道样本数
    qDebug() << "frame_size = " << pAStream->codecpar->frame_size;

    m_mutex.unlock();

    return true;
}

AVPacket *Demux::read()
{
    m_mutex.lock();
    if (!pFormatCtx) // 容错
    {
        m_mutex.unlock();
        return 0;
    }
    AVPacket *pkt = av_packet_alloc();
    // 读取一帧，并分配空间
    int re = av_read_frame(pFormatCtx, pkt);
    if (re != 0)
    {
        m_mutex.unlock();
        av_packet_free(&pkt);
        return 0;
    }
    // pts转换为毫秒
    pkt->pts = pkt->pts*(1000 * (r2d(pFormatCtx->streams[pkt->stream_index]->time_base)));
    pkt->dts = pkt->dts*(1000 * (r2d(pFormatCtx->streams[pkt->stream_index]->time_base)));
    m_mutex.unlock();

    return pkt;
}

AVCodecParameters *Demux::copyVPara()
{
    m_mutex.lock();
    if (!pFormatCtx)
    {
        m_mutex.unlock();
        return NULL;
    }
    AVCodecParameters *pa = avcodec_parameters_alloc();
    avcodec_parameters_copy(pa, pFormatCtx->streams[nVStreamIndex]->codecpar);
    m_mutex.unlock();

    return pa;
}

AVCodecParameters *Demux::copyAPara()
{
    m_mutex.lock();
    if (!pFormatCtx)
    {
        m_mutex.unlock();
        return NULL;
    }
    AVCodecParameters *pa = avcodec_parameters_alloc();
    avcodec_parameters_copy(pa, pFormatCtx->streams[nAStreamIndex]->codecpar);
    m_mutex.unlock();
    return pa;

}

bool Demux::isAudio(AVPacket *pkt)
{
    if (!pkt)
    {
        return false;
    }

    if (pkt->stream_index == nVStreamIndex)
    {
        return false;
    }
    return true;
}

// seek 位置 pos 0.0 ~1.0
bool Demux::seek(double pos)
{
    m_mutex.lock();
    if (!pFormatCtx)
    {
        m_mutex.unlock();
        return false;
    }
    // 清理读取缓冲
    avformat_flush(pFormatCtx);

    long long seekPos = 0;
    seekPos = pFormatCtx->streams[nVStreamIndex]->duration * pos;
    int re = av_seek_frame(pFormatCtx, nVStreamIndex, seekPos, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
    m_mutex.unlock();

    if (re < 0)
    {
        return false;
    }
    return true;
}

void Demux::clear()
{
    m_mutex.lock();
    if (!pFormatCtx)
    {
        m_mutex.unlock();
        return;
    }


    m_mutex.unlock();

}

void Demux::close()
{
    m_mutex.lock();
    if (!pFormatCtx)
    {
        m_mutex.unlock();
        return;
    }
    // 清理读取缓冲
    avformat_flush(pFormatCtx);
    avformat_close_input(&pFormatCtx);
    // 媒体总时长（毫秒）
    totalMs = 0;
    m_mutex.unlock();
}

AVPacket *Demux::readVideo()
{
    m_mutex.lock();
    if (!pFormatCtx) // 容错
    {
        m_mutex.unlock();
        return 0;
    }
    m_mutex.unlock();

    AVPacket* pkt = NULL;

    // 防止阻塞
    for (int i = 0; i < 20; i++)
    {
        pkt = read();
        if (!pkt)
        {
            break;
        }

        if (pkt->stream_index == nVStreamIndex)
        {
            break;
        }
        av_packet_free(&pkt);
    }

    return pkt;

}
