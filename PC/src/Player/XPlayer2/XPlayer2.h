#pragma once

#include <QtWidgets/QWidget>
#include "ui_XPlayer2.h"

class XPlayer2 : public QWidget
{
	Q_OBJECT

public:
	XPlayer2(QWidget *parent = Q_NULLPTR);
	~XPlayer2();

	//��ʱ�� ��������ʾ
	void timerEvent(QTimerEvent *e);

	//���ڳߴ�仯
	void resizeEvent(QResizeEvent *e);

	void SetPause(bool isPause);


	//˫��ȫ��
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
