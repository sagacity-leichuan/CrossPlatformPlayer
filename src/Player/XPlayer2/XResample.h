#pragma once
struct AVCodecParameters;
struct SwrContext;
struct AVFrame;
#include <mutex>
class XResample
{
public:

	//����������������һ�³��˲�����ʽ�����ΪS16
	virtual bool Open(AVCodecParameters *para,bool isClearPara = false);
	virtual void Close();
	// �����ز������С, ���ܳɹ�����ͷ�indata�ռ�
	virtual int Resample(AVFrame *indata, unsigned char *data);

	//AV_SAMPLE_FMT_S16
	int outFormat = 1;
	XResample();
	~XResample();
protected:
	std::mutex mux;
	SwrContext *actx = 0;
};

