#pragma execution_character_set("utf-8")
#include "XPlayer2.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "XDemuxThread.h"
static XDemuxThread dt;

XPlayer2::XPlayer2(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	dt.Start();
	startTimer(40);
}

void XPlayer2::OpenFile()
{
	//选择文件
	QString name = QFileDialog::getOpenFileName(this, "选择视频文件");
	if (name.isEmpty())return;
	this->setWindowTitle(name);
	if (!dt.Open(name.toLocal8Bit(), ui.video))
	{
		QMessageBox::information(0, "error", "open file failed!");
		return;
	}
	SetPause(dt.isPause);
}

//双击全屏
void XPlayer2::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (isFullScreen())
		this->showNormal();
	else
		this->showFullScreen();
}
//窗口尺寸变化
void XPlayer2::resizeEvent(QResizeEvent *e)
{
	ui.playPos->move(50, this->height() - 50);
	ui.playPos->resize(this->width() - 100, ui.playPos->height());
	ui.openFile->move(50, this->height() - 100);
	ui.isPlay->move(ui.openFile->x() + ui.openFile->width() + 10, ui.openFile->y());
	ui.video->resize(this->size());
}

void XPlayer2::SliderPress()
{
	isSliderPress = true;
}
void XPlayer2::SliderRelease()
{
	isSliderPress = false;
	double pos = 0.0;
	pos = (double)ui.playPos->value() / (double)ui.playPos->maximum();
	dt.Seek(pos);
}

//定时器 滑动条显示
void XPlayer2::timerEvent(QTimerEvent *e)
{
	if (isSliderPress)return;
	long long total = dt.totalMs;
	if (total > 0)
	{
		double pos = (double)dt.pts / (double)total;
		int v = ui.playPos->maximum() * pos;
		ui.playPos->setValue(v);
	}
}

void XPlayer2::PlayOrPause()
{
	bool isPause = !dt.isPause;
	SetPause(isPause);
	dt.SetPause(isPause);
}

void XPlayer2::SetPause(bool isPause)
{
	if (isPause)
		ui.isPlay->setText("播 放");
	else
		ui.isPlay->setText("暂 停");
}

XPlayer2::~XPlayer2()
{
	dt.Close();
}
