#ifndef _DRAWLAYER_CLASS_H
#define _DRAWLAYER_CLASS_H
#include "cocos2d.h"
#include "ClickButton.h"
using namespace std;

USING_NS_CC;

class DrawLayer : public Layer
{
public:
	DrawLayer();
	static DrawLayer * createLayer();
	static DrawLayer * getinstance();
	void ButtonClickToRect();

	void setSpritePosition(float with, float height, float sacllx, float scally);

	void setSpriteRotate3D(float _x , float _y , float _z);
	void updateMySprite3D(std::string filename, std::string texture, std::string file_animation);
	void updateMySpine(std::string filename, std::string json_name);
	virtual void update(float dt);
	void initShowPosLabel();

	//Spine²Ù×÷
	float getMySpineDuration();
	void setMySpineAnimation(const char * _name, bool is_re = true);
	void MySpineUnUpdate();
	void updateMySpinePercentage(float dt);
	vector<string> getSpineAnimation();

	void DrawInitPosi();
	void ButtonClick(ClickButton * &_ClickButton);
	void StartUpdate();
	void EndUpdate();
	void UpdateToButton();

	void setTransitionPos(Point pos);
	Point getTransitionPos(){ return transPos; };
protected:
	virtual bool init();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch* touch, Event  *event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	void ScheduMyUpdate(float dt);
	CREATE_FUNC(DrawLayer);
	

	
	void DoDrawRectInit();
	void DoDrawRectNow(DrawNode * & _DNode , Vec2  *&pos ,float apath = 1.0, int drawmode = -1);
	void DrawTempRect();
	void InitPosiupdate(float dt);
	

public:
	int selectModel = 0;
	int _select_col = -1;
	int _select_row = -1;
	std::vector<DrawNode *> _DrawVectors = std::vector<DrawNode*>();;
	Animation3D  *animation;
	Animate3D * animate;
	RepeatForever * _RepeatForever;

	float _MySpineDuration = 1;
	bool Is_MoveTORect = false;


	vector<std::string> SpineAnimationList;
	Sprite3D *_sprite;
private:
	DrawNode * PosiDraw = NULL;
	DrawNode * TempNode = NULL;
	Vec2			Startpoint;
	Vec2			Endpoint;
	Node			*VisiNode;
	Vec2			transPos;
	Vec2 _tempPoints[5];
	float mydt = 0.0;
	bool			isPlayAnimation;
	double			currTime;
	Label			*showPosLabel;
};

#endif // !_DRAWLAYER_CLASS_H