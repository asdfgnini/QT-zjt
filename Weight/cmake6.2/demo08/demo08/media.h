#ifndef MEDIA_H
#define MEDIA_H

//ffmpeg
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>

}
#include <QString>
#include <QDebug>
#include <QThread>
#include <QFile>

class Media
{
public:
    Media();
    ~Media();
    bool Open(QString FilePath);//打开流媒体文件,打开对应的视频和音频解码器
    void Close();//关闭流媒体文件解析和关闭对应的解析器
    bool Save_file();//解码后保存成文件到本地,目前支持YUV420p格式

public:
    bool is_FormatNULL();

    AVFormatContext* Get_format();
    AVCodecContext* Get_VideoDecodec();
    uint32_t Get_Videonum();



private:
    AVFormatContext* m_pAVFormatCtx = nullptr;//流文件解析上下文
    AVCodecContext* m_pVidDecodeCtx = nullptr;//视频解码器上下文
    uint32_t m_nVidStreamIndex = -1;	   //视频流索引值
    AVCodecContext* m_pAudDecodeCtx = nullptr;//音频解码器上下文
    uint32_t m_nAudStreamIndex = -1;	   //音频流索引值
};

#endif // MEDIA_H
