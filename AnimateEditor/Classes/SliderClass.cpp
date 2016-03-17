#include "SliderClass.h"
#include "MyConfig.h"
#include "qtedit.h"
SliderClass::SliderClass()
{
}

SliderClass::SliderClass(QWidget *parent /*= 0*/)
{

}

SliderClass::SliderClass(Qt::Orientation orientation, QWidget *parent /*= 0*/)
{

}


SliderClass::~SliderClass()
{
}

void SliderClass::mousePressEvent(QMouseEvent *ev)
{
	QPoint mousepos = ev->pos();
	int posi =  mousepos.x() / _Line_Btn_Width;
	QtEdit::getInstance()->PencentageSlider->setValue(posi + 1);
	if (QtEdit::getInstance()->ui.PauseButton->text() == _Pausetext)
	{
		QtEdit::getInstance()->pausebuttonclick();
	}

}

void SliderClass::mouseMoveEvent(QMouseEvent *ev)
{
	QPoint mousepos = ev->pos();
	int posi = mousepos.x() / _Line_Btn_Width;
	QtEdit::getInstance()->PencentageSlider->setValue(posi + 1);
	__super::mouseMoveEvent(ev);
}
