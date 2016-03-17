#ifndef _MYSPINE_CLASS_H_
#define _MYSPINE_CLASS_H_


#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"
class MySpine : public spine::SkeletonAnimation
{
public:
	MySpine();
	MySpine(const std::string& skeletonDataFile, const std::string& atlasFile, float scale);
	~MySpine();
	static MySpine * getinstance();
	void UpdateMySpineOnDetail(MySpine * _temp , float mydt);
	static MySpine* createWithFile(const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
	spAnimationState* self;
private:

};

#endif // !_MYSPINE_CLASS_H_