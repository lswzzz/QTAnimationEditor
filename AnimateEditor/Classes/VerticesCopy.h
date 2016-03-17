#pragma once
#include "cocos2d.h"
#include "MyConfig.h"
USING_NS_CC;
class VerticesCopy
{
public:
	VerticesCopy();
	static VerticesCopy * getinstance();
	static void destory();
	~VerticesCopy();

	inline bool is_has_copy(){ return _is_has_copy; };
	inline void set_is_has_copy(bool _is){ _is_has_copy = _is; };

	inline bool is_null(){ return _is_null; };
	inline void set_is_null(bool _is){ _is_null = _is; };

	inline void set_last_width(double _la){ _last_Width = _la; };
	inline double get_last_width(){ return _last_Width; };

	inline void set_last_height(double _la){ _last_Height = _la; };
	inline double get_last_height(){ return _last_Height; };

	inline void set_last_ScallX(double _la){ _last_ScallX = _la; };
	inline double get_last_ScallX(){ return _last_ScallX; };

	inline void set_last_ScallY(double _la){ _last_ScallY = _la; };
	inline double get_last_ScallY(){ return _last_ScallY; };

	inline void setRotate(double _ro){ Rotate = _ro; };
	inline double getRotate(){ return Rotate; };

	void setRelativevertices(Vec2 *&_temp);
	void setRelativeRotateVertices(Vec2 *&_temp);

	Vec2 * Relativevertices = nullptr;
	Vec2 * RelativeRotateVertices = nullptr;

private:
	static VerticesCopy * _VerticesCopy;
	double _last_Width = _IN_Width;
	double _last_Height = _IN_Height;
	double _last_ScallX = _IN_ScallX;
	double _last_ScallY = _IN_ScallY;
	bool _is_null = false;
	bool _is_has_copy = false;
	double Rotate;
};

