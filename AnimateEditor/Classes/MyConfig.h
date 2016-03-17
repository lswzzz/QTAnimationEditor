#ifndef  _MYCONFIG_H_
#define  _MYCONFIG_H_


#define  _IN_Rotate3D_Y			90.0f
#define  _IN_Width				500.0
#define  _IN_Height				100.0
#define  _IN_ScallX				1.0
#define  _ShowTransPosX			0.0
#define  _showTransPosY			0.0
#define  _IN_ScallY				1.0
#define  _TEN_ScallX			10.0
#define  _TEN_ScallY			10.0
#define  oneFPX					30.0
#define	 PI						3.1415926535898
#define  _Line_Btn_Width		40.0
#define	 _Line_Btn_Height		20.0
#define  _Effecttext			"Eff  "
#define  _Bodytext				"body"
#define  _Atttext				"Att  "
#define  _Injtext				"Inj  "
#define  _Peotext				"peo  "
#define  _Starttext				"Start"
#define  _Pausetext				"Pause"
#define  _InComboxtext			"-\350\257\267\351\200\211\346\213\251-"
#define  _Input_EXP				"^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,6})?$|(^\\t?$)"
#define  QStringToDouble(str)	str.toDouble();
#define  QStringToFloat(str)	str.toFloat()
#define  QStringToVec2(w,h)		Vec2(w.toFloat(),h.toFloat())
#define  FREE_DEL_VEC(f) do{if(f != NULL) {delete[] f;}}while (0);
#define  FREE_DEL_OBJ(f) do{if(f != NULL) {delete (f) ; f = NULL;}}while (0);
#define  DEL_FREE_OBJ(f) do {if(f) delete f;} while (0);
#define  MYDELETE(f) do{if(f != NULL) delete (f);}while(0);



#endif