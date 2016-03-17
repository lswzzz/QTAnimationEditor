#include "DrawNodeVertices.h"
#include "MyConfig.h"
DrawNodeVertices * DrawNodeVertices::_DrawNodeVertices = NULL;
DrawNodeVertices::DrawNodeVertices()
{
	_DrawNodeVertices = this;
	_DrawNodeVertices->init();
}
DrawNodeVertices * DrawNodeVertices::create()
{
	_DrawNodeVertices = new (std::nothrow) DrawNodeVertices();
	return _DrawNodeVertices;
}

DrawNodeVertices * DrawNodeVertices::getInstance()
{
	if (!_DrawNodeVertices)
	{
		_DrawNodeVertices = new DrawNodeVertices();
	}
	return _DrawNodeVertices;
}

DrawNodeVertices::~DrawNodeVertices()
{
	//drawnode->autorelease();
	FREE_DEL_VEC(Vertices);
	FREE_DEL_VEC(Relativevertices);
	FREE_DEL_VEC(RelativeRotateVertices);

	FREE_DEL_VEC(RotateVertices);

}

bool DrawNodeVertices::init()
{
	is_visible = true;
	Rotate = 0.0;
	Vertices = new Vec2[5];
	RotateVertices = new Vec2[5];
	Relativevertices = new Vec2[5];
	RelativeRotateVertices = new Vec2[5];
	for (int i = 0; i < 5; i++)
	{
		Vertices[i].set(0, 0);
		RotateVertices[i].set(0, 0);
		Relativevertices[i].set(0, 0);
		RelativeRotateVertices[i].set(0, 0);
	}
	return true;
}

void DrawNodeVertices::setRotateFromRelativeRotate(Vec2 * MyRelativeRotate, Vec2 relativeposi)
{
	
	double x = relativeposi.x - RelativePosition.x;
	double y = relativeposi.y - RelativePosition.y;
	_temp = Vec2(x, y);
	RotateVertices[0].set(MyRelativeRotate[0] - _temp);
	RotateVertices[1].set(MyRelativeRotate[1] - _temp);
	RotateVertices[2].set(MyRelativeRotate[2] - _temp);
	RotateVertices[3].set(MyRelativeRotate[3] - _temp);
	RotateVertices[4].set(MyRelativeRotate[4] - _temp);
	doubleToDoubletwo();
	//RelativeRotateVertices = MyRelativeRotate;
}
void DrawNodeVertices::setVerticeFromRelative(Vec2 * MyRelativeVertices, Vec2 relativeposi)
{
	
	double x = relativeposi.x - RelativePosition.x;
	double y = relativeposi.y - RelativePosition.y;
	_temp = Vec2(x, y);
	Relativevertices[0];
	Vertices[0].set(MyRelativeVertices[0] - _temp);
	Vertices[1].set(MyRelativeVertices[1] - _temp);
	Vertices[2].set(MyRelativeVertices[2] - _temp);
	Vertices[3].set(MyRelativeVertices[3] - _temp);
	Vertices[4].set(MyRelativeVertices[4] - _temp);
	//Relativevertices = MyRelativeVertices;
	doubleToDoubletwo();
}

void DrawNodeVertices::setRelativeRotateVertices(Vec2 *points, Vec2 relativeposi)
{
	double x = relativeposi.x - RelativePosition.x;
	double y = relativeposi.y - RelativePosition.y;
	_temp = Vec2(x, y);
	RelativeRotateVertices[0].set(points[0] + _temp);
	RelativeRotateVertices[1].set(points[1] + _temp);
	RelativeRotateVertices[2].set(points[2] + _temp);
	RelativeRotateVertices[3].set(points[3] + _temp);
	RelativeRotateVertices[4].set(points[4] + _temp);
	doubleToDoubletwo();
}
void DrawNodeVertices::setRelativeVertices(Vec2 *points, Vec2 relativeposi)
{

	double x = relativeposi.x - RelativePosition.x;
	double y = relativeposi.y - RelativePosition.y;
	_temp = Vec2(x, y);
	Relativevertices[0].set(points[0] + _temp);
	Relativevertices[1].set(points[1] + _temp);
	Relativevertices[2].set(points[2] + _temp);
	Relativevertices[3].set(points[3] + _temp);
	Relativevertices[4].set(points[4] + _temp);
	//Vertices = Relativevertices;
	doubleToDoubletwo();
}

