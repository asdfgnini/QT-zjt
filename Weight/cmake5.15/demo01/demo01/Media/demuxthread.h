#ifndef DEMUXTHREAD_H
#define DEMUXTHREAD_H

#include <QThread>
#include <mutex>

#include "videocall.h"
#include "demux.h"
#include "videothread.h"
#include "audiothread.h"

class DemuxThread : public QThread
{
public:
    DemuxThread();
    virtual ~DemuxThread();

    void run();

    //创建对象并打开
    virtual bool Open(const char *url, VideoCall *call);

    //启动所有线程
    virtual void Start();

    //关闭线程清理资源
    virtual void Close();
    virtual void Clear();

    virtual void Seek(double pos);

    bool isExit = false;
    long long pts = 0;
    long long totalMs = 0;
    void SetPause(bool isPause);
    bool isPause = false;
protected:
    std::mutex mux;
    Demux *demux = 0;
    VideoThread *vt = 0;
    AudioThread *at = 0;

};

#endif // DEMUXTHREAD_H
