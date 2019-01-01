#pragma once

#include <QtWidgets/QWidget>
#include "ui_XPlayer2.h"

class XPlayer2 : public QWidget
{
	Q_OBJECT

public:
	XPlayer2(QWidget *parent = Q_NULLPTR);
	~XPlayer2();

	//定时器 滑动条显示
	void timerEvent(QTimerEvent *e);

	//窗口尺寸变化
	void resizeEvent(QResizeEvent *e);

	void SetPause(bool isPause);


	//双击全屏
	void mouseDoubleClickEvent(QMouseEvent *e);

public slots:
	void OpenFile();
	void PlayOrPause();
	void SliderPress();
	void SliderRelease();

private:
	bool isSliderPress = false;
	Ui::XPlayer2Class ui;
};
