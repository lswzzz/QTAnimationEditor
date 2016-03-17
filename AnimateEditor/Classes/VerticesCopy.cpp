#include "VerticesCopy.h"
USING_NS_CC;
VerticesCopy * VerticesCopy::_VerticesCopy = NULL;
VerticesCopy::VerticesCopy()
{
	RelativeRotateVertices = new Vec2[5];
	Relativevertices = new Vec2[5];
}


VerticesCopy::~VerticesCopy()
{
	FREE_DEL_VEC(Relativevertices);
	FREE_DEL_VEC(RelativeRotateVertices);
}

VerticesCopy * VerticesCopy::getinstance()
{
	if (!_VerticesCopy)
	{
		_VerticesCopy = new VerticesCopy();
	}
	return _VerticesCopy;
}

void VerticesCopy::destory()
{
	delete _VerticesCopy;
	_VerticesCopy = NULL;
}

void VerticesCopy::setRelativevertices(Vec2 * &_temp)
{
	for (int i = 0; i < 5; i ++)
	{
		Relativevertices[i].set(_temp[i]);
	}
}

void VerticesCopy::setRelativeRotateVertices(Vec2 * &_temp)
{
	for (int i = 0; i < 5; i++)
	{
		RelativeRotateVertices[i].set(_temp[i]);
	}
}