void DrawNodeVertices::setRelativeVertices(Vec2 Startpoint, Vec2 Endpoint)
{
	Relativevertices[0].set(Startpoint);
	Relativevertices[1].set(Endpoint.x, Startpoint.y);
	Relativevertices[2].set(Endpoint);
	Relativevertices[3].set(Startpoint.x, Endpoint.y);
	Relativevertices[4].set(Startpoint);
	doubleToDoubletwo();
}

void DrawNodeVertices::setVertices(Vec2 Startpoint, Vec2 Endpoint)
{
	Vertices[0].set(Startpoint);
	Vertices[1].set(Endpoint.x, Startpoint.y);
	Vertices[2].set(Endpoint);
	Vertices[3].set(Startpoint.x, Endpoint.y);
	Vertices[4].set(Startpoint);
	setRotateVertices(Startpoint, Endpoint,Rotate);
	doubleToDoubletwo();

}
void DrawNodeVertices::setVerticesScallX(double PosiX, double InitX, double SX)
{
	RelativeScallX = SX / InitX;
	double _allX = PosiX - Vertices[0].x;
	Vec2 ve(PosiX - (_allX * SX / InitX), Vertices[0].y);
	Vertices[0].set(ve);

	_allX = PosiX - Vertices[1].x;
	ve.set(PosiX - (_allX * SX / InitX), Vertices[1].y);
	Vertices[1].set(ve);

	_allX = PosiX - Vertices[2].x;
	ve.set(PosiX - (_allX * SX / InitX), Vertices[2].y);
	Vertices[2].set(ve);

	_allX = PosiX - Vertices[3].x;
	ve.set(PosiX - (_allX * SX / InitX), Vertices[3].y);
	Vertices[3].set(ve);

	_allX = PosiX - Vertices[4].x;
	ve.set(PosiX - (_allX * SX / InitX), Vertices[4].y);
	Vertices[4].set(ve);


	_allX = PosiX - RotateVertices[0].x;
	ve.set(PosiX - (_allX * SX / InitX), RotateVertices[0].y);
	RotateVertices[0].set(ve);

	_allX = PosiX - RotateVertices[1].x;
	ve.set(PosiX - (_allX * SX / InitX), RotateVertices[1].y);
	RotateVertices[1].set(ve);

	_allX = PosiX - RotateVertices[2].x;
	ve.set(PosiX - (_allX * SX / InitX), RotateVertices[2].y);
	RotateVertices[2].set(ve);

	_allX = PosiX - RotateVertices[3].x;
	ve.set(PosiX - (_allX * SX / InitX), RotateVertices[3].y);
	RotateVertices[3].set(ve);

	_allX = PosiX - RotateVertices[4].x;
	ve.set(PosiX - (_allX * SX / InitX), RotateVertices[4].y);
	RotateVertices[4].set(ve);
	doubleToDoubletwo();
}
void DrawNodeVertices::setVerticesScallY(double PosiY, double InitY, double SY)
{
	RelativeScallY = SY / InitY;
	//Relativevertices[0].y = Relativevertices[0].y * SY / InitY;
	//Relativevertices[1].y = Relativevertices[1].y * SY / InitY;
	//Relativevertices[2].y = Relativevertices[2].y * SY / InitY;
	//Relativevertices[3].y = Relativevertices[3].y * SY / InitY;
	//Relativevertices[4].y = Relativevertices[4].y * SY / InitY;

	double _allY = PosiY - Vertices[0].y;
	Vec2 posi(Vertices[0].x , PosiY - (_allY * SY / InitY));
	Vertices[0].set(posi);

	_allY = PosiY - Vertices[1].y;
	posi.set(Vertices[1].x, PosiY - (_allY * SY / InitY));
	Vertices[1].set(posi);

	_allY = PosiY - Vertices[2].y;
	posi.set(Vertices[2].x, PosiY - (_allY * SY / InitY));
	Vertices[2].set(posi);

	_allY = PosiY - Vertices[3].y;
	posi.set(Vertices[3].x, PosiY - (_allY * SY / InitY));
	Vertices[3].set(posi);

	_allY = PosiY - Vertices[4].y;
	posi.set(Vertices[4].x, PosiY - (_allY * SY / InitY));
	Vertices[4].set(posi);




	_allY = PosiY - RotateVertices[0].y;
	posi.set(RotateVertices[0].x, PosiY - (_allY * SY / InitY));
	RotateVertices[0].set(posi);

	_allY = PosiY - RotateVertices[1].y;
	posi.set(RotateVertices[1].x, PosiY - (_allY * SY / InitY));
	RotateVertices[1].set(posi);

	_allY = PosiY - RotateVertices[2].y;
	posi.set(RotateVertices[2].x, PosiY - (_allY * SY / InitY));
	RotateVertices[2].set(posi);

	_allY = PosiY - RotateVertices[3].y;
	posi.set(RotateVertices[3].x, PosiY - (_allY * SY / InitY));
	RotateVertices[3].set(posi);

	_allY = PosiY - RotateVertices[4].y;
	posi.set(RotateVertices[4].x, PosiY - (_allY * SY / InitY));
	RotateVertices[4].set(posi);
	doubleToDoubletwo();
}
void DrawNodeVertices::setRelativeScallX(double PosiX, double InitX, double SX)
{
	RelativeScallX = SX / InitX;
	double _allX = PosiX - Relativevertices[0].x;
	Vec2 posi(PosiX - (_allX * SX / InitX), Relativevertices[0].y);
	Relativevertices[0].set(posi);

	_allX = PosiX - Relativevertices[1].x;
	posi.set(PosiX - (_allX * SX / InitX), Relativevertices[1].y);
	Relativevertices[1].set(posi);

	_allX = PosiX - Relativevertices[2].x;
	posi.set(PosiX - (_allX * SX / InitX), Relativevertices[2].y);
	Relativevertices[2].set(posi);

	_allX = PosiX - Relativevertices[3].x;
	posi.set(PosiX - (_allX * SX / InitX), Relativevertices[3].y);
	Relativevertices[3].set(posi);

	_allX = PosiX - Relativevertices[4].x;
	posi.set(PosiX - (_allX * SX / InitX), Relativevertices[4].y);
	Relativevertices[4].set(posi);

	//Relativevertices[0].x = Relativevertices[0].x * SX / InitX;
	//Relativevertices[1].x = Relativevertices[1].x * SX / InitX;
	//Relativevertices[2].x = Relativevertices[2].x * SX / InitX;
	//Relativevertices[3].x = Relativevertices[3].x * SX / InitX;
	//Relativevertices[4].x = Relativevertices[4].x * SX / InitX;


	_allX = PosiX - RelativeRotateVertices[0].x;
	posi.set(PosiX - (_allX * SX / InitX), RelativeRotateVertices[0].y);
	RelativeRotateVertices[0].set(posi);

	_allX = PosiX - RelativeRotateVertices[1].x;
	posi.set(PosiX - (_allX * SX / InitX), RelativeRotateVertices[1].y);
	RelativeRotateVertices[1].set(posi);

	_allX = PosiX - RelativeRotateVertices[2].x;
	posi.set(PosiX - (_allX * SX / InitX), RelativeRotateVertices[2].y);
	RelativeRotateVertices[2].set(posi);

	_allX = PosiX - RelativeRotateVertices[3].x;
	posi.set(PosiX - (_allX * SX / InitX), RelativeRotateVertices[3].y);
	RelativeRotateVertices[3].set(posi);

	_allX = PosiX - RelativeRotateVertices[4].x;
	posi.set(PosiX - (_allX * SX / InitX), RelativeRotateVertices[4].y);
	RelativeRotateVertices[4].set(posi);
	doubleToDoubletwo();
}
void DrawNodeVertices::setRelativeScallY(double PosiY , double InitY , double SY)
{
	RelativeScallY = SY / InitY;
	//Relativevertices[0].y = Relativevertices[0].y * SY / InitY;
	//Relativevertices[1].y = Relativevertices[1].y * SY / InitY;
	//Relativevertices[2].y = Relativevertices[2].y * SY / InitY;
	//Relativevertices[3].y = Relativevertices[3].y * SY / InitY;
	//Relativevertices[4].y = Relativevertices[4].y * SY / InitY;

	double _allY = PosiY - Relativevertices[0].y;
	Vec2 posi(Relativevertices[0].x , PosiY - (_allY * SY / InitY));
	Relativevertices[0].set(posi);

	_allY = PosiY - Relativevertices[1].y;
	posi.set(Relativevertices[1].x, PosiY - (_allY * SY / InitY));
	Relativevertices[1].set(posi);

	_allY = PosiY - Relativevertices[2].y;
	posi.set(Relativevertices[2].x, PosiY - (_allY * SY / InitY));
	Relativevertices[2].set(posi);

	_allY = PosiY - Relativevertices[3].y;
	posi.set(Relativevertices[3].x, PosiY - (_allY * SY / InitY));
	Relativevertices[3].set(posi);

	_allY = PosiY - Relativevertices[4].y;
	posi.set(Relativevertices[4].x, PosiY - (_allY * SY / InitY));
	Relativevertices[4].set(posi);




	_allY = PosiY - RelativeRotateVertices[0].y;
	posi.set(RelativeRotateVertices[0].x, PosiY - (_allY * SY / InitY));
	RelativeRotateVertices[0].set(posi);

	_allY = PosiY - RelativeRotateVertices[1].y;
	posi.set(RelativeRotateVertices[1].x, PosiY - (_allY * SY / InitY));
	RelativeRotateVertices[1].set(posi);

	_allY = PosiY - RelativeRotateVertices[2].y;
	posi.set(RelativeRotateVertices[2].x, PosiY - (_allY * SY / InitY));
	RelativeRotateVertices[2].set(posi);

	_allY = PosiY - RelativeRotateVertices[3].y;
	posi.set(RelativeRotateVertices[3].x, PosiY - (_allY * SY / InitY));
	RelativeRotateVertices[3].set(posi);

	_allY = PosiY - RelativeRotateVertices[4].y;
	posi.set(RelativeRotateVertices[4].x, PosiY - (_allY * SY / InitY));
	RelativeRotateVertices[4].set(posi);

	doubleToDoubletwo();

}
void DrawNodeVertices::setRotateVertices(Vec2 startPoint, Vec2 EndPoint, double _temp)
{
	//x=(x1-x2)cos¦È-(y1-y2)sin¦È+x2
	//y=(y1-y2)cos¦È+(x1-x2)sin¦È+y2
	//x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	//y = (one.y - two.y) * cos(rotate) + (one.x - two.x) * sin(rotate) + two.y;

	//x2 = (y1 - y0)*sina¡ã + (x1 - x0)*cosa¡ã
	//y2 = (y1 - y0)*cosa¡ã - (x1 - x0)*sina¡ã
	//x = (one.y - two.y) * sin(rotate) + (one.x - two.x) * cos(rotate);
	//y = (one.y - two.y) * cos(rotate) - (one.x - two.x) * sin(rotate);

	//xA`=x + (ax - x)cosk - (ay - y)sinK
	//yA`=y + (ax - x)sink + (ay - y)cosk
	//x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	//y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;

	//x0 = (x - rx0)*cos(a) - (y - ry0)*sin(a) + rx0;

	//y0 = (x - rx0)*sin(a) + (y - ry0)*cos(a) + ry0;

	if (_temp == -720)
	{
		_temp = Rotate;
	}
	//_temp = 90 - _temp;
	//double rotate = M_PI / 180.0 * (_temp * 1.0);
	double rotate = _temp;
	//rotate = _temp * 57.3;
	//log("%f", rotate);
	double x, y;
	Vec2 one = startPoint;
	Vec2 two = getMidPoint();
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RotateVertices[0].set(Vec2(x, y));

	one = Vec2(EndPoint.x, startPoint.y);
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RotateVertices[1].set(Vec2(x, y));

	one = EndPoint;
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RotateVertices[2].set(Vec2(x, y));

	one = Vec2(startPoint.x, EndPoint.y);
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RotateVertices[3].set(Vec2(x, y));

	RotateVertices[4].set(RotateVertices[0]);
	doubleToDoubletwo();
}
void DrawNodeVertices::setRotateRelativeVertices(Vec2 startPoint, Vec2 EndPoint, double _temp)
{
	//x=(x1-x2)cos¦È-(y1-y2)sin¦È+x2
	//y=(y1-y2)cos¦È+(x1-x2)sin¦È+y2
	//x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	//y = (one.y - two.y) * cos(rotate) + (one.x - two.x) * sin(rotate) + two.y;

	//x2 = (y1 - y0)*sina¡ã + (x1 - x0)*cosa¡ã
	//y2 = (y1 - y0)*cosa¡ã - (x1 - x0)*sina¡ã
	//x = (one.y - two.y) * sin(rotate) + (one.x - two.x) * cos(rotate);
	//y = (one.y - two.y) * cos(rotate) - (one.x - two.x) * sin(rotate);

	//xA`=x + (ax - x)cosk - (ay - y)sinK
	//yA`=y + (ax - x)sink + (ay - y)cosk
	//x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	//y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;

	//x0 = (x - rx0)*cos(a) - (y - ry0)*sin(a) + rx0;

	//y0 = (x - rx0)*sin(a) + (y - ry0)*cos(a) + ry0;

	if (_temp == -720)
	{
		_temp = Rotate;
	}
	//_temp = 90 - _temp;
	//double rotate = M_PI / 180.0 * (_temp * 1.0);
	double rotate = _temp;
	//rotate = _temp * 57.3;
	//log("%f", rotate);
	double x, y;
	Vec2 one = startPoint;
	Vec2 two = getRelateMidPoint();
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RelativeRotateVertices[0].set(Vec2(x, y));

	one = Vec2(EndPoint.x, startPoint.y);
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RelativeRotateVertices[1].set(Vec2(x, y));

	one = EndPoint;
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RelativeRotateVertices[2].set(Vec2(x, y));

	one = Vec2(startPoint.x, EndPoint.y);
	x = (one.x - two.x) * cos(rotate) - (one.y - two.y) * sin(rotate) + two.x;
	y = (one.x - two.x) * sin(rotate) + (one.y - two.y) * cos(rotate) + two.y;
	RelativeRotateVertices[3].set(Vec2(x, y));

	RelativeRotateVertices[4].set(RelativeRotateVertices[0]);
	doubleToDoubletwo();
}

