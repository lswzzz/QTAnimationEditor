#include "qtedit.h"
//#include <QtDebug>
#include "Classes/AppDelegate.h"
#include "Classes/CocosQtPort/CCQGLView.h"
#include <QTimer>
#include <QDockWidget>
#include "QTextEdit"
#include "QTextBlock"
#include <QEvent>
#include <qfiledialog.h>
#include "QMessageBox.h"
#include "cocos2d.h"
#include "QTableWidget.h"
#include "QTextStream.h"
#include "string.h"
#include "QTextCodec.h"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonValue"
#include "QJsonParseError"
#include <QProcess>
#include "QJSONobject"
#include "json/json.h"
#include "SQLite/DBUtil.h"
#include "MyConfig.h"
#include "Export_Data.h"
#include "HelloWorldScene.h"

USING_NS_CC;

static QtEdit* _QtEdit = NULL;
static DrawLayer *_DrawLayer = NULL;

QtEdit::QtEdit(QWidget *parent)
	: QMainWindow(parent),
	_appDelegate(NULL),
	_glWidget(NULL),
	is_import(false),
	Ctrl_Is_On(false),
	FPX(30),
	Shift_is_ON(false),
	Is_ChangeInputToBox(false),
	Space_is_ON(false)
	, isUpdateAnimation(true)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	spritePos = Point(_IN_Width, _IN_Height);
	_QtEdit = this;
	ui.setupUi(this);
	ui.SceneWidget->setWindowTitle("Cocos2dx Scene");
	ui.SceneWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.OutWiget->setWindowTitle("Out Put");
	//ui.OutWiget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.PerWiget->setWindowTitle("Frame Control");
	ui.PerWiget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.ListWidget->setWindowTitle("");
	ui.ListWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.AnimationtreeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.AnimationtreeWidget->header()->setStretchLastSection(true);
	ui.PerWidgetContents->setUpdatesEnabled(TRUE);
	//PencentageSlider->setGeometry(0, 0, this->width(), 40);
	codec = QTextCodec::codecForName("GB18030");

	PencentageSlider = new SliderClass(ui.PerWidgetContents);
	PencentageSlider->setObjectName(QStringLiteral("PencentageSlider"));
	PencentageSlider->setGeometry(QRect(0, 0, 960, 51));
	PencentageSlider->setMaximumSize(QSize(16777215, 16777215));
	PencentageSlider->setMinimum(0);
	PencentageSlider->setMaximum(99);
	PencentageSlider->setValue(0);
	PencentageSlider->setOrientation(Qt::Horizontal);
	this->sourceSize = this->baseSize();
	this->perWidgeBaseSize = ui.PerWiget->baseSize();
	AddCao();
	MySQLite();
	AddScallAreaWidget();
}

