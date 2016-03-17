#pragma once
//Spine��Qt�г�ͻ����Ҷ���solts������������Ա�����Ϊ����QT��Spine������
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class SpineIncl
{
public:
	SpineIncl();
	~SpineIncl();
	static SpineIncl * getinstance();
	void updateSpine(std::string filename, std::string json_name , Node * parent);
	float getMySpineDuration();
	void setMySpineAnimation(const char * _name, bool is_re = true);
	void MySpineUnUpdate();
	void setSpritePosition(float with, float height, float sacllx, float scally);
	void updateMySpinePercentage(float dt);
	void setModelPosition(Vec2 pos);
	Node* spineVec;
	Node * parent;
	float _Duration = -1;
	vector<std::string> SpineAnimationList;
};