Vec2 DrawNodeVertices::getMidPoint()
{
	return Vec2((Vertices[0].x + Vertices[2].x) / 2, (Vertices[0].y + Vertices[2].y) / 2);
}
Vec2 DrawNodeVertices::getRelateMidPoint()
{
	return Vec2((Relativevertices[0].x + Relativevertices[2].x) / 2, (Relativevertices[0].y + Relativevertices[2].y) / 2);
}

double DrawNodeVertices::getRotate(Vec2 StartPoint, Vec2 EndPoint, Vec2 midPoint)
{
	if (midPoint == Vec2(-1000 , -1000))
	{
		midPoint = getMidPoint();
	}
	int ro;
	double len_a, len_b, len_c;
	len_a = sqrt(((StartPoint.x - midPoint.x)) * ((StartPoint.x - midPoint.x)) + ((StartPoint.y - midPoint.y)) * ((StartPoint.y - midPoint.y)));
	len_b = sqrt(((StartPoint.x - EndPoint.x)) * ((StartPoint.x - EndPoint.x)) + ((StartPoint.y - EndPoint.y)) * ((StartPoint.y - EndPoint.y)));
	len_c = sqrt(((midPoint.x - EndPoint.x)) * ((midPoint.x - EndPoint.x)) + ((midPoint.y - EndPoint.y)) * ((midPoint.y - EndPoint.y) ));
	CosB = (len_a * len_a + len_c * len_c - len_b * len_b) / (2 * len_a * len_c);
	SinB = sqrt(1 - CosB * CosB);

	return CosB;

}
double DrawNodeVertices::myabs(double dt)
{
	return dt < 0 ? -dt : dt;
}