void QtEdit::AddCao()
{
	QObject::connect(ui.importaction, SIGNAL(triggered()), this, SLOT(import()));
	QObject::connect(ui.import_Spine, SIGNAL(triggered()), this, SLOT(importSpine()));

	QObject::connect(ui.modelTransPosX, SIGNAL(editingFinished()), this, SLOT(modelShowPosTransition()));
	QObject::connect(ui.modelTransPosY, SIGNAL(editingFinished()), this, SLOT(modelShowPosTransition()));
	QObject::connect(ui.ColorSureButton, SIGNAL(clicked()), this, SLOT(resetBgColor()));

	QObject::connect(ui.Box_Width, SIGNAL(textEdited(QString)), this, SLOT(BoxLengthChangeInput()));
	QObject::connect(ui.Box_Height, SIGNAL(textEdited(QString)), this, SLOT(BoxLengthChangeInput()));
	QObject::connect(ui.Box_X_Posi, SIGNAL(textEdited(QString)), this, SLOT(BoxMidPosiChangeInput()));
	QObject::connect(ui.Box_Y_Posi, SIGNAL(textEdited(QString)), this, SLOT(BoxMidPosiChangeInput()));

	QObject::connect(ui.Rotate3D_X, SIGNAL(textEdited(QString)), this, SLOT(Rotate3D_ChangeINput()));
	QObject::connect(ui.Rotate3D_Y, SIGNAL(textEdited(QString)), this, SLOT(Rotate3D_ChangeINput()));
	QObject::connect(ui.Rotate3D_Z, SIGNAL(textEdited(QString)), this, SLOT(Rotate3D_ChangeINput()));

	QObject::connect(ui.ScallX, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.ScallY, SIGNAL(textEdited(QString)), this, SLOT(ChangeInput()));
	QObject::connect(ui.Line_ID, SIGNAL(textEdited(QString)), this, SLOT(LineID_ChangeInput()));
	QObject::connect(ui.Re_Width, SIGNAL(textEdited(QString)), this, SLOT(ReChangeInput()));
	QObject::connect(ui.Re_Height, SIGNAL(textEdited(QString)), this, SLOT(ReChangeInput()));
	QObject::connect(ui.PauseButton, SIGNAL(clicked()), this, SLOT(pausebuttonclick()));
	QObject::connect(ui.showmessage, SIGNAL(textChanged()), this, SLOT(showmessageChange()));
	QObject::connect(PencentageSlider, SIGNAL(valueChanged(int)), this, SLOT(AnimationSlderChange()));
	QObject::connect(ui.AnimationtreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(AnimationTreeWidgetClick(QTreeWidgetItem*, int)));
	//QObject::connect(PencentageSlider, SIGNAL(actionTriggered(int)), this, SLOT(AnimationSlderClick(int)));
	QObject::connect(ui.actionHelp, SIGNAL(triggered()), this, SLOT(ActionHelp()));
	QObject::connect(ui.exportaction, SIGNAL(triggered()), this, SLOT(exportData()));
	QObject::connect(ui.openaction, SIGNAL(triggered()), this, SLOT(openData()));
	QObject::connect(ui.closeaction, SIGNAL(triggered()), this, SLOT(close()));
	QObject::connect(ui.Action_Save, SIGNAL(triggered()), this, SLOT(saveAllData()));
	QObject::connect(ui.export_byte, SIGNAL(triggered()), this, SLOT(export_byteData()));
	QObject::connect(ui.St_Width, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	QObject::connect(ui.St_Height, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	QObject::connect(ui.En_Width, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	QObject::connect(ui.En_Height, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
	QObject::connect(ui.Rotate, SIGNAL(textEdited(QString)), this, SLOT(BoxChangeInput(QString)));
}

QtEdit::~QtEdit()
{
	Director::getInstance()->release();
	delete _QtEdit;
}

QtEdit * QtEdit::getInstance()
{
	if (_QtEdit == NULL)
	{
		new QtEdit();
	}
	return _QtEdit;
}

void QtEdit::ShowMsg(std::string str)
{
	mymsg = mymsg + str + "\n";
	ui.showmessage->setPlainText((codec->toUnicode(mymsg.c_str())));
	QTextCursor cursor = ui.showmessage->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui.showmessage->setTextCursor(cursor);
	
}

void QtEdit::BoxChangeInput(QString str)
{
	if (_allClickButton.size() <= 0)
	{
		return;
	}
	QString title = _QtEdit->windowTitle();
	title = title.split("*").at(0);
	title += "*";
	_QtEdit->setWindowTitle(title);
	_tempClickButton = _allClickButton.at(selectRow).at(selectCol);
	double _S_W = ui.St_Width->text().toDouble();
	double _S_H = ui.St_Height->text().toDouble();
	double _E_W = ui.En_Width->text().toDouble();
	double _E_H = ui.En_Height->text().toDouble();
	double _Rotate = ui.Rotate->text().toDouble();
	double _x = spritePos.x;
	double _y = spritePos.y;
	double _sx = ui.ScallX->text().toDouble();
	double _sy = ui.ScallY->text().toDouble();
	_Rotate = _Rotate;
	_tempClickButton->_DrawNodeVertices->Relativevertices[0].set(_S_W + _x, _S_H + _y);
	_tempClickButton->_DrawNodeVertices->Relativevertices[2].set(_E_W + _x, _E_H + _y);
	_tempClickButton->_DrawNodeVertices->Rotate = _Rotate;
	_tempClickButton->_DrawNodeVertices->updateRetlativeVertices();
	_tempClickButton->setFrame(true);
	_tempClickButton->setButtonColor();
	_tempClickButton->setIsNULL(false);


	//_tempClickButton->_DrawNodeVertices->setRelativeScallX(_x, _sx, _IN_ScallX);
	//_tempClickButton->_DrawNodeVertices->setRelativeScallY(_y, _sy, _IN_ScallY);
	//_tempClickButton->_DrawNodeVertices->setVerticesScallX(_x, _sx, _IN_ScallX);
	//_tempClickButton->_DrawNodeVertices->setVerticesScallY(_y, _sy, _IN_ScallY);
	Vec2 roposi;
	roposi.set(_x, _y);
	_tempClickButton->_DrawNodeVertices->setRotateRelativeVertices(_tempClickButton->_DrawNodeVertices->Relativevertices[0], _tempClickButton->_DrawNodeVertices->Relativevertices[2], _Rotate * (PI / 180));

	//_tempClickButton->_DrawNodeVertices->setRelativeRotateVertices(_tempClickButton->_DrawNodeVertices->RotateVertices, roposi);
	//_tempClickButton->_DrawNodeVertices->setRotateFromRelativeRotate(_tempClickButton->_DrawNodeVertices->RotateVertices, roposi);
	//_allClickButton[selectRow][selectCol] = _tempClickButton;
	ClickToRepaintBar();

}

void QtEdit::wheelEvent(QWheelEvent *e)
{
	//int numDegrees = e->delta() / 8;//滚动的角度，*8就是鼠标滚动的距离
	//int numSteps = numDegrees / 15;//滚动的步数，*15就是鼠标滚动的角度
	/*bool has = ui.Width->hasFocus();*/
	//if (!is_import)
	//{
	//	return;
	//}
	double _ScallX = ui.ScallX->text().toDouble();
	double _ScallY = ui.ScallY->text().toDouble();
	int num = e->delta();
	int down_up = 1;
	if (num < 0)//向下滚动
	{
		down_up = -1;
	}
	else
	{
		down_up = 1;
	}
	if (ui.Re_Width->hasFocus())
	{
		spritePos.x = (spritePos.x + down_up);
		//ui.Width->setText(QString::number(ui.Width->text().toDouble() + down_up));
		ui.Re_Width->setText(QString::number(ui.Re_Width->text().toDouble() + down_up));
		ChangeInput();
	}
	else if (ui.Re_Height->hasFocus())
	{
		spritePos.y = spritePos.y + down_up;
		//ui.Height->setText(QString::number(ui.Height->text().toDouble() + down_up));
		ui.Re_Height->setText(QString::number(ui.Re_Height->text().toDouble() + down_up));
		ChangeInput();
	}
	else if (ui.Box_Height->hasFocus())
	{
		ui.Box_Height->setText(QString("%2").arg(ui.Box_Height->text().toDouble() + down_up));
		BoxLengthChangeInput();
	}
	else if (ui.Box_Width->hasFocus())
	{
		ui.Box_Width->setText(QString("%2").arg(ui.Box_Width->text().toDouble() + down_up));
		BoxLengthChangeInput();
	}
	else if (ui.Box_X_Posi->hasFocus())
	{
		ui.Box_X_Posi->setText(QString("%2").arg(ui.Box_X_Posi->text().toDouble() + down_up));
		BoxMidPosiChangeInput();
	}
	else if (ui.Box_Y_Posi->hasFocus())
	{
		ui.Box_Y_Posi->setText(QString("%2").arg(ui.Box_Y_Posi->text().toDouble() + down_up));
		BoxMidPosiChangeInput();
	}
	else if (ui.ScallX->hasFocus())
	{
		double _x = ui.ScallX->text().toDouble();
		if (down_up == -1 && _x  > 0 && _x < 0.2)
		{
			ui.ScallX->setText("0");
		}
		else if (down_up == 1 && _x < 0 && _x > -0.2)
		{
			ui.ScallX->setText("0");
		}
		else
		{
			ui.ScallX->setText(QString("%2").arg(ui.ScallX->text().toDouble() + (down_up * 0.1)));
		}
		ChangeInput();
	}
	else if (ui.ScallY->hasFocus())
	{
		double _y = ui.ScallY->text().toDouble();
		if (down_up == -1 && _y  > 0 && _y < 0.2)
		{
			ui.ScallY->setText("0");
		}
		else if (down_up == 1 && _y < 0 && _y > -0.2)
		{
			ui.ScallY->setText("0");
		}
		else
		{
			ui.ScallY->setText(QString("%2").arg(ui.ScallY->text().toDouble() + (down_up * 0.1)));
		}
		//ui.ScallY->setText(QString::number(ui.ScallY->text().toDouble() + (down_up * 0.1)));
		//ReChangeInput();
		ChangeInput();
	}
	else if (ui.Rotate3D_X->hasFocus())
	{
		ui.Rotate3D_X->setText(QString("%2").arg(ui.Rotate3D_X->text().toDouble() + down_up));
		Rotate3D_ChangeINput();
	}
	else if (ui.Rotate3D_Y->hasFocus())
	{
		ui.Rotate3D_Y->setText(QString("%2").arg(ui.Rotate3D_Y->text().toDouble() + down_up));
		Rotate3D_ChangeINput();
	}
	else if (ui.Rotate3D_Z->hasFocus())
	{
		ui.Rotate3D_Z->setText(QString("%2").arg(ui.Rotate3D_Z->text().toDouble() + down_up));
		Rotate3D_ChangeINput();
	}
	else if (ui.modelTransPosX->hasFocus()){
		ui.modelTransPosX->setText(QString("%2").arg(ui.modelTransPosX->text().toDouble() + down_up));
		modelShowPosTransition();
	}
	else if (ui.modelTransPosY->hasFocus()){
		ui.modelTransPosY->setText(QString("%2").arg(ui.modelTransPosY->text().toDouble() + down_up));
		modelShowPosTransition();
	}
	else if (ui.St_Width->text() != "")
	{
		if (ui.St_Width->hasFocus())
		{
			ui.St_Width->setText(QString::number(ui.St_Width->text().toDouble() + down_up));
		}
		else if (ui.St_Height->hasFocus())
		{
			ui.St_Height->setText(QString::number(ui.St_Height->text().toDouble() + down_up));
		}
		else if (ui.En_Width->hasFocus())
		{
			ui.En_Width->setText(QString::number(ui.En_Width->text().toDouble() + down_up));
		}
		else if (ui.En_Height->hasFocus())
		{
			ui.En_Height->setText(QString::number(ui.En_Height->text().toDouble() + down_up));
		}
		else if (ui.Rotate->hasFocus())
		{
			ui.Rotate->setText(QString::number(ui.Rotate->text().toDouble() + down_up));
		}
		else
			return;
		BoxChangeInput("");
		pu = 1;
	}
}

void QtEdit::saveAllData()
{
	if (_animateLineButton.size() > 0 )
	{
		QString str = _QtEdit->windowTitle();
		str = str.split("*").at(0);
		_QtEdit->setWindowTitle(str);
		Export_Data * ex = Export_Data::getinstance();
		ex->Data_TO_Relatite(_allClickButton, _animateLineButton);
		ex->Export_SaveData(_animateLineButton, saveDataName.toLocal8Bit().data());
	}
	
}

void QtEdit::importSpine()
{
	QString file_name;
	QString filter = openSpineFile_Path;;
	if (openSpineFile_Path.lastIndexOf(".") != -1)
	{
		filter = "atlas files (*.atlas);;all files (*)";
	}
	if (this->windowTitle().indexOf("*") != -1)
	{
		QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有操作保存，是否先保存再导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (rb == QMessageBox::Yes)
		{
			//import();
			Export_Data *_Export_Data = Export_Data::getinstance();
			_Export_Data->Data_TO_Relatite(_allClickButton , _animateLineButton);
			_Export_Data->Export_SaveData(_animateLineButton, saveDataName.toLocal8Bit().data());
		}
	}
	file_name = QFileDialog::getOpenFileName(this,
		codec->toUnicode("导入atlas文件"), openSpineFile_Path, filter);
	if (!file_name.isNull())
	{
		if (ui.PauseButton->text() == _Pausetext)
		{
			pausebuttonclick();
		}
		int i = 0;
		for (i = 0; i < _animateLineButton.size(); i++)
		{
			DEL_FREE_OBJ(_animateLineButton.at(i));
		}
		_animateLineButton.clear();
		_allClickButton.clear();
		//_last_animaID = -1;
		_last_animaname = "";
		//fileName是文件名
		is_import = true;
		MySQLite(true, file_name, "open_spine_path");
		_DrawLayer = DrawLayer::getinstance();
		//log("%d", file_name.lastIndexOf("/"));
		//QStringList strlist = file_name.split("Resources/");
		QString Re_File_name = file_name.mid(file_name.lastIndexOf("/") + 1);
		this->setWindowTitle(Re_File_name);
		QFileInfo fi;
		fi = QFileInfo(file_name);
		saveDataName = fi.path() + "/" + fi.fileName().split(".").at(0) + tr(".data");
		_filename = fi.fileName().split(".").at(0);
		animation_list.clear();
		_DrawLayer->removeAllChildrenWithCleanup(true);
		_DrawLayer->DrawInitPosi();
		_DrawLayer->initShowPosLabel();
		_allClickButton.resize(0);
		_DrawLayer->updateMySpine(file_name.toLocal8Bit().data(), (fi.path() + "/" + fi.fileName().split(".").at(0) + ".json").toLocal8Bit().data());
		SpiteS_Model = 2;
		AddAnimationList(file_name);
		ui.ListWidget->setWindowTitle("");
		if (animation_list.size() != 0)
		{
			is_import = true;
			_DrawLayer->setMySpineAnimation(animation_list.at(0).toLocal8Bit().data(), true);
			ui.ListWidget->setWindowTitle(codec->toUnicode("请选择一个动作"));
			//setPerWiget(_DrawLayer->getMySpineDuration() * oneFPX);
			//从.data文件中导入数据
			QMessageBox message(QMessageBox::NoIcon, codec->toUnicode("导入数据中，请耐心等待片刻"), "");
			message.show();
			Init();
			CheckAnimation();
			_allClickButton.resize(0);
			message.clickedButton();
			std::string str;
			std::string _ani_name;
			int _len;
			int j;
			bool Is_has;
			if (animation_list.size() != _animateLineButton.size())
			{
				for (i = 0; i < animation_list.size(); i++)
				{
					Is_has = false;
					str = animation_list.at(i).split(".").at(0).toLocal8Bit().data();
					_len = str.find_last_of("/");
					str = str.substr(_len + 1);
					for (j = 0; j < _animateLineButton.size(); j++)
					{
						if (str == _animateLineButton.at(j)->_anima_Name)
						{
							Is_has = true;
							break;
						}
					}
					if (!Is_has)
					{
						MyLineVector * _MyLineVector = new MyLineVector();
						_MyLineVector->_anima_Name = str;
						_animateLineButton.push_back(_MyLineVector);
					}
				}
			}

			if (animation_list.size() != _animateLineButton.size())
			{
				for (i = 0; i < _animateLineButton.size(); i++)
				{
					Is_has = false;
					for (j = 0; j < animation_list.size(); j++)
					{
						str = animation_list.at(j).split(".").at(0).toLocal8Bit().data();
						_len = str.find_last_of("/");
						str = str.substr(_len + 1);
						if (str == _animateLineButton.at(i)->_anima_Name)
						{
							Is_has = true;
							break;
						}
					}
					if (!Is_has)
					{
						DEL_FREE_OBJ(_animateLineButton[i]);
						_animateLineButton.removeAt(i);
						i--;
					}
				}
			}

		}
		else
		{
			//QMessageBox::about(this, tr("information"), tr("No animations"));
			QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有animations"));
		}

	}
	else{
		//点的是取消
	}
}

void QtEdit::on_actionImporteffect_triggered()
{
	QString filter = tr("c3b Files (*.c3b);; c3t Files (*.c3t);; all Files (*)");
	QStringList pathList = QFileDialog::getOpenFileNames(this,
		codec->toUnicode("导入特效文件"), openC3bFile_Path, filter);
}

void QtEdit::export_byteData()
{
	if (_animateLineButton.size() <= 0)
	{
		QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有导入资源,请先导入资源"));
		//QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有导入资源，是否先导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		//if (rb == QMessageBox::Yes)
		//{
		//	import();

		//}

	}
	else
	{
		export_Byte_Path = saveDataName;
		export_Byte_Path = export_Byte_Path.split(".").at(0);
		QString fileName = QFileDialog::getSaveFileName(this,
			codec->toUnicode("导出二进制数据"),
			export_Byte_Path,
			tr("byte Files (*.byte);; all files (*)"));

		if (!fileName.isNull())
		{
			int i;
			//fileName是文件名
			MySQLite(true, fileName, "byte_path");
			Export_Data *_Export_Data = Export_Data::getinstance();
			_Export_Data->Data_TO_Relatite(_allClickButton,_animateLineButton);
			_Export_Data->Export_ByteData(_animateLineButton, fileName.toLocal8Bit().data());
		}
		else
		{
			//点的是取消
		}
	}
	
}

void QtEdit::deletePro()
{
	DEL_FREE_OBJ(scrollArea->parent());
}
void QtEdit::closeEvent(QCloseEvent *event)
{
	int i;
	if (this->windowTitle().indexOf("*") != -1)
	{
		std::string showabout = "当前未保存是否退出?";
		switch (QMessageBox::warning(this, codec->toUnicode("警告"), codec->toUnicode(showabout.c_str()),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
		{
		case QMessageBox::Save:
			//label->setText(" Warning button / Save ");
			//_Export_Data = Export_Data::getInstence();
			//_Export_Data->DrawDataTo_Qtedit();
			//_Export_Data->Dosave_JsonData(saveDataName..toLocal8Bit().data(), spritesPoints, true);
			cocos2d::Director::getInstance()->end();
			for (i = 0; i < _animateLineButton.size(); i ++)
			{
				DEL_FREE_OBJ(_animateLineButton.at(i));
			}
			deletePro();
			exit(0);
			qApp->quit();
			event->accept();  //接受退出信号，程序退出
			break;
		case QMessageBox::Discard:
			//label->setText(" Warning button / Discard ");
			cocos2d::Director::getInstance()->end();
			for (i = 0; i < _animateLineButton.size(); i++)
			{
				DEL_FREE_OBJ(_animateLineButton.at(i));
			}
			deletePro();
			exit(0);
			qApp->quit();
			event->accept();  //接受退出信号，程序退出
			break;
		case QMessageBox::Cancel:
			//label->setText(" Warning button / Cancel ");
			event->ignore();  //忽略退出信号，程序继续运行
			break;
		default:
			break;
		}
		
	}
	else
	{
		cocos2d::Director::getInstance()->end();
		for (i = 0; i < _animateLineButton.size(); i++)
		{
			DEL_FREE_OBJ(_animateLineButton.at(i));
		}
		exit(0);
		qApp->quit();
		event->accept();  //接受退出信号，程序退出
	}
}
void QtEdit::resizeEvent(QResizeEvent * event)
{
	int _width = this->width();
	int _height = this->height();
	buttonWidget->setGeometry(QRect(0, 20, 8000, _height - 720));
	//_LinesTableWidget->setGeometry(QRect(0, 45, _width - 70, _height - 800));
	scrollArea->setGeometry(QRect(0, 20, _width, _height - 740));
	_LinesTableWidget->setGeometry(QRect(0, 45, _LinesTableWidget->width(), scrollArea->height()));
	ui.showmessage->setGeometry(QRect(0, 0, ui.OutWiget->width(), ui.OutWiget->height()));
	ui.AnimationtreeWidget->setGeometry(QRect(0, 0, ui.ListWidget->width(), ui.ListWidget->height()));
	QSize off = QSize(_width - sourceSize.width(), _height - sourceSize.height());
	ui.PerWiget->setMinimumSize(perWidgeBaseSize.width()+ off.width(), perWidgeBaseSize.height()+ off.height());
}

void QtEdit::setGLView(QWidget *glWidget)
{
	_glWidget = glWidget;

	if (_glWidget)
	{
		this->setParent((HWND)glWidget->winId());
 		ui.SceneWidget->setWidget(_glWidget);
		_glWidget->setFixedHeight(639);
 		setCentralWidget(ui.SceneWidget);
	}
}
void QtEdit::MySQLite(bool is_Update /* = false */, QString data /* = 0  */, QString col_name /* = "" */)
{
	int i;
	if (!is_Update)
	{
		DBUtil *db = DBUtil::getInstance();
		db->openDBWithName("QtEditSQLite");
		//db->deleteTable("DROP TABLE IF EXISTS tb_FilePath;", "tb_FilePath");
		db->createTable("create table if not exists tb_FilePath(open_c3b_path VARCHAR(50) NOT NULL ,open_spine_path VARCHAR(50) NOT NULL, byte_path VARCHAR(50) NOT NULL , json_path VARCHAR(50) NOT NULL)", "tb_FilePath");
		std::vector<std::map<std::string, std::string> > SQL_data = db->searchData("select * from tb_FilePath");
		if (SQL_data.size() == 0)
		{
			db->insertData("insert into tb_FilePath values('./' , './', './' , './')");
		}
		for (i = 0; i < SQL_data.size(); i++)
		{
			map<string, string> temp = SQL_data.at(i);
			//temp.at(0).at(1);
			for (map<string, string>::iterator iter = temp.begin(); iter != temp.end(); ++iter)
			{
				//log("%s:%s", iter->first.c_str(), iter->second.c_str());
				if (iter->first == "byte_path")
				{
					export_Byte_Path = iter->second.c_str();
				}
				else if (iter->first == "json_path")
				{
					export_Json_Path = iter->second.c_str();
				}
				else if (iter->first == "open_spine_path")
				{
					openSpineFile_Path = iter->second.c_str();
				}
				else
				{
					openC3bFile_Path = iter->second.c_str();
				}
				//openFile_Path = iter->second.c_str();
			}
		}
		db->closeDB();
	}
	else
	{
		DBUtil *db = DBUtil::getInstance();
		db->openDBWithName("QtEditSQLite");
		std::sprintf(myshowstr, "update tb_FilePath set %s = '%s'", col_name.toLocal8Bit().data(), data.toLocal8Bit().data());
		db->updateData(myshowstr);
		db->closeDB();
		if (col_name == "open_c3b_path")
		{
			openC3bFile_Path = data;
		}
		else if (col_name == "json_path")
		{
			export_Json_Path = data;
		}
		else if (col_name == "open_spine_path")
		{
			openSpineFile_Path = data;
		}
		else
		{
			export_Byte_Path = data;
		}
	}
}
void QtEdit::exportData()
{
	//ShowMsg("Export");
	if (_animateLineButton.size() <= 0)
	{
		//QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有导入资源，是否先导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		//if (rb == QMessageBox::Yes)
		//{
		//	import();
		//	
		//}
		QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有导入资源，请先导入资源"));
	}
	else
	{
		QString fileName = QFileDialog::getSaveFileName(this,
			codec->toUnicode("导出JSON文件"),
			export_Json_Path,
			tr("json Files (*.json);; all files (*)"));

		if (!fileName.isNull())
		{
			//fileName是文件名
			//doSaveData(fileName);
			
			MySQLite(true, fileName, "json_path");
			Export_Data *_Export_Data = Export_Data::getinstance();
			_Export_Data->Data_TO_Relatite(_allClickButton,_animateLineButton);
			_Export_Data->Export_JSONData(_animateLineButton, fileName.toLocal8Bit().data());
		}
		else
		{
			//点的是取消
		}
	}
	
}

void QtEdit::ReChangeInput()
{
	spritePos.x = floatToInt(ui.Re_Width->text().toInt() + _IN_Width);
	spritePos.y = floatToInt(ui.Re_Height->text().toInt() + _IN_Height);
	//ui.Width->setText(QString("%2").arg(ui.Re_Width->text().toInt() + _IN_Width));
	//ui.Height->setText(QString("%2").arg(ui.Re_Height->text().toInt() + _IN_Height));
	ChangeInput();
}

void QtEdit::ActionHelp()
{
	//QMessageBox::aboutQt(NULL, "About Qt");
	std::string showabout = "";
	showabout = "cocos Action Edit是FBX用cocos2dx自带的转换器转换到c3b或c3t中，支持一个model多个Animation的动作编辑器\n";
	showabout += "贴图的名字必须和model的一样，并且贴图文件是.png格式，动作的c3b和c3t必须放在animations文件夹下\n";
	showabout += "本编辑器还支持Spine的操作，Spine的文件要求是json文件和atlas文件名必须一致，否则出错,\n";
	showabout += "这个编辑器支持保存操作、导出二进制文件和导出json格式操作。二进制文件格式为自己的格式";
	showabout += "\n本编辑器存在很多问题。如发现问题发邮件到：liweicg@gmail.com";
	showabout += "\nCopyRight(©) killer & TimeNew Studios";
	QMessageBox::about(NULL, "About Edit", codec->toUnicode(showabout.c_str()));
}

void QtEdit::openData()
{
	QDir dir;
	std::sprintf(myshowstr, "cmd   /c   %s/RunScore/StartFBXToCocos.bat", dir.currentPath().toLocal8Bit().data());
	WinExec(myshowstr, SW_HIDE);
	std::sprintf(myshowstr, "cmd   /c   %s/StartFBXToCocos.bat", dir.currentPath().toLocal8Bit().data());
	WinExec(myshowstr, SW_HIDE);
}
void QtEdit::import()
{
	_DrawLayer = DrawLayer::getinstance();
	QString file_name;
	QString filter = openC3bFile_Path;;
	if (openC3bFile_Path.lastIndexOf(".") != -1)
	{
		if (openC3bFile_Path.mid(openC3bFile_Path.lastIndexOf(".") + 1) != "c3t")
		{
			filter = tr("c3b Files (*.c3b);; c3t Files (*.c3t);; all Files (*)");
		}
		else
		{
			filter = tr("c3t Files (*.c3t);; c3b Files (*.c3b);; all Files (*)");
		}
	}
	if (this->windowTitle().indexOf("*") != -1)
	{
		QMessageBox::StandardButton rb = QMessageBox::question(NULL, "information", codec->toUnicode("当前没有操作保存，是否先保存再导入资源?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (rb == QMessageBox::Yes)
		{
			Export_Data * ex = Export_Data::getinstance();
			ex->Data_TO_Relatite(_allClickButton, _animateLineButton);
			ex->Export_SaveData(_animateLineButton, saveDataName.toLocal8Bit().data());
		}
	}
	file_name = QFileDialog::getOpenFileName(this,
		codec->toUnicode("导入文件"), openC3bFile_Path, filter);
	if (!file_name.isNull())
	{
		
		if (ui.PauseButton->text() == _Pausetext)
		{
			pausebuttonclick();
		}
		//fileName是文件名
		int i = 0;
		for (i = 0; i < _animateLineButton.size(); i ++)
		{
			DEL_FREE_OBJ(_animateLineButton.at(i));
		}
		_animateLineButton.clear();
		_allClickButton.clear();
		//_last_animaID = -1;
		_last_animaname = "";
		SpiteS_Model = 1;
		MySQLite(true, file_name, "open_c3b_path");
		//log("%d", file_name.lastIndexOf("/"));
		//QStringList strlist = file_name.split("Resources/");
		QString Re_File_name = file_name.mid(file_name.lastIndexOf("/") + 1);
		this->setWindowTitle(Re_File_name);

		if (_DrawLayer->_sprite)
		{
			_DrawLayer->removeChild(_DrawLayer->_sprite, true);
		}

		QFileInfo fi;
		fi = QFileInfo(file_name);
		saveDataName = fi.path() + "/" + fi.fileName().split(".").at(0) + tr(".data");
		_filename = fi.fileName().split(".").at(0);
		animation_list.clear();
		_DrawLayer->removeAllChildrenWithCleanup(true);
		_DrawLayer->DrawInitPosi();

		AddAnimationList(file_name);
		ui.ListWidget->setWindowTitle("");
		if (animation_list.size() != 0)
		{
			ui.ListWidget->setWindowTitle(codec->toUnicode("请选择一个动作"));
			_DrawLayer->updateMySprite3D(file_name.toLocal8Bit().data(), 
				QString(file_name.split(".").at(0) + ".png").toLocal8Bit().data(), animation_list.at(0).toLocal8Bit().data());
			//ui.dockWidget->setWindowTitle(animation_list.at(0));
			FPX = _DrawLayer->animate->getDuration() * oneFPX;
			//setPerWiget(FPX);
			//从.data文件中导入数据
			int i, j;
			bool Is_has = false;
			QMessageBox message(QMessageBox::Warning, codec->toUnicode("导入数据中，请耐心等待片刻"), "");
			message.show();
			Init();
			CheckAnimation();
			_allClickButton.resize(0);
			message.clickedButton();
			std::string str;
			std::string _ani_name;
			int _len;
			if (animation_list.size() != _animateLineButton.size())
			{
				for (i = 0; i < animation_list.size(); i++)
				{
					Is_has = false;
					str = animation_list.at(i).split(".").at(0).toLocal8Bit().data();
					_len = str.find_last_of("/");
					str = str.substr(_len + 1);
					for (j = 0; j < _animateLineButton.size(); j++)
					{
						if (str == _animateLineButton.at(j)->_anima_Name)
						{
							Is_has = true;
							break;
						}
					}
					if (!Is_has)
					{
						MyLineVector * _MyLineVector = new MyLineVector();
						_MyLineVector->_anima_Name = str;
						_animateLineButton.push_back(_MyLineVector);
					}
				}
			}
			if (animation_list.size() != _animateLineButton.size())
			{
				for (i = 0; i < _animateLineButton.size(); i++)
				{
					Is_has = false;
					for (j = 0; j < animation_list.size(); j ++)
					{
						str = animation_list.at(j).split(".").at(0).toLocal8Bit().data();
						_len = str.find_last_of("/");
						str = str.substr(_len + 1);
						if (str == _animateLineButton.at(i)->_anima_Name)
						{
							Is_has = true;
							break;
						}
					}
					if (!Is_has)
					{
						//DEL_FREE_OBJ(_animateLineButton.at(i));
						DEL_FREE_OBJ(_animateLineButton[i]);
						_animateLineButton.removeAt(i);
						i--;
					}
				}
			}
			DrawLayer::getinstance()->setSpriteRotate3D(_Rotate_3d_x , _Rotate_3d_y , _Rotate_3d_z);
			ui.Rotate3D_X->setText(QString("%2").arg(_Rotate_3d_x));
			ui.Rotate3D_Y->setText(QString("%2").arg(_Rotate_3d_y));
			ui.Rotate3D_Z->setText(QString("%2").arg(_Rotate_3d_z));

		}
		else
		{
			//QMessageBox::about(this, tr("information"), tr("No animations"));
			QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有animations"));
		}

	}
	else{
		//点的是取消
	}
}

void QtEdit::CheckAnimation()
{
	int i, j;
	int len;
	std::string str;
	std::string _ani_name;
	MyLineVector * _ani_line;
	bool _is_has;
	for (i = 0; i < _animateLineButton.size(); i++)
	{
		_ani_line = _animateLineButton.at(i);
		str = _ani_line->_anima_Name;
		len = str.find_last_of("/");
		str = str.substr(len + 1);
		_is_has = false;
		for (j = 0; j < animation_list.size(); j ++)
		{
			_ani_name = animation_list.at(j).toLocal8Bit().data();
			len = _ani_name.find_last_of("/");
			_ani_name = _ani_name.substr(len + 1);
			len = _ani_name.find_last_of(".");
			if (-1 != len)
			{
				_ani_name = _ani_name.substr(0, len);
			}
			if (_ani_name == str)
			{
				_is_has = true;
				break;;
			}

		}
		if (false == _is_has)
		{
			//DEL_FREE_OBJ(_ani_line);
			DEL_FREE_OBJ(_animateLineButton[i]);
			_animateLineButton.removeAt(i);
			i--;
		}
	}
}

void QtEdit::clearAllClickButton(int col)
{
	int i;
	int j = 0;
	QVector<ClickButton*>_templine;
	ClickButton *_temp;
	_retaliteAllClickButton.clear();
	for (i = 0; i < _allClickButton.size(); i++)
	{
		_templine.clear();
		for (j = 0; j < _allClickButton.at(i).size(); j++)
		{
			_temp = _allClickButton.at(i).at(j)->copy();
			_templine.push_back(_temp);
		}
		_retaliteAllClickButton.push_back(_templine);
	}
	for (i = 0; i < _animateLineButton.size(); i++)
	{
		//if (_animateLineButton.at(i)->_anima_ID == _last_animaID)
		if (_animateLineButton.at(i)->_anima_Name == _last_animaname)
		{
			_animateLineButton.at(i)->_lineButton = _retaliteAllClickButton;
			break;
		}
	}
	if (_animateLineButton.size() == 0)
	{
		for (i = 0; i < animation_list.size(); i++)
		{
			_MyLineVector = new MyLineVector();
			//_MyLineVector->_anima_ID = i;
			std::string str = animation_list[i].toLocal8Bit().data();
			int  _leng;
			if (str.find_last_of("/") == -1)
			{
				_leng = 0;
			}
			else
			{
				_leng = str.find_last_of("/");
			}
			str = str.substr(_leng);
			int _len = str.find_last_of(".");

			if (_len != -1)
			{
				str = str.substr(1, _len - 1);
			}
			_MyLineVector->_anima_Name = str;
			_animateLineButton.push_back(_MyLineVector);
		}
	}
	_last_animaname = animation_list.at(col).split(".").at(0).toLocal8Bit().data();
	int _len = _last_animaname.find_last_of("/");
	_last_animaname = _last_animaname.substr(_len + 1);
}

void QtEdit::resetClickButton(int col)
{
	if (1 == getSpriteModel())
	{
		ShowMsg(QString("animations/" + animation_list.at(col).split("animations/").at(1)).toLocal8Bit().data());
		_DrawLayer->_sprite->stopAllActions();
		//CC_SAFE_RELEASE(_DrawRectLayer->animation);
		//CC_SAFE_RELEASE(_DrawRectLayer->animate);
		_DrawLayer->animation = Animation3D::getOrCreate(animation_list.at(col).toLocal8Bit().data());
		if (_DrawLayer->animation != NULL)
		{
			_DrawLayer->animate = Animate3D::create(_DrawLayer->animation);
			_DrawLayer->animate->is_auto_update = false;
			_DrawLayer->_RepeatForever = RepeatForever::create(_DrawLayer->animate);
			_DrawLayer->_sprite->runAction(_DrawLayer->_RepeatForever);
		}
		ui.ListWidget->setWindowTitle(animation_list.at(col));
		FPX = _DrawLayer->animation->getDuration() * oneFPX;
		setPerWiget(FPX);
		Init_ClickButton(col);
	}
	else
	{
		ShowMsg(animation_list.at(col).toLocal8Bit().data());
		//_DrawRectLayer->MySpineUnUpdate();
		_DrawLayer->setMySpineAnimation(animation_list.at(col).toLocal8Bit().data());
		ui.ListWidget->setWindowTitle(animation_list.at(col));
		FPX = _DrawLayer->getMySpineDuration() * oneFPX;
		setPerWiget(FPX);
		Init_ClickButton(col);
	}
	SeleteLineRow = 0;
	selectRow = 0;
	selectCol = 1;
	if (_QtEdit->_allClickButton.at(0).size() > 0)
	{
		_QtEdit->_allClickButton.at(selectRow).at(selectCol - 1)->Click_ED(true);
	}
	else
	{
		selectRow = -1;
		selectCol = 0;
		QMessageBox::warning(this, codec->toUnicode("警告"), codec->toUnicode("当前帧数为0"));
	}
	SpriteChange();

}


void QtEdit::setPerWiget(int max)
{
	SeleteLineRow = -1;
	PencentageSlider->setGeometry(QRect(40, 0, FPX * 40, 50));
	PencentageSlider->setMaximum(max);
	PencentageSlider->setMinimum(1);
	PencentageSlider->setValue(0);

	_LinesTableWidget->setColumnCount(FPX);
	_LinesTableWidget->setRowCount(0);
	_LinesTableWidget->setGeometry(QRect(0, 45, FPX * 40 + 40 , scrollArea->height()));
	//scrollArea->setGeometry(QRect(0, 20, FPX * 40 + 40, scrollArea->height()));
}
//读取json
void QtEdit::Init()
{
	Json::Value root_json;
	Json::Value _anima_json;
	Json::Value _line_anima;
	Json::Value _item;
	Json::Value ObjectItem;
	Json::Value _item_item;
	Json::Value _saItem;
	QVector<QVector<ClickButton *>> _lineButton;
	ClickButton * _temp;
	DrawNodeVertices * _drawNodeVertices;
	std::string _ani_name;
	int _anima_ID;
	int _line_ID;
	int i;
	int j;
	int k;
	double _ScallX;
	double _ScallY;
	double Width;
	double Height;
	double _last_w;
	double _last_h;
	double _last_sx;
	double _last_sy;
	double st_x;
	double st_y;
	double en_x;
	double en_y;
	double _rotate;
	int _row;
	int _col;
	int frame_model;
	bool _is_frame;
	bool _is_null;
	bool _is_gravity;
	Json::Reader _reader;
	QFile file(saveDataName);
	QVector<ClickButton *> _linebtn;
	MyLineVector * _lineVector;
	_drawNodeVertices;
	_animateLineButton.clear();
	if (!file.exists())
	{
		file.open(QIODevice::ReadWrite);
		file.close();
		return;
	}
	QString _MyData = NULL;
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::about(this, tr("information"), tr("Read ERROR"));
		return;
	}
	//_MyData = QByteArray::fromBase64(file.readAll());
	_MyData = file.readAll();
	file.close();
	if (!_reader.parse(_MyData.toLocal8Bit().data(), root_json))
	{
		return;
	}	
	std::string _opfile = saveDataName.toLocal8Bit().data();
	std::string str = _opfile.substr(_opfile.find_last_of("/"));
	int _len = str.find_last_of(".");
	str = str.substr(1, _len - 1);
	_Rotate_3d_x = root_json["rotate3d_x"].asDouble();
	if (!root_json["rotate3d_y"].isNull())
	{
		_Rotate_3d_y = root_json["rotate3d_y"].asDouble();
	}
	_Rotate_3d_z = root_json["rotate3d_z"].asDouble();
	_anima_json = root_json[str];
	for (k = 0; k < _anima_json.size(); k ++)
	{
		_saItem = _anima_json[k];
		_ani_name = _saItem["name"].asCString();
		
		//_anima_ID = _saItem["ID"].asDouble();
		_line_anima = _saItem["_data"];
		_lineVector = new MyLineVector();
		//_lineVector->_anima_ID = _anima_ID;
		_lineVector->_anima_Name = _ani_name;
		Point transPos = Point(_saItem["transPos_X"].asDouble(), _saItem["transPos_Y"].asDouble());
		_lineVector->transPos = transPos;
		_allClickButton.clear();
		int lineSize = _line_anima.size();
		for (i = 0; i < _line_anima.size(); i ++)
		{
			ObjectItem = _line_anima[i];
			_line_ID = ObjectItem["line_id"].asDouble();
			_item_item = ObjectItem["line_data"];
			auto count = _item_item.size();
			_linebtn.clear();
			int itemsize = _item_item.size();
			int last_rol = -1;
			int index = 0;
			for (int ss = 0; ss < animation_list.size(); ss++){
				QString str = animation_list.at(ss);
				str = str.section("/", -1).section(".", 0, -2);
				if (str == _ani_name.c_str()){
					index = ss;
				}
			}
			//这里的last_rol可能有错误，原来的话last_rol最多只有61但实际上可能超过61所以这里导入的时候要重设置为count
			if (1 == SpiteS_Model)
			{
				_DrawLayer->animation = Animation3D::getOrCreate(animation_list.at(index).toLocal8Bit().data());
				//last_rol = _DrawLayer->animation->getDuration() * oneFPX;
				last_rol = count;
			}
			else
			{
				_DrawLayer->setMySpineAnimation(animation_list.at(index).toLocal8Bit().data());
				//last_rol = _DrawLayer->getMySpineDuration() * oneFPX;
				last_rol = count;
			}
			if (itemsize > last_rol){
				itemsize = last_rol;
			}
			//先把它初始化好
			for (j = 0; j < itemsize; j++)
			{
				_temp = new ClickButton(0, 0, 0);
				_linebtn.push_back(_temp);
			}
			for (j = 0; j < itemsize; j++)
			{
				_item = _item_item[j];
				_ScallX = _item["_ScallX"].asDouble();
				_ScallY = _item["_ScallY"].asDouble();
				Width = _item["Width"].asDouble();
				Height = _item["Height"].asDouble();
				_last_w = _item["_last_w"].asDouble();
				_last_h = _item["_last_h"].asDouble();
				_last_sx = _item["_last_sx"].asDouble();
				_last_sy = _item["_last_sy"].asDouble();
				st_x = _item["st_x"].asDouble();
				st_y = _item["st_y"].asDouble();
				en_x = _item["en_x"].asDouble();
				en_y = _item["en_y"].asDouble();
				_rotate = _item["_rotate"].asDouble();
				_row = _item["_row"].asDouble();
				_col = _item["_col"].asDouble();
				_is_frame = _item["_is_frame"].asBool();
				frame_model = _item["frame_model"].asDouble();
				_is_null = _item["_is_null"].asBool();
				if (!_item["_is_gravity"].isNull())
				{
					_is_gravity = _item["_is_gravity"].asBool();
				}
				else
				{
					_is_gravity = true;
				}

				//_temp = new ClickButton(_row , _col, frame_model);
				_temp = _linebtn.at(_col - 1);
				_temp->setCol(_col);
				_temp->setRow(_row);
				_temp->setFrameModel(frame_model);
				_temp->setFrame(_is_frame);
				_temp->setIsNULL(_is_null);
				_temp->setGravity(_is_gravity);
				_temp->_Width = Width;
				_temp->_Height = Height;
				_temp->_ScallX = _ScallX;
				_temp->_ScallY = _ScallY;
				_drawNodeVertices = _temp->_DrawNodeVertices;
				_drawNodeVertices->_last_Height = _last_h;
				_drawNodeVertices->_last_Width = _last_w;
				_drawNodeVertices->_last_ScallX = _last_sx;
				_drawNodeVertices->_last_ScallY = _last_sy;
				_drawNodeVertices->Relativevertices[0].set(st_x, st_y);
				_drawNodeVertices->Relativevertices[2].set(en_x, en_y);
				_drawNodeVertices->Rotate = _rotate;
				_drawNodeVertices->updateRetlativeVertices();
			}
			_allClickButton.push_back(_linebtn);
			if (_linebtn.size() > 0)
				_allClickButton.at(i).at(0)->setLineID(_line_ID);
		}
		_lineVector->_lineButton = _allClickButton;
		_animateLineButton.push_back(_lineVector);
	}
	int a = 1;
}


//Slider下的Button响应
void QtEdit::SlderButtonClick()
{
	

	
}

void QtEdit::AddScallAreaWidget()
{
	_now_linesize = 1;
	buttonWidget = new QWidget(ui.PerWiget);
	buttonWidget->setPalette(QPalette(Qt::gray));
	buttonWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea = new QScrollArea(ui.PerWiget);
	scrollArea->setAlignment(Qt::AlignCenter);
	//scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(buttonWidget);
	scrollArea->setGeometry(QRect(0, 20, 1770, 230));
	scallbar = scrollArea->horizontalScrollBar();
	buttonWidget->setGeometry(QRect(0, 0, 8000, 210));

	PencentageSlider->setParent(buttonWidget);
	PencentageSlider->setGeometry(QRect(40, 0, FPX * 40, 50));
	PencentageSlider->setMinimum(1);
	PencentageSlider->setMaximum(30);

	_LinesTableWidget = new QTableWidget(buttonWidget);
	//QStringList header;
	//header << "Month" << "Description";
	QHeaderView *headerView = _LinesTableWidget->horizontalHeader();
	headerView->setSectionResizeMode(QHeaderView::Fixed);//去除表头的移动
	headerView = _LinesTableWidget->verticalHeader();
	headerView->setSectionResizeMode(QHeaderView::Fixed);//去除表头的移动
	_LinesTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	_LinesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	_LinesTableWidget->setVerticalHeaderLabels(_lineVerHeader);
	_LinesTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	_LinesTableWidget->horizontalHeader()->setLineWidth(20);
	_LinesTableWidget->hasAutoScroll();
	_LinesTableWidget->setShowGrid(true);
	_LinesTableWidget->setStyleSheet("background: transparent;border:0px");
	QObject::connect(_LinesTableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnTableWidgetSelect()));
	//_LinesTableWidget->setRangeSelected(QHeaderView::Fixed);

	_LinesTableWidget->setGeometry(QRect(0, 45, 1700, scrollArea->height()));
	Add_LineBtn = new QPushButton(buttonWidget);
	Add_LineBtn->setIcon(QIcon("addbtn_png.png"));
	//Add_LineBtn->setFlat(true);
	Add_LineBtn->setGeometry(QRect(0, 15, 40, 20)); 
	Add_LineBtn->setAutoFillBackground(true);
	Add_LineBtn->setPalette(QPalette(Qt::yellow));
	QObject::connect(Add_LineBtn, SIGNAL(clicked()), this, SLOT(AddLineButton_Click()));

}



void QtEdit::showmessageChange()
{
	
	mymsg = ui.showmessage->toPlainText().toLocal8Bit().data();
}

void QtEdit::Rotate3D_ChangeINput()
{
	if (SpiteS_Model == 1)
	{
		if (_animateLineButton.size() > 0)
		{
			_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
			_Rotate_3d_x = ui.Rotate3D_X->text().toDouble();
			_Rotate_3d_y = ui.Rotate3D_Y->text().toDouble();
			_Rotate_3d_z = ui.Rotate3D_Z->text().toDouble();
			DrawLayer::getinstance()->setSpriteRotate3D(_Rotate_3d_x, _Rotate_3d_y, _Rotate_3d_z);
			
		}
	}
}
void QtEdit::BoxLengthChangeInput()
{
	if (_allClickButton.size() > 0)
	{
		_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
		_tempClickButton = _tempClickButton = _allClickButton.at(selectRow).at(selectCol);
		DrawNodeVertices * _DrawNodeVertices = _tempClickButton->_DrawNodeVertices;
		double _width = abs(_DrawNodeVertices->Relativevertices[0].x - _DrawNodeVertices->Relativevertices[2].x);	
		double _height = abs(_DrawNodeVertices->Relativevertices[0].y - _DrawNodeVertices->Relativevertices[2].y);
		double _input_width = ui.Box_Width->text().toDouble();
		double _input_height = ui.Box_Height->text().toDouble();
		double _reinput;

		_width = doubleToDoubletwo(_width);
		_height = doubleToDoubletwo(_height);
		_input_width = doubleToDoubletwo(_input_width);
		_input_height = doubleToDoubletwo(_input_height);
		int _Rotate = ui.Rotate->text().toInt();
		if (_width != _input_width)
		{
			_reinput = _width - _input_width;
			_reinput = _reinput / 2;
			_DrawNodeVertices->Relativevertices[0].set(_DrawNodeVertices->Relativevertices[0].x + _reinput, _DrawNodeVertices->Relativevertices[0].y);
			_DrawNodeVertices->Relativevertices[2].set(_DrawNodeVertices->Relativevertices[2].x - _reinput, _DrawNodeVertices->Relativevertices[2].y);
			_DrawNodeVertices->updateRetlativeVertices();
		}
		else
		{
			_reinput = _height - _input_height;
			_reinput = _reinput / 2;
			_DrawNodeVertices->Relativevertices[0].set(_DrawNodeVertices->Relativevertices[0].x, _DrawNodeVertices->Relativevertices[0].y - _reinput);
			_DrawNodeVertices->Relativevertices[2].set(_DrawNodeVertices->Relativevertices[2].x, _DrawNodeVertices->Relativevertices[2].y + _reinput);
			_DrawNodeVertices->updateRetlativeVertices();
		}
		_tempClickButton->_DrawNodeVertices->setRotateRelativeVertices(_tempClickButton->_DrawNodeVertices->Relativevertices[0], _tempClickButton->_DrawNodeVertices->Relativevertices[2], _Rotate * (PI / 180));
		ClickToRepaintBar();
	}
}

void QtEdit::BoxMidPosiChangeInput()
{
	if (_allClickButton.size() > 0)
	{
		_tempClickButton = _allClickButton.at(selectRow).at(selectCol);
		DrawNodeVertices * _DrawNodeVertices = _tempClickButton->_DrawNodeVertices;
		double _x = spritePos.x;
		double _y = spritePos.y;
		_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
		double _inputX = ui.Box_X_Posi->text().toDouble();
		double _inputY = ui.Box_Y_Posi->text().toDouble();
		double _posiX = _tempClickButton->_DrawNodeVertices->getRelateMidPoint().x - _x;
		double _posiY = _tempClickButton->_DrawNodeVertices->getRelateMidPoint().y - _y;
		double _Rotate = ui.Rotate->text().toDouble();
		double _reposi;
		_inputX = doubleToDoubletwo(_inputX);
		_inputY = doubleToDoubletwo(_inputY);
		_posiX = doubleToDoubletwo(_posiX);
		_posiY = doubleToDoubletwo(_posiY);
		if (_inputX != _posiX)
		{
			_reposi = _inputX - _posiX;
			_DrawNodeVertices->Relativevertices[0].set(_DrawNodeVertices->Relativevertices[0].x + _reposi, _DrawNodeVertices->Relativevertices[0].y);
			_DrawNodeVertices->Relativevertices[2].set(_DrawNodeVertices->Relativevertices[2].x + _reposi, _DrawNodeVertices->Relativevertices[2].y);
			_DrawNodeVertices->updateRetlativeVertices();
		}
		else if (_inputY != _posiY)
		{
			_reposi = _inputY - _posiY;
			_DrawNodeVertices->Relativevertices[0].set(_DrawNodeVertices->Relativevertices[0].x, _DrawNodeVertices->Relativevertices[0].y + _reposi);
			_DrawNodeVertices->Relativevertices[2].set(_DrawNodeVertices->Relativevertices[2].x, _DrawNodeVertices->Relativevertices[2].y + _reposi);
			_DrawNodeVertices->updateRetlativeVertices();
		}
		_tempClickButton->_DrawNodeVertices->setRotateRelativeVertices(_tempClickButton->_DrawNodeVertices->Relativevertices[0], _tempClickButton->_DrawNodeVertices->Relativevertices[2], _Rotate * (PI / 180));
		ClickToRepaintBar();
	}

}

void QtEdit::ChangeInput()
{
	if (_allClickButton.size() > 0 && selectCol != -1)
	{
		QString str = _QtEdit->windowTitle();
		str = str.split("*").at(0);
		str += "*";
		_QtEdit->setWindowTitle(str);
		ClickButton * _tempClick = _allClickButton.at(0).at(selectCol);
		_tempClick->setFrame(true);
		_tempClick->setButtonColor();
		_tempClick->_ScallX = ui.ScallX->text().toDouble();
		_tempClick->_ScallY = ui.ScallY->text().toDouble();
		_tempClick->_Width = spritePos.x;
		_tempClick->_Height = spritePos.y;
		ui.Re_Height->setText(QString("%2").arg(_tempClick->_Height - _IN_Height));
		ui.Re_Width->setText(QString("%2").arg(_tempClick->_Width - _IN_Width));
		_DrawLayer->setSpritePosition(_tempClick->_Width, _tempClick->_Height, _tempClick->_ScallX, _tempClick->_ScallY);
		double _x = spritePos.x;
		double _y = spritePos.y;
		double _sx = ui.ScallX->text().toDouble();
		double _sy = ui.ScallY->text().toDouble();
		double _Rotate = ui.Rotate->text().toDouble();
		_x = doubleToDoubletwo(_x);
		_y = doubleToDoubletwo(_y);
		_sx = doubleToDoubletwo(_sx);
		_sy = doubleToDoubletwo(_sy);
		_Rotate = doubleToDoubletwo(_Rotate);
		
		_tempClick = _allClickButton.at(selectRow).at(selectCol);
		_tempClick->_DrawNodeVertices->updateRetlativeVertices(_x, _y, _sx, _sy);
		Vec2 roposi;
		roposi.set(_x, _y);
		_tempClick->_DrawNodeVertices->setRotateRelativeVertices(_tempClick->_DrawNodeVertices->Relativevertices[0], _tempClick->_DrawNodeVertices->Relativevertices[2], _Rotate * (PI / 180));
		
		for (int i = 0; i < _allClickButton.size(); i ++)
		{
			_tempClick = _allClickButton.at(i).at(selectCol);
			_Rotate = _tempClick->_DrawNodeVertices->Rotate;
			_tempClick->_DrawNodeVertices->updateRetlativeVertices(_x, _y, _sx, _sy);
			_tempClick->_DrawNodeVertices->setRotateRelativeVertices(_tempClick->_DrawNodeVertices->Relativevertices[0], _tempClick->_DrawNodeVertices->Relativevertices[2], _Rotate * (PI / 180));

		}
		ClickToRepaintBar();

	}
}

void QtEdit::modelShowPosTransition()
{
	if (_allClickButton.size() > 0 && selectCol != -1)
	{
		double x = ui.modelTransPosX->text().toDouble();
		double y = ui.modelTransPosY->text().toDouble();
		auto strstr = animation_list.at(_mycol);
		QString str;
		if (getSpriteModel() == 1){
			str = animation_list.at(_mycol).section("/", -1).section(".", 0, -2);
		}
		else{
			str = animation_list.at(_mycol);
		}
		for (int i = 0; i < _animateLineButton.size(); i++){
			auto vec = _animateLineButton.at(i);
			if (str == vec->_anima_Name.c_str()){
				vec->transPos = Point(x, y);
				_DrawLayer->setTransitionPos(Point(x, y));
			}
		}
	}
}

void QtEdit::resetBgColor()
{
	int r = ui.RLineEdit->text().toInt();
	int g = ui.GLineEdit->text().toInt();
	int b = ui.BLineEdit->text().toInt();
	HelloWorld* scene = HelloWorld::getInstance();
	scene->setLayerColor(Color3B(r, g, b));
}

void QtEdit::pausebuttonclick()
{
	
	if (_allClickButton.size() > 0 )
	{
		pu *= -1;
		if (-1 == pu)
		{
			ui.PauseButton->setText(_Pausetext);
			_DrawLayer->StartUpdate();
		}
		else
		{
			ui.PauseButton->setText(_Starttext);
			_DrawLayer->EndUpdate();
		}
	}
}


//进度条有点击
void QtEdit::AnimationSlderClick(int per)
{
	if (ui.PauseButton->text() == _Pausetext)
	{
		pausebuttonclick();
	}
}
//进度条值变换了
void QtEdit::AnimationSlderChange()
{
	//isClickToChange = false;
	int a = PencentageSlider->value();
	a -- ;
	if (SeleteLineRow != -1 && SeleteLineRow < _allClickButton.size())
	{
		if (selectRow != -1)
		{
			_allClickButton.at(selectRow).at(selectCol)->Click_ED();
		}
		selectCol = a;
		if (!isClickToChange)
		{
			_allClickButton.at(SeleteLineRow).at(selectCol)->Click_ED(true);
		}
		isClickToChange = false;
		if (isUpdateAnimation){
			SpriteChange();
		}
	}




}
void QtEdit::yestButtonClick()
{
	
}
//键盘操作
//Ctrl是否有按下
void QtEdit::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Control)
	{
		Ctrl_Is_On = true;
	}
	if (e->key() == Qt::Key_Shift)
	{
		Shift_is_ON = true;
	}
	if (e->key() == Qt::Key_Space)
	{
		Space_is_ON = true;
	}
	if (e->key() == Qt::Key_S)
	{
		KeyS_is_ON = true;
	}
	if (e->key() == Qt::Key_F5)
	{
		pausebuttonclick();
	}
	if (Ctrl_Is_On && KeyS_is_ON && _allClickButton.size() > 0)
	{
		QString str = windowTitle();
		str = str.split("*").at(0);
		setWindowTitle(str);
		Export_Data * _Export_Data = Export_Data::getinstance();
		_Export_Data->Data_TO_Relatite(_allClickButton, _animateLineButton);
		_Export_Data->Export_SaveData(_animateLineButton, saveDataName.toLocal8Bit().data());
	}
}


void QtEdit::keyReleaseEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Control)
	{
		Ctrl_Is_On = false;
	}
	if (e->key() == Qt::Key_Shift)
	{
		Shift_is_ON = false;
	}
	if (e->key() == Qt::Key_Space)
	{
		Space_is_ON = false;
	}
	if (e->key() == Qt::Key_S)
	{
		KeyS_is_ON = false;
	}
}

void QtEdit::AddAnimationList(QString full_path_name)
{
	
	QFileInfo fi;
	QString file_name, file_path;
	fi = QFileInfo(full_path_name);
	file_name = fi.fileName();
	file_path = fi.absolutePath(); 
	file_path = file_path + "/animations/";
	re_file_path = file_path;
	int dir_count;
	QDir dir(file_path);
	if (1 == SpiteS_Model)
	{
		//SpiteS_Model = 1;
		//判断路径是否存在
		if (!dir.exists(file_path))
		{
			QMessageBox::about(this, tr("information"), tr("No animations Fold"));
			return;
		}
		//获取所选文件类型过滤器
		QStringList filters;
		filters << QString("*.c3t") << QString("*.c3b");
		//定义迭代器并设置过滤器
		dir.setNameFilters(filters);//设置文件名称过滤器，只为filters格式（后缀为.c3B，c3t等格式）
		dir_count = dir.count();
		if (dir_count <= 0)
		{
			return;
		}
	}
	else if (full_path_name.indexOf("atlas"))
	{
		//SpiteS_Model = 2;
	}
	animation_list.clear();
	//获取分隔符
	//只写结点的实现
	QList<QTreeWidgetItem *> rootList;
	//先把之前的清除了
	ui.AnimationtreeWidget->clear();
	QTreeWidgetItem *imageItem1 = new QTreeWidgetItem;   //添加第一个父节点
	imageItem1->setText(0, file_name.split(".").at(0));
	rootList.append(imageItem1);

	QTreeWidgetItem *imageItem1_1;
	int i, j;
	QString name, path;
	QString temp;
	int list_size = 0;
	bool is_in_list;
	for (i = 0; i < _animateLineButton.size(); i ++)
	{
		DEL_FREE_OBJ(_animateLineButton.at(i));
	}
	_LinesTableWidget->setRowCount(0);
	_LinesTableWidget->setColumnCount(0);
	_LinesTableWidget->currentRow();
	_LinesTableWidget->clear();
	_animateLineButton.clear();
	_allClickButton.clear();
	_retaliteAllClickButton.clear();
	if (1 == SpiteS_Model)
	{
		for (i = 0; i < dir_count; i++)
		{
			name = dir[i];  //文件名称
			path = re_file_path + name;   //文件路径

			list_size = animation_list.size();
			//查找是否有同名文件
			is_in_list = false;
			for (j = 0; j < list_size; j++)
			{
				temp = animation_list.at(j).split(".").at(0);//获取到文件名称，无后缀
				//存在同名
				if (path.split(".").at(0) == temp)
				{
					is_in_list = true;
				}
			}
			if (!is_in_list)
			{
				//_MyLineVector = new MyLineVector();
				//_MyLineVector->_anima_ID = i;
				//std::string str = path.toLocal8Bit().data();
				//str = str.substr(str.find_last_of("/"));
				//int _len = str.find_last_of(".");

				//str = str.substr(1, _len - 1);
				//_MyLineVector->_anima_Name = str;
				//_animateLineButton.push_back(_MyLineVector);
				animation_list.append(path);
				ShowMsg(QString("Import animations/" + name).toLocal8Bit().data());
				auto name = path.section("/", -1);
				imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QString(name))); //添加子节点
				imageItem1->addChild(imageItem1_1);
			}
		}
	}
	else
	{

		vector<string> ani;
		ani = _DrawLayer->getSpineAnimation();
		for (i = 0; i < ani.size(); i ++)
		{
			//_MyLineVector = new MyLineVector();
			//_MyLineVector->_anima_ID = i;
			//_MyLineVector->_anima_Name = ani.at(i);
			//_animateLineButton.push_back(_MyLineVector);
			animation_list.push_back(ani.at(i).c_str());
			imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QString(ani.at(i).c_str()))); //添加子节点
			imageItem1->addChild(imageItem1_1);
		}
			
	}
	_mycol = 0;
	ui.AnimationtreeWidget->insertTopLevelItems(0, rootList);  //将结点插入部件中

	ui.AnimationtreeWidget->expandAll(); //全部展开
}

