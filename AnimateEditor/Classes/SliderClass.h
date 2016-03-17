#pragma once
#include "qwidget.h"
#include "qslider.h"
class SliderClass : public QSlider
{
	Q_OBJECT
public:
	SliderClass();
	~SliderClass();
	SliderClass(QWidget *parent = 0);
	SliderClass(Qt::Orientation orientation, QWidget *parent = 0);
protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
};

