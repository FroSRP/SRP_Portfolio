#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void MAP::Init(const char* strFile)
{
	Load(strFile);
}

void MAP::Load(const char* strFile)
{
	ifstream finMap;
	finMap.open(strFile);
	if (!finMap.is_open())
	{
		return;
	}
	
	string strData[4];
	int nCx, nCy, nWidth, nHeight;
	
	for (int i = 0; i < 3; i++)
	{
		finMap >> strData[i];
	}
	nSizeX = stoi(strData[0]);
	nSizeY = stoi(strData[1]);
	nCollisionRectNum = stoi(strData[2]);

	while (!finMap.eof())
	{
		for (int i = 0; i < 4; i++)
		{
			finMap >> strData[i];
		}
		nCx = stoi(strData[0]);
		nCy = stoi(strData[1]);
		nWidth = stoi(strData[2]);
		nHeight = stoi(strData[3]);

		vec_rectCollision.push_back(Rect(nCx, nCy, nWidth, nHeight));
	}

	finMap.close();
	return;
}

void MAP::Release()
{

}

int MAP::getSizeX()
{
	return nSizeX;
}

int MAP::getSizeY()
{
	return nSizeY;
}

int MAP::getCollisionRectNum()
{
	return nCollisionRectNum;
}

vector<Rect>* MAP::getRectCulling()
{
	return &vec_rectCulling;
}

void MAP::DrawCollisionBox(Graphics & graphics, POINT* ptCamera, Rect* clientRect, int nMagnification)
{
	Pen pen(Color(240, 240, 240));
	vec_rectCulling.clear();
	for (int nRectIndex = 0; nRectIndex < nCollisionRectNum; nRectIndex++)
	{
		if (overlapsRect(Rect(ptCamera->x - clientRect->Width / (nMagnification * 2), ptCamera->y - clientRect->Height / (nMagnification * 2),
			clientRect->Width / nMagnification, clientRect->Height / nMagnification), vec_rectCollision[nRectIndex]))
		{
			vec_rectCulling.push_back(vec_rectCollision[nRectIndex]);
		}
	}

	//int nRectCullingNum = vec_rectCulling.size();
	//for (int nRectIndex = 0; nRectIndex < nRectCullingNum; nRectIndex++)
	//{
	//	graphics.DrawRectangle(&pen, (vec_rectCulling[nRectIndex].X - ptCamera->x) * nMagnification + (clientRect->Width / 2),
	//		(vec_rectCulling[nRectIndex].Y - ptCamera->y) * nMagnification + (clientRect->Height / 2),
	//		vec_rectCulling[nRectIndex].Width * nMagnification, vec_rectCulling[nRectIndex].Height * nMagnification);
	//}
}

bool MAP::overlapsRect(const Rect & rect1, const Rect& rect2) const
{
	if (rect2.GetRight() > rect1.GetLeft() && rect2.GetLeft() < rect1.GetRight() &&
		rect2.GetBottom() > rect1.GetTop() && rect2.GetTop() < rect1.GetBottom())
	{
		return true;
	}
	else
	{
		return false;
	}
}