//在左边的model树中点击了一个动画
void QtEdit::AnimationTreeWidgetClick(QTreeWidgetItem * item, int column)
{
	int last_rol = -1;
	if (1 == SpiteS_Model)
	{
		last_rol = _DrawLayer->animation->getDuration() * oneFPX;
	}
	else
	{
		last_rol = _DrawLayer->getMySpineDuration() * oneFPX;
	}
	last_rol++;
	QTreeWidgetItem *parent = item->parent();
	if (NULL == parent) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
		return;
	if (ui.PauseButton->text() == _Pausetext)
	{
		pausebuttonclick();
	}
	int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)
	_mycol = col;
	char s[100];
	int i;
	int j = 0;
	QVector<ClickButton*>_templine;
	ClickButton *_temp;
	_retaliteAllClickButton.clear();
	for (i = 0; i < _allClickButton.size(); i ++)
	{
		_templine.clear();
		for (j = 0; j < _allClickButton.at(i).size(); j ++)
		{
			_temp = _allClickButton.at(i).at(j)->copy();
			_templine.push_back(_temp);
		}
		_retaliteAllClickButton.push_back(_templine);
	}
	for (i = 0; i < _animateLineButton.size(); i ++)
	{
		//if (_animateLineButton.at(i)->_anima_ID == _last_animaID)
		if ( _animateLineButton.at(i)->_anima_Name == _last_animaname)
		{
			_animateLineButton.at(i)->_lineButton = _retaliteAllClickButton;
			break;
		}
	}
	if (_animateLineButton.size() == 0)
	{
		for (i = 0; i < animation_list.size(); i ++)
		{
			_MyLineVector = new MyLineVector();
			//_MyLineVector->_anima_ID = i;
			std::string str = animation_list[i].toLocal8Bit().data();
			int  _leng;
			if (str.find_last_of("/") == -1)
			{
				_leng = 0;
			}
			else
			{
				_leng = str.find_last_of("/");
			}
			str = str.substr(_leng);
			int _len = str.find_last_of(".");

			if (_len != -1)
			{
				str = str.substr(1, _len - 1);
			}
			_MyLineVector->_anima_Name = str;
			_animateLineButton.push_back(_MyLineVector);
		}
	}
	_last_animaname = animation_list.at(col).split(".").at(0).toLocal8Bit().data();
	int _len = _last_animaname.find_last_of("/");
	_last_animaname = _last_animaname.substr(_len + 1);
	bool Is_Has = false;
	//log("%d", column);
	std::sprintf(s, "%s %d", "CL_", col);
	//
	if (1 == SpiteS_Model)
	{
		ShowMsg(QString("animations/" + animation_list.at(col).split("animations/").at(1)).toLocal8Bit().data());
		_DrawLayer->_sprite->stopAllActions();
		_DrawLayer->animation = Animation3D::getOrCreate(animation_list.at(col).toLocal8Bit().data());
		if (_DrawLayer->animation != NULL)
		{
			_DrawLayer->animate = Animate3D::create(_DrawLayer->animation);
			_DrawLayer->animate->is_auto_update = false;
			_DrawLayer->_RepeatForever = RepeatForever::create(_DrawLayer->animate);
			_DrawLayer->_sprite->runAction(_DrawLayer->_RepeatForever);
		}
		ui.ListWidget->setWindowTitle(animation_list.at(col));
		FPX = _DrawLayer->animation->getDuration() * oneFPX;
		setPerWiget(FPX);
		Init_ClickButton(col);
	}
	else
	{
		ShowMsg(animation_list.at(col).toLocal8Bit().data());
		//_DrawRectLayer->MySpineUnUpdate();
		_DrawLayer->setMySpineAnimation(animation_list.at(col).toLocal8Bit().data());
		ui.ListWidget->setWindowTitle(animation_list.at(col));
		FPX = _DrawLayer->getMySpineDuration() * oneFPX;
		setPerWiget(FPX);
		Init_ClickButton(col);
	}
	QString str;
	if (1 == SpiteS_Model){
		str = animation_list.at(col).section("/", -1).section(".", 0, -2);
	}
	else{
		str = animation_list.at(col);
	}
	for (int bb = 0; bb < _animateLineButton.size(); bb++){
		auto vec = _animateLineButton.at(bb);
		if (str == vec->_anima_Name.c_str()){
			Point p = Point(vec->transPos.x, vec->transPos.y);
			_DrawLayer->setTransitionPos(Point(vec->transPos.x, vec->transPos.y));
			ui.modelTransPosX->setText(QString::number((int)vec->transPos.x));
			ui.modelTransPosY->setText(QString::number((int)vec->transPos.y));
		}
	}
	SeleteLineRow = 0;
	selectRow = 0;
	selectCol = 1;
	if (_QtEdit->_allClickButton.at(0).size() > 0)
	{
		_QtEdit->_allClickButton.at(selectRow).at(selectCol - 1)->Click_ED(true);
	}
	else
	{
		selectRow = -1;
		selectCol = 0;
		QMessageBox::warning(this, codec->toUnicode("警告"), codec->toUnicode("当前帧数为0"));
	}
	//_QtEdit->_allClickButton.at(selectRow).at(0)->Click_ED(true);
	SpriteChange();

	//PencentageSlider->setValue(1);
	
}

