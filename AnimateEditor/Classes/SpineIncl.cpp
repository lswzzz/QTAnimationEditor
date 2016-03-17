#include "SpineIncl.h"
#include "MySpine.h"
static SpineIncl * _SpineIncl = NULL;
static spTrackEntry* _entry;
static MySpine *_MySpine = NULL;
SpineIncl::SpineIncl()
{
}


SpineIncl::~SpineIncl()
{
}

SpineIncl * SpineIncl::getinstance()
{
	if (_SpineIncl == NULL)
	{
		_SpineIncl = new SpineIncl();
		//_SpineIncl->autorelease();
	}
	return _SpineIncl;
}

void SpineIncl::updateSpine(std::string filename, std::string json_name, Node * _parent)
{
	parent = _parent;
	_MySpine = _MySpine->createWithFile(json_name, filename);
	spineVec = Node::create();
	parent->addChild(spineVec);
	spineVec->addChild(_MySpine);
	spSkeletonData * self = _MySpine->getSkeleton()->data;
	int i;
	SpineAnimationList.clear();
	for (i = 0; i < self->animationsCount; i++)
	{
		//log("%s", self->animations[i]->name);
		SpineAnimationList.push_back(self->animations[i]->name);
	}
	_MySpine->setToSetupPose();
	_MySpine->unscheduleUpdate();
}

float SpineIncl::getMySpineDuration()
{
	return _Duration;
}

void SpineIncl::setMySpineAnimation(const char * _name, bool is_te /* = true */)
{
	_MySpine->setToSetupPose();
	_entry = _MySpine->setAnimation(0, _name, is_te);
	_Duration = _entry->animation->duration;
}

void SpineIncl::updateMySpinePercentage(float dt)
{
	//log("all = %f  now = %f", _MySpineDuration , dt);
	_MySpine->UpdateMySpineOnDetail(_MySpine, dt);
	spAnimationState_apply(_MySpine->getState(), _MySpine->getSkeleton());
	spSkeleton_updateWorldTransform(_MySpine->getSkeleton());
}

void SpineIncl::setModelPosition(Vec2 pos)
{
	_MySpine->setPosition(pos);
}

void SpineIncl::MySpineUnUpdate()
{
	if (_MySpine != NULL)
	{
		_MySpine->unscheduleUpdate();
	}
}

void SpineIncl::setSpritePosition(float with, float height, float sacllx, float scally)
{
	Vec2 posi(with, height);
	spineVec->setPosition(posi);
	spineVec->setScaleX(sacllx);
	spineVec->setScaleY(scally);
}
