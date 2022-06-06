#pragma once
#include "framework.h"

class ROPE
{
private:
	int nRopeNum;
	vector<Rect> vec_ropeRect;

public:
	void Init(const char* strFile);
	void Load(const char* strFile);
	void Release();

	int getRopeNum();
	vector<Rect>* getRopeRect();
	void DrawCollisionBox(Graphics &graphics, POINT* ptCamera, Rect* clientRect, int nMagnification);
};