void QtEdit::mousePressEvent(QMouseEvent *e)
{
	//stPoint = e->pos();
	if (selectRow != -1 && selectCol != -1 && selectRow < _allClickButton.size() && _allClickButton.size() > 0)
	{
		if (e->button() == Qt::RightButton)
		{
			stPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			stPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			QPoint str(_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].x, _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].y);
			QPoint end(_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].x, _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].y);
			_mouse_is_in = Is_Point_Into(stPoint, str, end);
		}
	}
}
bool  QtEdit::Is_Point_Into(QPoint po, QPoint st, QPoint en)
{
	if (po.x() < st.x() && po.x() < en.x())
	{
		return false;
	}
	if (po.x() > st.x() && po.x() > en.x())
	{
		return false;
	}
	if (po.y() < st.y() && po.y() < en.y())
	{
		return false;
	}
	if (po.y() > st.y() && po.y() > en.y())
	{
		return false;
	}
	return true;
}
void QtEdit::deleteDrawnode()
{
	_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
	int i;
}

void QtEdit::mouseReleaseEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::RightButton))
	{
		if (selectRow != -1 && selectCol != -1 && selectRow < _allClickButton.size() && selectRow < _allClickButton.size() && _allClickButton.size() > 0 && _allClickButton.at(selectRow).at(selectCol)->isFrame() && _mouse_is_in)
		{
			enPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			enPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			QPoint str(_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].x, _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].y);
			QPoint end(_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].x, _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].y);
			bool is_in = Is_Point_Into(enPoint, str, end);
			double rotate;
			if (is_in)
			{
				Vec2 str(stPoint.x(), stPoint.y());
				Vec2 end(enPoint.x(), enPoint.y());
				Vec2 midpoint((_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].x + _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].x) / 2, (_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].y + _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].y) / 2);
				rotate = _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->getRotate(str, end, midpoint);
				rotate = rotate * (180 / PI);
				ui.Rotate->setText(QString("%2").arg((int)rotate));
				BoxChangeInput("");
				//log("%f" , rotate);
			}
		}

	}
}


