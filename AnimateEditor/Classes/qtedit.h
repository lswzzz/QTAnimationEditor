#ifndef QTEDIT_H
#define QTEDIT_H

#include <QtWidgets/QMainWindow>
#include "ui_qtedit.h"
#include "QTableWidget.h"
#include "qframe.h"
#include "QScrollArea.h"
#include "qtableview.h"
#include "ClickButton.h"
#include "qstandarditemmodel.h"
#include "MyLineVector.h"
#include "DrawLayer.h"
#include "SliderClass.h"

class AppDelegate;
namespace Ui {
	class QtEdit;
}
class QtEdit : public QMainWindow
{
	Q_OBJECT

public:
	QtEdit(QWidget *parent       = 0);
	~QtEdit();
	Ui::QtEditClass getUI(){ return ui; };
	void setGLView(QWidget *glWidget);
	void ShowMsg(std::string);
	static QtEdit * getInstance();
	void AddCao();
	void MySQLite(bool is_Update = false, QString data = 0 , QString col_name = "");
	void AddTimeLine(int _linemodel);
	void DeleteLine(int _row);
	void ClickToRepaintBar();
	void ShowMessageInBar(int argc , ...);
	void Update_DrawLayer();
	int floatToInt(float f);
	double doubleToDoubletwo(double &f);
	void CheckAnimation();
	Point getSpritePos(){ return spritePos; };
	int getSpriteModel(){ return SpiteS_Model; };
	void clearAllClickButton(int col);
	void resetClickButton(int col);
	void SpriteChange(float dt);

public:
	int SpiteS_Model             = 0;
	bool Ctrl_Is_On;
	QVector<QVector<ClickButton *>> _allClickButton;
	QVector<QVector<ClickButton *>> _retaliteAllClickButton;
	QVector<MyLineVector *> _animateLineButton;
	MyLineVector * _MyLineVector;
	QWidget * buttonWidget;
	QFrame * line;
	QLabel * showline;
	QScrollArea *scrollArea;
	int FPX                      = 30;
	bool is_import;
	Ui::QtEditClass ui;
	int pu                       = 1;

	int _now_linesize;
	QTextCodec *codec;
	bool Shift_is_ON             = false;
	bool Space_is_ON             = false;
	bool KeyS_is_ON              = false;
	QStringList myBox_Comboxlist;
	QRegExp  *double_rx;//正则表达式
	QRegExpValidator * validtor;
	bool Is_ChangeInputToBox;//
	QStringList animation_list;
	QString openC3bFile_Path     = "./";
	QString export_Byte_Path     = "./";
	QString export_Json_Path     = "./";
	QString openSpineFile_Path   = "./";
	//当前点击的行列
	int selectRow                = -1;
	int selectCol                = -1;
	int SeleteLineRow            = -1;
	bool isClickToChange         = false;
	int selectModel              = 0;
	double _Rotate_3d_x          = 0;
	double _Rotate_3d_y          = _IN_Rotate3D_Y;
	double _Rotate_3d_z          = 0;
	SliderClass * PencentageSlider;
	bool						isUpdateAnimation;
public slots:
	void pausebuttonclick();
	void saveAllData();
private slots:
	void yestButtonClick();
	//导入c3b
	void import();
	//导入spine
	void importSpine();
	void on_actionImporteffect_triggered();
	void exportData();
	void openData();
	void BoxLengthChangeInput();
	void BoxMidPosiChangeInput();
	void Rotate3D_ChangeINput();
	void ChangeInput();
	void ReChangeInput();
	void showmessageChange();
	void AnimationSlderChange();
	void AnimationSlderClick(int);
	void keyPressEvent(QKeyEvent *);
	void keyReleaseEvent(QKeyEvent *);
	void AnimationTreeWidgetClick(QTreeWidgetItem * item, int column);
	void SlderButtonClick();
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void ActionHelp();
	void deleteDrawnode();
	void BoxChangeInput(QString str);
	void export_byteData();
	void wheelEvent(QWheelEvent *e);//鼠标滚动
	void AddLineButton_Click();
	void OnTableWidgetSelect();
	void LineID_ChangeInput();
	void modelShowPosTransition();
	void resetBgColor();
protected:
	void closeEvent(QCloseEvent *);
	void setParent(HWND);
	//读取json数据
	void Init();
	void AddScallAreaWidget();
	void AddAnimationList(QString full_path_name);
	void setPerWiget(int max);
	void SpriteChange();
	void Init_ClickButton(int col);
	bool Is_Point_Into(QPoint po, QPoint st, QPoint en);

	QString getHeadName(int _model);
	void deletePro();

	void resizeEvent(QResizeEvent * event);

	
private:
	
	AppDelegate         *_appDelegate;
	QWidget             *_glWidget;

	std::string			mymsg;
	
	double				mouseX;
	double				mouseY;
	char				myshowstr[100];
	QPoint				stPoint;
	QPoint				enPoint;
	QString				saveDataName;
	QString				_filename;
	int					_mycol;
	QString				re_file_path;
	QScrollBar			*scallbar;
	bool				_mouse_is_in;

	QPushButton *Add_LineBtn;
	QTableWidget * _LinesTableWidget;
	QStringList _lineVerHeader;

	ClickButton * _tempClickButton;
	//int _last_animaID          = -1;
	std::string _last_animaname  = "";
	Point spritePos;
	QSize sourceSize;
	QSize perWidgeBaseSize;
public:
	HWND m_Parent;
};

#endif // QTEDIT_H
