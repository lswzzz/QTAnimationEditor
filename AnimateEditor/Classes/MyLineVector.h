#ifndef _MYLINEVECTOR_CLASS_H_
#define  _MYLINEVECTOR_CLASS_H_


#include "cocos2d.h"
#include "ClickButton.h"
class MyLineVector
{
public:
	MyLineVector();
	~MyLineVector();
	QVector<QVector<ClickButton *>> _lineButton;
	//int _anima_ID;
	std::string _anima_Name;
	Point transPos;
};

#endif // !_MYLINEVECTOR_CLASS_H_
