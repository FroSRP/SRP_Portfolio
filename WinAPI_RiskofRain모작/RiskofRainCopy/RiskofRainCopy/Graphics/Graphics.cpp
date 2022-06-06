#include "Graphics.h"

void GRAPHICS::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	if (!hMemDC)
	{
		MessageBox(hWnd, _T("CreateCompatibleDC failed"),
			_T("Error"), MB_OK);

		return;
	}
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc,
			rectView.right, rectView.bottom);
	}

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

	Gdi_Draw(hMemDC);

	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom,
		hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void GRAPHICS::Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiToken, &gpsi, NULL);

	pLobbyImg = new Image((WCHAR*)L"Graphics/images/title.jpg");
	pSurvivorImg = new Image((WCHAR*)L"Graphics/images/Survivor/Survivor_Commando_Sprite.png");
	pMapImg = new Image((WCHAR*)L"Graphics/images/Risk_of_Rain_map_water.png");
	pMonsterImg = new Image((WCHAR*)L"Graphics/images/Monster/Monster_Imp_Sprite.png");

	nMagnification = 2;
}

void GRAPHICS::Gdi_Draw(HDC hdc)
{
	Gdiplus::Graphics graphics(hdc);
	if (OnGdi_Paint == NULL)
	{
		return;
	}
	(this->*OnGdi_Paint)(graphics);
}

void GRAPHICS::Gdi_End()
{
	cUI.Release();
	GdiplusShutdown(g_GdiToken);
}

void GRAPHICS::setPaint(int nStatus)
{
	switch (nStatus)
	{
	case 0:
		OnGdi_Paint = &GRAPHICS::DrawLobby;
		break;
	case 1:
		OnGdi_Paint = &GRAPHICS::DrawPlay;
		break;
	}
}

void GRAPHICS::setClientRect(HWND hWnd)
{
	GetClientRect(hWnd, &rectView);
	clientRect = Gdiplus::Rect(rectView.left, rectView.top, rectView.right, rectView.bottom);
	cUI.Init(&clientRect);
}

Gdiplus::Rect * GRAPHICS::getClientRect()
{
	return &clientRect;
}

void GRAPHICS::DrawLobby(Graphics &graphics)
{
	graphics.DrawImage(pLobbyImg, 0, 0, clientRect.Width, clientRect.Height);
	cUI.whereMenuMouseOn(ptMousePos);
	cUI.DrawLobbyUI(graphics);
}

void GRAPHICS::DrawPlay(Graphics &graphics)
{
	graphics.DrawImage(pMapImg, RectF(0, 0, clientRect.Width, clientRect.Height),
		ptCamera->x - clientRect.Width / (nMagnification * 2), ptCamera->y - clientRect.Height / (nMagnification * 2),
		clientRect.Width / nMagnification, clientRect.Height / nMagnification, UnitPixel);

	for (int nIndex = 0; nIndex < (*nMonsterNum); nIndex++)
	{
		(*pMonster)[nIndex].monsterIsInScreen(ptCamera, &clientRect, nMagnification);
		(*pMonster)[nIndex].DrawMonster(graphics, pMonsterImg, ptCamera, &clientRect, nMagnification);
	}
	pSurvivor->DrawSurvivor(graphics, pSurvivorImg);
	pMap->DrawCollisionBox(graphics, ptCamera, &clientRect, nMagnification);
	pRope->DrawCollisionBox(graphics, ptCamera, &clientRect, nMagnification);
	
}

void GRAPHICS::DrawOver(Graphics &graphics)
{

}

UI & GRAPHICS::getUI()
{
	return cUI;
}

void GRAPHICS::setMousePos(POINT * _ptMousePos)
{
	ptMousePos = _ptMousePos;
}

void GRAPHICS::setSurvivor(SURVIVOR * _pSurvivor)
{
	pSurvivor = _pSurvivor;
	setCamera(pSurvivor->getPos());
}

void GRAPHICS::setMap(MAP * _pMap)
{
	pMap = _pMap;
}

void GRAPHICS::setRope(ROPE * _pRope)
{
	pRope = _pRope;
}

void GRAPHICS::setCamera(POINT * _ptCamera)
{
	ptCamera = _ptCamera;
}

void GRAPHICS::setMonster(vector<MONSTER>* _pMonster, int* _nMonsterNum)
{
	pMonster = _pMonster;
	nMonsterNum = _nMonsterNum;
}
