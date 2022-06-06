#pragma once
#include "framework.h"

class MAP
{
private:
	int nSizeX;
	int nSizeY;
	int nCollisionRectNum;
	vector<Rect> vec_rectCollision;
	vector<Rect> vec_rectCulling;
	
public:
	void Init(const char* strFile);
	void Load(const char* strFile);
	void Release();

	int getSizeX();
	int getSizeY();
	int getCollisionRectNum();
	vector<Rect>* getRectCulling();
	void DrawCollisionBox(Graphics &graphics, POINT* ptCamera, Rect* clientRect, int nMagnification);

	bool overlapsRect(const Rect & rect1, const Rect& rect2) const;
};