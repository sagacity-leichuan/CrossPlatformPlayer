#pragma once

///解码和显示视频
struct AVPacket;
struct AVCodecParameters;
class XDecode;
#include <list>
#include <mutex>
#include <QThread>
#include "IVideoCall.h"
#include "XDecodeThread.h"
class XVideoThread:public XDecodeThread
{
public:

	//??pts,??????????pts >= seekpts return true ??????
	virtual bool RepaintPts(AVPacket *pkt, long long seekpts);
	//??,?????????
	virtual bool Open(AVCodecParameters *para,IVideoCall *call,int width,int height);
	void run();
	XVideoThread();
	virtual ~XVideoThread();
	//同步时间，由外部传入
	long long synpts = 0;
	void SetPause(bool isPause);
	bool isPause = false;
protected:
	std::mutex vmux;
	IVideoCall *call = 0;


};