void QtEdit::mouseMoveEvent(QMouseEvent *e)
{
	
	if ((e->buttons() & Qt::RightButton))
	{
		if (selectRow != -1 && selectCol != -1 && selectRow < _allClickButton.size() && _allClickButton.size() > 0 && _allClickButton.at(selectRow).at(selectCol)->isFrame() && _mouse_is_in)
		{
			enPoint.setX(e->pos().x() - ui.SceneWidget->pos().x());
			enPoint.setY(ui.SceneWidget->height() - (e->pos().y() - ui.SceneWidget->pos().y()) - (ui.SceneWidget->height() - 640) / 4);
			QPoint str(_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].x, _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].y);
			QPoint end(_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].x, _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].y);
			bool is_in = Is_Point_Into(enPoint, str, end);
			double rotate;
			if (is_in)
			{
				Vec2 str(stPoint.x(), stPoint.y());
				Vec2 end(enPoint.x(), enPoint.y());
				Vec2 midpoint((_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].x + _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].x) / 2, (_allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[0].y + _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->Relativevertices[2].y) / 2);
				rotate = _allClickButton.at(selectRow).at(selectCol)->_DrawNodeVertices->getRotate(str, end, midpoint);
				rotate = rotate * (180 / PI);
				ui.Rotate->setText(QString("%2").arg((int)rotate));
				BoxChangeInput("");
				//log("%f" , rotate);
			}
		}

	}
}



