#include "MySpine.h"
#include "spine/spine-cocos2dx.h"
using namespace spine;
static MySpine * _MySpine = NULL;

MySpine::MySpine()
{
}
MySpine::MySpine(const std::string& skeletonDataFile, const std::string& atlasFile, float scale) :SkeletonAnimation(skeletonDataFile , atlasFile , scale)
{

}

MySpine::~MySpine()
{
}

void MySpine::UpdateMySpineOnDetail(MySpine * _temp, float mydt)
{
	int i;
	self = _temp->getState();
	if (!self)
	{
		return;
	}
	float previousDelta;
	float delta = 0.02;
	delta *= self->timeScale;
	for (i = 0; i < self->tracksCount; ++i) {
		spTrackEntry* current = self->tracks[i];
		if (!current) continue;

		//current->time += delta * current->timeScale;
		current->time = mydt;
		//log("%f", current->time);
		if (current->previous) {
			previousDelta = delta * current->previous->timeScale;
			current->previous->time += previousDelta;
			current->mixTime += previousDelta;
		}

		if (current->next) {
			current->next->time = current->lastTime - current->next->delay;
			//if (current->next->time >= 0) _spAnimationState_setCurrent(self, i, current->next);
		}
		else {
			/* End non-looping animation when it reaches its end time and there is no next entry. */
			if (!current->loop && current->lastTime >= current->endTime)
				spAnimationState_clearTrack(self, i);
		}
	}
}
MySpine* MySpine::createWithFile(const std::string& skeletonDataFile, const std::string& atlasFile, float scale) {
	_MySpine = new MySpine(skeletonDataFile, atlasFile, scale);
	_MySpine->autorelease();
	return _MySpine;
}

MySpine * MySpine::getinstance()
{
	return _MySpine;
}
