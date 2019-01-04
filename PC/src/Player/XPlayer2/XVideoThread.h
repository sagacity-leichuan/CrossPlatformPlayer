#pragma once

///�������ʾ��Ƶ
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
	//ͬ��ʱ�䣬���ⲿ����
	long long synpts = 0;
	void SetPause(bool isPause);
	bool isPause = false;
protected:
	std::mutex vmux;
	IVideoCall *call = 0;


};