void QtEdit::setParent(HWND parent)
{
	m_Parent = parent;
}

void QtEdit::AddTimeLine(int _linemodel)
{
	_lineVerHeader << getHeadName(_linemodel);
	int i = 0;
	int _row = _LinesTableWidget->rowCount();
	_row++;
	_LinesTableWidget->setColumnCount(FPX);
	_LinesTableWidget->setRowCount(_row);
	ClickButton * _Temp;
	QVector<ClickButton*> _temp_line;
	for (i = 0; i < FPX; i++)
	{
		_Temp = new ClickButton(_row - 1, i + 1, _linemodel);
		_LinesTableWidget->setCellWidget(_row - 1, i, _Temp);
		_LinesTableWidget->setRowHeight(_row - 1, _Line_Btn_Height);
		_LinesTableWidget->setColumnWidth(i, _Line_Btn_Width);
		_temp_line.push_back(_Temp);
	}
	_allClickButton.push_back(_temp_line);
	_LinesTableWidget->setVerticalHeaderLabels(_lineVerHeader);
}

void QtEdit::AddLineButton_Click()
{
	if (_allClickButton.size() > 0)
	{
		QMessageBox box(QMessageBox::Warning, "Select", codec->toUnicode("请选择你所需要创建的时间线类型"));
		box.setStandardButtons(QMessageBox::Ok | QMessageBox::Discard | QMessageBox::Save | QMessageBox::Open | QMessageBox::Cancel);
		box.setButtonText(QMessageBox::Ok, QString(codec->toUnicode("碰撞线")));
		box.setButtonText(QMessageBox::Discard, QString(codec->toUnicode("受击线")));
		box.setButtonText(QMessageBox::Save, QString(codec->toUnicode("攻击线")));
		box.setButtonText(QMessageBox::Open, QString(codec->toUnicode("特效线")));
		box.setButtonText(QMessageBox::Cancel, QString(codec->toUnicode("取 消")));
		int _click = box.exec();
		switch (_click)
		{
		case QMessageBox::Ok:
			AddTimeLine(1);
			break;
		case QMessageBox::Discard:
			AddTimeLine(2);
			break;
		case QMessageBox::Save:
			AddTimeLine(3);
			break;
		case QMessageBox::Open:
			AddTimeLine(4);
			break;
		case QMessageBox::Cancel:
			break;
		default:
			break;
		}
	}
	else
	{
		QMessageBox::about(this, tr("information"), codec->toUnicode("当前没有导入资源或未选中一个动作,请确认"));
	}
	
}

