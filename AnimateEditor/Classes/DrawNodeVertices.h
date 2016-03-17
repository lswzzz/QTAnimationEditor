
#pragma once
#include "cocos2d.h"
#include "MyConfig.h"
USING_NS_CC;
class DrawNodeVertices 
{
public:
	DrawNodeVertices();
	~DrawNodeVertices();
	static DrawNodeVertices * getInstance();
	static DrawNodeVertices * create();
	bool init();
	void setVertices(Vec2, Vec2);
	void setRelativeVertices(Vec2, Vec2);
	void setRotateVertices(Vec2 startPoint, Vec2 EndPoint, double rotate = -720);
	void setRotateRelativeVertices(Vec2 startPoint, Vec2 EndPoint, double rotate = -720);
	void updateVertices();
	void updateRetlativeVertices();
	Vec2 getMidPoint();
	Vec2 getRelateMidPoint();
	double getRotate(Vec2 StartPoint, Vec2 EndPoint, Vec2 minPoint = Vec2( -1000, -1000));
	void setRelativeVertices(Vec2 *points, Vec2 relativeposi);
	void setRelativeRotateVertices(Vec2 *points, Vec2 relativeposi);
	void setVerticeFromRelative(Vec2 * MyRelativeVertices, Vec2 relativeposi);
	void setRotateFromRelativeRotate(Vec2  MyRelativeRotate[5], Vec2 relativeposi);
	void setRelativeScallX(double PosiX , double InitX, double SX);
	void setRelativeScallY(double PosiY , double InitY , double SY);
	void setVerticesScallX(double PosiX, double InitX, double SX);
	void setVerticesScallY(double PosiY, double InitY, double SY);
	void updateRetlativeVertices(double _w, double _h, double _sx, double _sy);
	void reset();
	double myabs(double);
	DrawNodeVertices * copy();
public:
	int Singl_ID;
	bool is_visible;
	Vec2 *Vertices = NULL;
	Vec2 *RotateVertices = NULL;
	double Rotate;
	double SinB;
	double CosB;
	Vec2 * Relativevertices = nullptr;
	Vec2 * RelativeRotateVertices = nullptr;
	Vec2 RelativePosition = Vec2(_IN_Width, _IN_Height);
	Vec2 _temp;
	double RelativeScallX;
	double RelativeScallY;
	static DrawNodeVertices * _DrawNodeVertices;
	double _last_Width = _IN_Width;
	double _last_Height = _IN_Height;
	double _last_ScallX = _IN_ScallX;
	double _last_ScallY = _IN_ScallY;
protected:
	void doubleToDoubletwo();
};

