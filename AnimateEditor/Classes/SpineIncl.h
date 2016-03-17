#pragma once
//Spine和Qt有冲突，大家都有solts这个鬼东西，所以本类是为了让QT和Spine隔绝的
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