void DrawNodeVertices::updateRetlativeVertices()
{
	Relativevertices[1].set(Relativevertices[2].x, Relativevertices[0].y);
	Relativevertices[3].set(Relativevertices[0].x, Relativevertices[2].y);
	Relativevertices[4].set(Relativevertices[0]);
	doubleToDoubletwo();
}

void DrawNodeVertices::updateRetlativeVertices(double _w, double _h, double _sx, double _sy)
{
	if (_sy == 0.0 || _sx == 0.0)
	{
		return;
	}
	double _tew, _teh, _tesx, _tesy;
	_tew = _w - _last_Width;
	_teh = _h - _last_Height;
	if (_sx != _last_ScallX || _sy != _last_ScallY)
	{
		setRelativeScallX(_last_Width, _last_ScallX, _IN_ScallX);
		setRelativeScallY(_last_Height, _last_ScallY, _IN_ScallY);
		setRelativeScallX(_last_Width, _IN_ScallX, _sx);
		setRelativeScallY(_last_Height, _IN_ScallY, _sy);
	}
	Vec2 reposi(_tew, _teh);
	Relativevertices[0].set(Relativevertices[0] + reposi);
	Relativevertices[2].set(Relativevertices[2] + reposi);
	updateRetlativeVertices();

	_last_Height = _h;
	_last_Width = _w;
	_last_ScallX = _sx;
	_last_ScallY = _sy;
	doubleToDoubletwo();
}

