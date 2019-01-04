#include "XPlayer2.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "XDemux.h"
#include "XDecode.h"
#include "XResample.h"
#include "XAudioPlay.h"
#include "XAudioThread.h"
#include "XVideoThread.h"
#include "XDemuxThread.h"
using namespace std;

#include <QThread>

class TestThread :public QThread
{
public:
	XAudioThread at;
	XVideoThread vt;
	void Init()
	{
		//香港卫视
        const char *url = "rtmp://live.hkstv.hk.lxdns.com/live/hks1";
		//char *url = "rtmp://live.hkstv.hk.lxdns.com/live/hks2";
		cout << "demux.Open = " << demux.Open(url);
		demux.Read();
		demux.Clear();
		demux.Close();
		url = "v1080.mp4";
		cout << "demux.Open = " << demux.Open(url);
		//cout << "CopyVPara = " << demux.CopyVPara() << endl;
		//cout << "CopyAPara = " << demux.CopyAPara() << endl;
		//cout << "seek=" << demux.Seek(0.95) << endl;

		/////////////////////////////

		//cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVPara()) << endl;
		//vdecode.Clear();
		//vdecode.Close();
		//cout << "adecode.Open() = " << adecode.Open(demux.CopyAPara()) << endl;

		//cout << "resample.Open = " << resample.Open(demux.CopyAPara()) << endl;
		//XAudioPlay::Get()->channels = demux.channels;
		//XAudioPlay::Get()->sampleRate = demux.sampleRate;

		//cout << "XAudioPlay::Get()->Open() = " << XAudioPlay::Get()->Open() << endl;

		cout << "at.Open = " << at.Open(demux.CopyAPara(), demux.sampleRate, demux.channels);
		vt.Open(demux.CopyVPara(), video, demux.width, demux.height);
		at.start();
		vt.start();

	}
	unsigned char *pcm = new unsigned char[1024 * 1024];
	void run()
	{
		for (;;)
		{
			AVPacket *pkt = demux.Read();
			if (demux.IsAudio(pkt))
			{
				at.Push(pkt);
				/*adecode.Send(pkt);
				AVFrame *frame = adecode.Recv();
				int len = resample.Resample(frame, pcm);
				cout << "Resample:" << len << " ";
				while (len > 0)
				{
					if (XAudioPlay::Get()->GetFree() >= len)
					{
						XAudioPlay::Get()->Write(pcm, len);
						break;
					}
					msleep(1);
				}*/
				//cout << "Audio:" << frame << endl;
			}
			else
			{
				vt.Push(pkt);
				/*vdecode.Send(pkt);
				AVFrame *frame = vdecode.Recv();
				video->Repaint(frame);*/
				//msleep(40);
				//cout << "Video:" << frame << endl;
			}
			if (!pkt)break;
		}
	}
public:
	///测试XDemux
	XDemux demux;
	///解码测试
	XDecode vdecode;
	XDecode adecode;
	XResample resample;
	XVideoWidget *video = 0;

};

//v1080.mp4
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XPlayer2 w;
	w.show();

	//初始化gl窗口
	//TestThread tt;
	//w.ui.video->Init(tt.demux.width, tt.demux.height);
	//tt.video = w.ui.video;
	//tt.Init();
	//tt.start();
	//XDemuxThread dt;
	//char *url = "rtmp://live.hkstv.hk.lxdns.com/live/hks1";
	//char *url = "rtmp://live.hkstv.hk.lxdns.com/live/hks2";
	//url = "v1080.mp4";
	//dt.Open(url, w.ui.video);
	//dt.Start();


	return a.exec();
}
