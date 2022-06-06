#pragma once
#include "../framework.h"
#include "../UI.h"
#include "../Objects/Survivor.h"
#include "../Map.h"
#include "../Rope.h"
#include "../Objects/Monster.h"

class GRAPHICS
{
private:
	HBITMAP				hDoubleBufferImage;
	Image*				pLobbyImg;
	Image*				pMapImg;
	RECT				rectView;
	UI					cUI;
	Gdiplus::Rect		clientRect;
	POINT*				ptMousePos;
	Image*				pSurvivorImg;
	SURVIVOR*			pSurvivor;
	MAP*				pMap;
	ROPE*				pRope;
	POINT*				ptCamera;
	int					nMagnification;
	Image*				pMonsterImg;
	vector<MONSTER>*	pMonster;
	int*				nMonsterNum;

public:
	ULONG_PTR	g_GdiToken;
	void		(GRAPHICS::*OnGdi_Paint)(Graphics&);

public:
	void			DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
	void			Gdi_Init();
	void			Gdi_Draw(HDC hdc);
	void			Gdi_End();
	void			setPaint(int nStatus);
	void			setClientRect(HWND hWnd);
	Gdiplus::Rect*	getClientRect();
	void			DrawLobby(Graphics &graphics);
	void			DrawPlay(Graphics &graphics);
	void			DrawOver(Graphics &graphics);
	UI&				getUI();
	void			setMousePos(POINT* _ptMousePos);
	void			setSurvivor(SURVIVOR* _pSurvivor);
	void			setMap(MAP* _pMap);
	void			setRope(ROPE* _pRope);
	void			setCamera(POINT* _ptCamera);
	void			setMonster(vector<MONSTER>* _pMonster, int* _nMonsterNum);

};