void QtEdit::DeleteLine(int _row)
{
	_QtEdit = QtEdit::getInstance();
	QString str = _QtEdit->windowTitle();
	str = str.split("*").at(0);
	str += "*";
	_QtEdit->setWindowTitle(str);
	int i = 0;
	QVector<QVector<ClickButton*>>::iterator it = _allClickButton.begin();
	i = 0;
	for (it; it < _allClickButton.end();i++, it ++)
	{
		if (i == _row)
		{
			_allClickButton.erase(it);
			_LinesTableWidget->removeRow(_row);
			_lineVerHeader.removeAt(i);
			break;
		}
	}
	int j = 0;
	if (_row == SeleteLineRow)
	{
		SeleteLineRow = -1;
	}
	for (;i < _allClickButton.size() ; i ++)
	{
		for (j = 0; j < _allClickButton.at(0).size(); j ++)
		{
			_allClickButton.at(i).at(j)->setRowOpt();
		}
	}
}

void QtEdit::OnTableWidgetSelect()
{
	SeleteLineRow = _LinesTableWidget->currentRow();
	//QList<QTableWidgetSelectionRange>ranges = _LinesTableWidget->selectedRanges();
	//int count = ranges.count();
	//int i, j;
	//int selectcount = 0;
	//int topRow, bottomRow;
	//for (i = 0; i < count; i++)
	//{
	//	topRow = ranges.at(i).topRow();
	//	bottomRow = ranges.at(i).bottomRow();
	//	if (topRow != bottomRow)
	//	{
	//		break;
	//	}
	//	for (j = topRow; j <= bottomRow; j++)
	//	{
	//		//if (selectRow != -1 && selectCol != -1 && selectCol < _allClickButton.at(0).size())
	//		//{
	//		//	_allClickButton.at(selectRow).at(selectCol)->setText(QStringLiteral(""));
	//		//}
	//		if (j != 0)
	//		{
	//			SeleteLineRow = j;
	//		}
	//		
	//	}
	//}
	if (SeleteLineRow < 0)
	{
		SeleteLineRow = 0;
	}
	if (SeleteLineRow < _allClickButton.size())
	{
		ui.Line_ID->setText(QString("%1").arg(_allClickButton.at(SeleteLineRow).at(0)->getLineID()));
	}
	
}

