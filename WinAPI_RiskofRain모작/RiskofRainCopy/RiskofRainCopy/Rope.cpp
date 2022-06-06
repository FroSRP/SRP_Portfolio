#include "Rope.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void ROPE::Init(const char * strFile)
{
	Load(strFile);
}

void ROPE::Load(const char * strFile)
{
	ifstream finRope;
	finRope.open(strFile);
	if (!finRope.is_open())
	{
		return;
	}

	string strData[4];
	int nCx, nCy, nWidth, nHeight;

	finRope >> strData[0];
	nRopeNum = stoi(strData[0]);

	while (!finRope.eof())
	{
		for (int i = 0; i < 4; i++)
		{
			finRope >> strData[i];
		}
		nCx = stoi(strData[0]);
		nCy = stoi(strData[1]);
		nWidth = stoi(strData[2]);
		nHeight = stoi(strData[3]);

		vec_ropeRect.push_back(Rect(nCx, nCy, nWidth, nHeight));
	}

	finRope.close();
	return;
}

void ROPE::Release()
{
}

int ROPE::getRopeNum()
{
	return nRopeNum;
}

vector<Rect>* ROPE::getRopeRect()
{
	return &vec_ropeRect;
}

void ROPE::DrawCollisionBox(Graphics & graphics, POINT * ptCamera, Rect * clientRect, int nMagnification)
{
	//Pen pen(Color(240, 240, 240));

	//for (int nRectIndex = 0; nRectIndex < nRopeNum; nRectIndex++)
	//{
	//	graphics.DrawRectangle(&pen, (vec_ropeRect[nRectIndex].X - ptCamera->x) * nMagnification + (clientRect->Width / 2),
	//		(vec_ropeRect[nRectIndex].Y - ptCamera->y) * nMagnification + (clientRect->Height / 2),
	//		vec_ropeRect[nRectIndex].Width * nMagnification, vec_ropeRect[nRectIndex].Height * nMagnification);
	//}
}