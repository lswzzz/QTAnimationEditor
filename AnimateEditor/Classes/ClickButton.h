#ifndef _CLICKBUTTON_CLASS_H_
#define  _CLICKBUTTON_CLASS_H_


#include "QPushButton.h"
#include "qmenu.h"
#include "QMouseEvent"
#include "DrawNodeVertices.h"
#include "MyConfig.h"

class ClickButton : public QPushButton
{
	Q_OBJECT
public:
	ClickButton(int row, int col, int frame_Model = 0, QWidget *parent = 0);

	~ClickButton(){
		//FREE_DEL_OBJ(one_BoxAction);
		//FREE_DEL_OBJ(delete_AllAction);
		//FREE_DEL_OBJ(delete_LineAction);
		//FREE_DEL_OBJ(popMenu);
		//QPushButton::destroy();
		FREE_DEL_OBJ(_DrawNodeVertices);
	};
	void setButtonColor();
	inline void  setRow(int row){ _row = row;  };
	inline void setRowOpt(){ _row--; };
	inline int getRow(){ return _row; };
	inline void setCol(int col){ _col = col; };
	inline int getCol(){ return _col; };
	inline void setFrame(bool is_frame){ _is_Frame = is_frame; };
	inline bool isFrame(){ return _is_Frame; };
	inline void setFrameModel(int _model){ _frame_Model = _model; };
	inline int getFrameMode(){ return _frame_Model; };
	inline void setParent(QWidget *parent){ _parent = parent; setParent(parent); };
	inline QWidget * parent(){ return _parent;  };
	inline void setLineID(int line_ID){ _line_ID = line_ID; };
	inline int getLineID(){ return _line_ID; };
	inline void setIsNULL(bool _null){ _is_null = _null; };
	inline bool isNULL(){ return _is_null; };
	inline bool getGravity(){ return _is_gravity; };
	inline void setGravity(bool _gravity){ _is_gravity = _gravity;  };
	void DoDelFrame();
	void Click_ED(bool is_click = false);
	ClickButton * copy();
protected:
	void UpdateVertices();
private slots:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void DelAction();
	void DddAction();
	void DelLine();
	void DelFrame();
	void DoGravity();
	//void focusInEvent(QFocusEvent *);
	//void focusOutEvent(QFocusEvent *);
	void copyAction();
	void pasteAction();
	void FreeBox();
private:
	int _row;
	int _col;
	bool _is_Frame = false;
	int _frame_Model;
	QAction * one_BoxAction;
	QAction * Gra_Action;
	QAction * delete_AllAction;
	QAction * delete_LineAction;
	QAction * free_BoxAction;
	QAction * copy_VerticesAction;
	QAction * pause_VerticesAction;
	QMenu* popMenu;
	QWidget * _parent;
	int _line_ID;
	bool _is_null = false;
	bool _is_gravity = true;
	bool KeyCtrl_Is_ON = false;
	bool KeyC_Is_ON = false;
	bool KeyV_Is_ON = false;
public:
	DrawNodeVertices * _DrawNodeVertices = NULL;
	double _ScallX = _IN_ScallX;
	double _ScallY = _IN_ScallY;
	double _Height = _IN_Height;
	double _Width = _IN_Width;
};

#endif // _CLICKBUTTON_CLASS_H_