void QtEdit::LineID_ChangeInput()
{
	int _lineId = ui.Line_ID->text().toInt();
	if (SeleteLineRow >= 0)
	{
		_QtEdit->setWindowTitle(_QtEdit->windowTitle().split("*").at(0) + "*");
		_allClickButton.at(SeleteLineRow).at(0)->setLineID(_lineId);
	}
}
//点击事件产生绘图界面显示
void QtEdit::ClickToRepaintBar()
{
	_DrawLayer->ButtonClickToRect();
	//_DrawLayer = DrawLayer::_DrawLayer;
	_tempClickButton = _allClickButton.at(selectRow).at(selectCol);

	ClickButton * _tempClick = _allClickButton.at(0).at(selectCol);

	ui.Is_gravity->setText(_tempClick->getGravity() == true ? "true" : "false");
	ui.Re_Height->setText(QString("%2").arg(_tempClick->_Height - _IN_Height));
	ui.Re_Width->setText(QString("%2").arg(_tempClick->_Width - _IN_Width));
	spritePos.x = floatToInt(ui.Re_Width->text().toDouble() + _IN_Width);
	spritePos.y = floatToInt(ui.Re_Height->text().toDouble() + _IN_Height);
	ui.ScallX->setText(QString("%2").arg(_tempClick->_ScallX));
	ui.ScallY->setText(QString("%2").arg(_tempClick->_ScallY));

	double _x = spritePos.x;
	double _y = spritePos.y;
	_x = doubleToDoubletwo(_x);
	_y = doubleToDoubletwo(_y);

	selectModel = _tempClickButton->getFrameMode();
	double _ScallX = ui.ScallX->text().toDouble();
	double _ScallY = ui.ScallY->text().toDouble();
	double _Height = spritePos.y;
	double _Width = spritePos.x;

	_ScallX = doubleToDoubletwo(_ScallX);
	_ScallY = doubleToDoubletwo(_ScallY);
	_Height = doubleToDoubletwo(_Height);
	_Width = doubleToDoubletwo(_Width);

	ui.St_Height->setText(QString("%2").arg(floatToInt(_tempClickButton->_DrawNodeVertices->Relativevertices[0].y - _y)));
	ui.St_Width->setText(QString("%2").arg(floatToInt(_tempClickButton->_DrawNodeVertices->Relativevertices[0].x - _x)));
	ui.En_Height->setText(QString("%2").arg(floatToInt(_tempClickButton->_DrawNodeVertices->Relativevertices[2].y - _y)));
	ui.En_Width->setText(QString("%2").arg(floatToInt(_tempClickButton->_DrawNodeVertices->Relativevertices[2].x - _x)));
	ui.St_Height_RE->setText(QString("%2").arg((_tempClickButton->_DrawNodeVertices->Relativevertices[0].y - _y) / _ScallY));
	ui.St_Width_RE->setText(QString("%2").arg((_tempClickButton->_DrawNodeVertices->Relativevertices[0].x - _x) / _ScallX));
	ui.En_Height_RE->setText(QString("%2").arg((_tempClickButton->_DrawNodeVertices->Relativevertices[2].y - _y) / _ScallY));
	ui.En_Width_RE->setText(QString("%2").arg((_tempClickButton->_DrawNodeVertices->Relativevertices[2].x - _x) / _ScallX));
	ui.Rotate->setText(QString("%2").arg((int)_tempClickButton->_DrawNodeVertices->Rotate));



	double box_width = abs(ui.St_Width_RE->text().toDouble() - ui.En_Width_RE->text().toDouble());
	double box_height = abs(ui.St_Height_RE->text().toDouble() - ui.En_Height_RE->text().toDouble());
	double box_x_posi = _tempClickButton->_DrawNodeVertices->getRelateMidPoint().x;
	double box_y_posi = _tempClickButton->_DrawNodeVertices->getRelateMidPoint().y;

	box_width = doubleToDoubletwo(box_width);
	box_height = doubleToDoubletwo(box_height);
	box_x_posi = doubleToDoubletwo(box_x_posi);
	box_y_posi = doubleToDoubletwo(box_y_posi);


	ui.Box_X_Posi->setText(QString("%2").arg(box_x_posi - _Width));
	ui.Box_Y_Posi->setText(QString("%2").arg(box_y_posi - _Height));
	ui.Box_X_Posi_RE->setText(QString("%2").arg((box_x_posi - _Width) / _ScallX));
	ui.Box_Y_Posi_RE->setText(QString("%2").arg((box_y_posi - _Height) / _ScallY));

	ui.Box_Width->setText(QString("%2").arg(box_width * _ScallX));
	ui.Box_Height->setText(QString("%2").arg(box_height * _ScallY));
	ui.Box_Width_RE->setText(QString("%2").arg(box_width));
	ui.Box_Height_RE->setText(QString("%2").arg(box_height));
	_DrawLayer->setSpritePosition(_Width, _Height, _ScallX, _ScallY);

	ui.Is_show->setText(_allClickButton.at(selectRow).at(selectCol)->isNULL() == true ? "false" : "true");


}

void QtEdit::ShowMessageInBar(int argc ,...)
{
	// 声明一个指针, 用于持有可变参数
	va_list pArg;
	// 将 pArg 初始化为指向第一个参数
	va_start(pArg, argc);
	// 输出参数
	for (int i = 0; i != argc; ++i){
		// 获取 pArg 所指向的参数并输出
		mymsg += va_arg(pArg, char *);
	}
	mymsg += "\n";
	va_end(pArg);
	ui.showmessage->setPlainText(mymsg.c_str());
}

void QtEdit::SpriteChange(float dt)
{
	double time__ = dt;
	if (1 == SpiteS_Model)
	{
		double t = _DrawLayer->animation->getDuration();
		_DrawLayer->animate->updateOnPercentage(time__ / _DrawLayer->animation->getDuration());
	}
	else{
		double t = _DrawLayer->getMySpineDuration();
		_DrawLayer->updateMySpinePercentage(time__);
	}
	ui.currFrameTime->setText(QString::number(time__));
}

void QtEdit::SpriteChange()
{
	double time__ = 0.0f;
	if (1 == SpiteS_Model)
	{
		time__ = selectCol / oneFPX;
		//c3b是按照百分比来计算的
		_DrawLayer->animate->updateOnPercentage(0.01 * selectCol * 100.0 / (FPX - 1));
	}
	else
	{
		time__ = selectCol / oneFPX;
		//Spine Spine是按照时间来计算的
		_DrawLayer->updateMySpinePercentage(selectCol / oneFPX);
	}
	ui.currFrameTime->setText(QString::number(time__));
	if (selectRow != -1 && selectRow < _allClickButton.size())
	{
		_tempClickButton = _allClickButton.at(selectRow).at(selectCol);
		//空实现
		_DrawLayer->ButtonClick(_tempClickButton);
	}
	
}

void QtEdit::Init_ClickButton(int col)
{
	int _len, i;
	std::string str;
	str = animation_list.at(col).split(".").at(0).toLocal8Bit().data();
	_len = str.find_last_of("/");
	str = str.substr(_len + 1);
	_allClickButton.clear();
	for (i = 0; i < _animateLineButton.size(); i++)
	{
		if (str == _animateLineButton.at(i)->_anima_Name)
		{
			_allClickButton = _animateLineButton.at(i)->_lineButton;
			break;
		}
	}
	//_allClickButton = _animateLineButton.at(col)->_lineButton;
	int j = 0;
	ClickButton * _Temp;
	if (_allClickButton.size() == 0)
	{
		
		QVector<ClickButton*> _temp_line;
		for (i = 0; i < FPX; i++)
		{
			_Temp = new ClickButton(0, i + 1, 0);
			_temp_line.push_back(_Temp);
		}
		_allClickButton.push_back(_temp_line);
	}
	_LinesTableWidget->setRowCount(0);
	_LinesTableWidget->setColumnCount(0);
	_LinesTableWidget->clearContents();
	_LinesTableWidget->setRowCount(_allClickButton.size());
	_LinesTableWidget->setColumnCount(FPX);
	_lineVerHeader.clear();
	int _frame_model;
	//_lineVerHeader << QStringLiteral("peo");
	QVector<ClickButton *> _add_line;
	for (i = 0; i < _allClickButton.size(); i++)
	{
		_add_line.clear();
		for (j = 0; j < FPX; j++)
		{
			if (j < _allClickButton.at(i).size())
			{
				_Temp = _allClickButton.at(i).at(j);
				if (j == 0)
				{
					_lineVerHeader.push_back(getHeadName(_Temp->getFrameMode()));
				}
				_LinesTableWidget->setCellWidget(i, j, _Temp);
				_LinesTableWidget->setRowHeight(i, _Line_Btn_Height);
				_LinesTableWidget->setColumnWidth(j, _Line_Btn_Width);
				if (_Temp->isFrame())
				{
					_Temp->setButtonColor();
				}
				_frame_model = _Temp->getFrameMode();
			}
			else
			{
				ClickButton *_TempClick = new ClickButton(i, j + 1, _frame_model);
				if (j == 0)
				{
					_lineVerHeader.push_back(getHeadName(_TempClick->getFrameMode()));
				}
				_LinesTableWidget->setCellWidget(i, j, _TempClick);
				_LinesTableWidget->setRowHeight(i, _Line_Btn_Height);
				_LinesTableWidget->setColumnWidth(j, _Line_Btn_Width);
				if (_TempClick->isFrame())
				{
					_TempClick->setButtonColor();
				}
				_add_line.push_back(_TempClick);
			}
		}
		if (_add_line.size() > 0)
		{
			int _last = _allClickButton.at(i).size();
			_allClickButton[i].resize(_allClickButton.at(i).size() + _add_line.size());
			for (j = 0; j < _add_line.size(); j++)
			{
				_allClickButton[i][_last + j] = _add_line.at(j);
			}
		}
		else if (FPX < _allClickButton.at(i).size())
		{
			for (j = FPX; j < _allClickButton.at(i).size(); j++)
			{
				delete _allClickButton.at(i).at(j);
			}
			_allClickButton[i].resize(FPX);
		}
	}
	
	_LinesTableWidget->setVerticalHeaderLabels(_lineVerHeader);
}

QString QtEdit::getHeadName(int _model)
{
	QString str;
	if (_model == 0)
	{
		str = _Peotext;
	}
	else if (_model == 1)
	{
		//_name = "body";
		str = _Bodytext;
	}
	else if (_model == 2)
	{
		//_lineVerHeader << "inj  ";
		str = _Injtext;
	}
	else if (_model == 3)
	{
		//_lineVerHeader << "att  ";
		str = _Atttext;
	}
	else if (_model == 4)
	{
		//_lineVerHeader << "eff  ";
		str = _Effecttext;
	}
	return str;
}
int QtEdit::floatToInt(float f){
	int num = 0;
	if (f > 0) //正数
		num = (f * 10 + 5) / 10;
	else if (f < 0) //负数
		num = (f * 10 - 5) / 10;
	else num = 0;

	return num;

}

void QtEdit::Update_DrawLayer()
{
	//_DrawLayer = DrawLayer::getinstance();
}

double QtEdit::doubleToDoubletwo(double &f)
{
	char str[20];
	std::sprintf(str, "%.2f", f);
	return atof(str);
}
