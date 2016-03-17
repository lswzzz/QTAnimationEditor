#ifndef _EXPORT_DATA_CLASS_H_
#define _EXPORT_DATA_CLASS_H_


#include "cocos2d.h"
#include "qtedit.h"
#include "ByteArray.h"
#include "qthread.h"
class Export_Data : public QThread
{
public:
	Export_Data();
	~Export_Data();
	static Export_Data * getinstance();
	void Export_JSONData(QVector<MyLineVector *> & _animateLineButton , std::string file_name);
	void Export_SaveData(QVector<MyLineVector *> & _animateLineButton , std::string file_name);
	void Export_ByteData(QVector<MyLineVector *> & _animateLineButton, std::string file_name);
	void Data_TO_Relatite(QVector<QVector<ClickButton *>> & _allButton, QVector<MyLineVector *> & _animateLineButton);
	Q_OBJECT
protected slots:
	void run();
protected:
	static Export_Data * _Export_Data;
	ByteArray *_ByteArray;

	QVector<MyLineVector *>  _animateLineButton;
	std::string file_name;
};

#endif // !_EXPORT_DATA_CLASS_H_