#define _CRT_SECURE_NO_WARNINGS
#include "media.h"

#include <cstdio>
#include <iostream>
using namespace std;

Media::Media()
{

}

Media::~Media()
{
    //关闭流媒体文件解析
    if (m_pAVFormatCtx != nullptr)
    {
        avformat_close_input(&m_pAVFormatCtx);
        m_pAVFormatCtx = nullptr;
    }

    //关闭视频解码器
    if (m_pVidDecodeCtx != nullptr)
    {
        avcodec_close(m_pVidDecodeCtx);
        avcodec_free_context(&m_pVidDecodeCtx);
        m_pVidDecodeCtx = nullptr;
    }
    //关闭音频解码器
    if (m_pAudDecodeCtx != nullptr)
    {
        avcodec_close(m_pAudDecodeCtx);
        avcodec_free_context(&m_pAudDecodeCtx);
        m_pAudDecodeCtx = nullptr;
    }
}


static double r2d(AVRational r)
{
    return r.den == 0 ? 0 : (double)r.num / (double)r.den;
}
bool Media::Open(QString FilePath)
{
    bool re_value = true;
    int res = 0;
    qDebug() << "Demux: " << FilePath;
    AVDictionary* format_ops = nullptr;
    av_dict_set(&format_ops, "probesize", "32", 0);

    re_value = avformat_open_input(&m_pAVFormatCtx, FilePath.toStdString().c_str(), NULL, &format_ops);
    if (re_value)//return 0 success
    {
        char err_buffer[1024] = { 0 };
        av_strerror(re_value, err_buffer, sizeof(err_buffer));
        qDebug() << "Demux: " << "open " << FilePath << "fail: " << err_buffer;
        Close();
        return false;
    }
    else
    {
        cout << "Demux: " << "success to avformat_open_input" << endl;
    }

    res = avformat_find_stream_info(m_pAVFormatCtx, NULL);
    if (res < 0)
    {
        char errBuf[1024] = { 0 };
        av_strerror(res, errBuf, sizeof(errBuf));
        qDebug() << "Demux: " << "open " << FilePath << " failed! :" << errBuf;
        Close();
        return false;
    }
    else if(res == AVERROR_EOF)
    {
        cout << "Demux " << "reached to file end" << endl;;
    }
    else
    {
        cout << "Demux: " << "success to avformat_find_stream_info" <<endl;
    }
    //打印音视频流信息
    qDebug() << QString::fromUtf8("================打印音视频流信息========================");
    cout << "Demux: " << "duration: " << m_pAVFormatCtx->duration << endl;//直接获取获取不到，采用探测
    int64_t totalMs = m_pAVFormatCtx->duration / (AV_TIME_BASE / 1000);
    cout << "Demux: " << "totalMs: " << totalMs << "ms" << endl;
    qDebug() << "Demux: " << "nb_stream: " << m_pAVFormatCtx->nb_streams ;
    for (unsigned int i = 0; i < m_pAVFormatCtx->nb_streams; i++)
    {
        qDebug() << "Demux: " << "stream codec type: " << m_pAVFormatCtx->streams[i]->codecpar->codec_type ;
    }
    qDebug() << "Demux: " << "iformat name: " << m_pAVFormatCtx->iformat->name ;
    qDebug() << "Demux: " << "iformat long name: " << m_pAVFormatCtx->iformat->long_name ;
    qDebug() << "======================================================" ;
    m_nVidStreamIndex = av_find_best_stream(m_pAVFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (m_nVidStreamIndex == -1)
    {
        qDebug() << "Demux: " << "fail to find videostream";
        Close();
        return false;
    }
    else
    {
        qDebug() << "Demux: " << "success to find videostream: " << "videoindex: " << m_nVidStreamIndex ;
    }
    //打印视频流相关信息
    qDebug() << QString::fromUtf8("================打印视频流信息========================");
    qDebug() << "Demux: " << "codec_id = " << m_pAVFormatCtx->streams[m_nVidStreamIndex]->codecpar->codec_id ;
    qDebug() << "Demux: " << "format = " << m_pAVFormatCtx->streams[m_nVidStreamIndex]->codecpar->format ;
    qDebug() << "Demux: " << "width=" << m_pAVFormatCtx->streams[m_nVidStreamIndex]->codecpar->width ;
    qDebug() << "Demux: " << "height=" << m_pAVFormatCtx->streams[m_nVidStreamIndex]->codecpar->height ;

    qDebug() << "Demux: " << "video fps = " << r2d(m_pAVFormatCtx->streams[m_nVidStreamIndex]->avg_frame_rate) ;

    qDebug() << "======================================================" ;

    m_nAudStreamIndex = av_find_best_stream(m_pAVFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if (m_nAudStreamIndex == -1)
    {
        qDebug() << "Demux: " << "fail to find audiostream";
        Close();
        return false;
    }
    else
    {
        qDebug() << "Demux: " << "success to find audiostream: " << "audioindex: " << m_nAudStreamIndex ;
    }
    //打印音频流相关信息
    qDebug() << QString::fromUtf8("================打印音频流信息========================");
    qDebug() << "Demux: " << "codec_id = " << m_pAVFormatCtx->streams[m_nAudStreamIndex]->codecpar->codec_id ;
    qDebug() << "Demux: " << "format = " << m_pAVFormatCtx->streams[m_nAudStreamIndex]->codecpar->format ;
    qDebug() << "Demux: " << "sample_rate = " << m_pAVFormatCtx->streams[m_nAudStreamIndex]->codecpar->sample_rate ;
    // AVSampleFormat;
    qDebug() << "Demux: " << "channels = " << m_pAVFormatCtx->streams[m_nAudStreamIndex]->codecpar->ch_layout.nb_channels ;
    // 一帧数据 单通道样本数
    qDebug() << "Demux: " << "frame_size = " << m_pAVFormatCtx->streams[m_nAudStreamIndex]->codecpar->frame_size ;
    qDebug() << "======================================================" ;


    //创建视频解码器并且打开
    const AVCodec* video_codec = nullptr;
    //获取avcodec
    video_codec = avcodec_find_decoder(m_pAVFormatCtx->streams[m_nVidStreamIndex]->codecpar->codec_id);
    if (video_codec == nullptr)
    {
        qDebug() << "Demux: " << "can not find video codec" ;
        Close();
        return false;
    }
    m_pVidDecodeCtx = avcodec_alloc_context3(video_codec);
    if (m_pVidDecodeCtx == nullptr)
    {
        cout << "Demux: " << "fail to avcodec_alloc_context3" << endl;
        Close();
        return false;
    }
    res = avcodec_parameters_to_context(m_pVidDecodeCtx, m_pAVFormatCtx->streams[m_nVidStreamIndex]->codecpar);
    if (res != 0)
    {
        cout << "Demux: " << "fail to avcodec_parameters_to_context" << endl;
        Close();
        return false;
    }
    res = avcodec_open2(m_pVidDecodeCtx, NULL, NULL);
    if (res != 0)
    {
        cout << "Demux: " << "fail to avcodec_open2" << endl;
        Close();
        return false;
    }
    else
    {
        cout << "success to open VideoDecoder" << endl;
    }

    //创建音频解码器并且打开
    const AVCodec* audio_codec = nullptr;
    //获取avcodec
    audio_codec = avcodec_find_decoder(m_pAVFormatCtx->streams[m_nAudStreamIndex]->codecpar->codec_id);
    if (audio_codec == nullptr)
    {
        cout << "Demux: " << "can not find video codec" << "line: " <<  __LINE__ << endl;
        Close();
        return false;
    }
    m_pAudDecodeCtx = avcodec_alloc_context3(audio_codec);
    if (m_pAudDecodeCtx == nullptr)
    {
        cout << "Demux: " << "fail to avcodec_alloc_context3" << "line: " << __LINE__ << endl;
        Close();
        return false;
    }
    res = avcodec_parameters_to_context(m_pAudDecodeCtx, m_pAVFormatCtx->streams[m_nAudStreamIndex]->codecpar);
    if (res != 0)
    {
        cout << "Demux: " << "fail to avcodec_parameters_to_context" << "line: " << __LINE__ << endl;
        Close();
        return false;
    }
    res = avcodec_open2(m_pAudDecodeCtx, NULL, NULL);
    if (res != 0)
    {
        cout << "Demux: " << "fail to avcodec_open2" << "line: " << __LINE__ << endl;
        Close();
        return false;
    }
    else
    {
        cout << "success to open AudioDecoder" << endl;
    }

    return true;
}

void Media::Close()
{
    //关闭流媒体文件解析
    if (m_pAVFormatCtx != nullptr)
    {
        avformat_close_input(&m_pAVFormatCtx);
        m_pAVFormatCtx = nullptr;
    }

    //关闭视频解码器
    if (m_pVidDecodeCtx != nullptr)
    {
        avcodec_close(m_pVidDecodeCtx);
        avcodec_free_context(&m_pVidDecodeCtx);
        m_pVidDecodeCtx = nullptr;
    }
    //关闭音频解码器
    if (m_pAudDecodeCtx != nullptr)
    {
        avcodec_close(m_pAudDecodeCtx);
        avcodec_free_context(&m_pAudDecodeCtx);
        m_pAudDecodeCtx = nullptr;
    }
}

// #define C_WAY
bool Media::Save_file()
{
    if(m_pAVFormatCtx == nullptr)
    {
        qDebug() << "NO Media";
        return false;
    }
    int w = m_pVidDecodeCtx->width;
    int h = m_pVidDecodeCtx->height;

    AVPacket *packet = av_packet_alloc();
    av_new_packet(packet,m_pVidDecodeCtx->width * m_pVidDecodeCtx->height);
    AVFrame *frame = av_frame_alloc();
#ifdef C_WAY
    FILE *fp = fopen("C:\\Users\\Administrator\\Desktop\\Qt\\demo01\\demo01\\640x360_YUV420P.yuv","w+b");
    if(fp == nullptr)
    {
        qDebug() << "Can't open file";
        av_packet_free(&packet);
        av_frame_free(&frame);
        return false;
    }
#else
    QFile fp("C:\\Users\\Administrator\\Desktop\\Qt\\demo01\\demo01\\640x360_YUV420P.yuv");
    bool ok = fp.open(QIODevice::ReadWrite);
    if(ok == false)
    {
        qDebug() << "Can't open file";
        av_packet_free(&packet);
        av_frame_free(&frame);
        return false;

    }
    QDataStream binstream(&fp);
    QByteArray DataAllArray;
#endif

    while(av_read_frame(m_pAVFormatCtx,packet) >= 0)
    {
        if(packet->stream_index == m_nVidStreamIndex)
        {
            if(avcodec_send_packet(m_pVidDecodeCtx,packet) == 0)
            {
                while(avcodec_receive_frame(m_pVidDecodeCtx,frame) == 0)
                {
#ifdef C_WAY
                    fwrite(frame->data[0],1,w*h,fp);
                    fwrite(frame->data[1],1,w*h/4,fp);
                    fwrite(frame->data[2],1,w*h/4,fp);
#else
                    DataAllArray = QByteArray((const char*)frame->data[0],w*h);
                    fp.write(DataAllArray);
                    DataAllArray = QByteArray((const char*)frame->data[1],w*h/4);
                    fp.write(DataAllArray);
                    DataAllArray = QByteArray((const char*)frame->data[2],w*h/4);
                    fp.write(DataAllArray);
#endif


                    //avcodec_receive_frame 会调用av_frame_unref() ，所以这里无需调用
                }
            }
        }
        av_packet_unref(packet);
    }
    av_packet_free(&packet);
    av_frame_free(&frame);
#ifdef C_WAY
    fclose(fp);
#else
    fp.close();
#endif
    return false;
}

bool Media::is_FormatNULL()
{
    if(m_pAVFormatCtx != nullptr)
    {
        return false;
    }

    return true;
}

AVFormatContext *Media::Get_format()
{
    return m_pAVFormatCtx;
}

AVCodecContext *Media::Get_VideoDecodec()
{
    return m_pVidDecodeCtx;
}

uint32_t Media::Get_Videonum()
{
    return m_nVidStreamIndex;
}