void DrawNodeVertices::updateVertices()
{
	Vertices[1].set(Vertices[2].x, Vertices[0].y);
	Vertices[3].set(Vertices[0].x, Vertices[2].y);
	Vertices[4].set(Vertices[0]);
	doubleToDoubletwo();
}

DrawNodeVertices * DrawNodeVertices::copy()
{
	DrawNodeVertices * _copy = new DrawNodeVertices();
	_copy->is_visible = is_visible;
	int i = 0;
	for (i = 0; i < 5; i ++)
	{
		_copy->RelativeRotateVertices[i].set(RelativeRotateVertices[i]);
		_copy->RelativeScallX = RelativeScallX;
		_copy->RelativeScallY = RelativeScallY;
		_copy->Relativevertices[i].set(Relativevertices[i]);
		_copy->Rotate = Rotate;
		_copy->Singl_ID = Singl_ID;
		_copy->Vertices[i].set(Vertices[i]);
		_copy->RelativePosition.set(RelativePosition);
	}
	_copy->_last_Height = _last_Height;
	_copy->_last_Width = _last_Width;
	_copy->_last_ScallX = _last_ScallX;
	_copy->_last_ScallY = _last_ScallY;
	return _copy;
}

void DrawNodeVertices::reset()
{
	_last_ScallX = _IN_ScallX;
	_last_ScallY = _IN_ScallY;
	_last_Width = _IN_Width;
	_last_Height = _IN_Height;
	Rotate = 0;
	int i = 0;
	for (i = 0; i < 5; i ++)
	{
		Vertices[i].setZero();
		RotateVertices[i].setZero();
		Relativevertices[i].setZero();
		RelativeRotateVertices[i].setZero();
	}
}

void DrawNodeVertices::doubleToDoubletwo()
{
	double _x , _y;
	char str[20];
	int i = 0;
	for (i = 0; i < 5; i ++)
	{
		std::sprintf(str, "%.2f", RelativeRotateVertices[i].x);
		_x = std::atof(str);
		std::sprintf(str, "%.2f", RelativeRotateVertices[i].y);
		_y = std::atof(str);
		RelativeRotateVertices[i].set(_x, _y);

		std::sprintf(str, "%.2f", Relativevertices[i].x);
		_x = std::atof(str);
		std::sprintf(str, "%.2f", Relativevertices[i].y);
		_y = std::atof(str);
		Relativevertices[i].set(_x, _y);

		std::sprintf(str, "%.2f", Vertices[i].x);
		_x = std::atof(str);
		std::sprintf(str, "%.2f", Vertices[i].y);
		_y = std::atof(str);
		Vertices[i].set(_x, _y);

		std::sprintf(str, "%.2f", RotateVertices[i].x);
		_x = std::atof(str);
		std::sprintf(str, "%.2f", RotateVertices[i].y);
		_y = std::atof(str);
		RotateVertices[i].set(_x, _y);
	}
}
