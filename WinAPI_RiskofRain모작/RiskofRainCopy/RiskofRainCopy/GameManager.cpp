#include "GameManager.h"

GAMEMANAGER::GAMEMANAGER() :
	eState{},
	cGraphics{},
	pHWnd{},
	ptMousePos{},
	cSurvivor{}
{
}

GAMEMANAGER::~GAMEMANAGER()
{
}

GAMEMANAGER * GAMEMANAGER::getInstance()
{
	static GAMEMANAGER instance;
	return &instance;
}

void GAMEMANAGER::Init(HWND* _pHWnd)
{
	transitionState(GAMEMANAGER::STATE::gameLobby);
	cSurvivor.Init();
	cGraphics.setSurvivor(&cSurvivor);
	pHWnd = _pHWnd;
	cMap.Init("Risk_of_Rain_mapdata_water.txt");
	cRope.Init("Risk_of_Rain_ropedata_water.txt");
	cGraphics.setMap(&cMap);
	cGraphics.setRope(&cRope);
	cGraphics.setMonster(&vec_cMonster, &nMonsterNum);
	vec_cMonster.push_back(MONSTER());
}

void GAMEMANAGER::Update()
{
	DWORD newTime = GetTickCount();

	static DWORD oldTime = newTime;

	if (newTime - oldTime < 34)
	{
		return;
	}
	oldTime = newTime;

	switch (eState)
	{
	case GAMEMANAGER::STATE::gamePlay:
		cSurvivor.Update();
		cSurvivor.survivorIsInAir(cMap.getRectCulling());
		cSurvivor.survivorIsOnRope(cRope.getRopeRect(), cRope.getRopeNum());
		
		nMonsterNum = vec_cMonster.size();
		for (int nIndex = 0; nIndex < nMonsterNum; nIndex++)
		{
			vec_cMonster[nIndex].Update();
			vec_cMonster[nIndex].monsterIsInAir(cMap.getRectCulling());
		}

		break;
	}

	UpdateFrame();
}

void GAMEMANAGER::Render()
{
	if (*pHWnd == NULL)
	{
		return;
	}

	DWORD newTime = GetTickCount();

	static DWORD oldTime = newTime;

	if (newTime - oldTime < 17)
	{
		return;
	}
	oldTime = newTime;

	HDC hdc = GetDC(*pHWnd);
	cGraphics.DrawBitmapDoubleBuffering(*pHWnd, hdc);
	ReleaseDC(*pHWnd, hdc);
}

void GAMEMANAGER::transitionState(STATE _eState)
{
	eState = _eState;
	cGraphics.setPaint((int)eState);
}

void GAMEMANAGER::Release()
{
	cSurvivor.Release();
	cGraphics.Gdi_End();
}

void GAMEMANAGER::UpdateFrame()
{
	cSurvivor.UpdateFrame();
	for (int nIndex = 0; nIndex < nMonsterNum; nIndex++)
	{
		vec_cMonster[nIndex].UpdateFrame();
	}
}

GAMEMANAGER::STATE GAMEMANAGER::getState()
{
	return eState;
}

GRAPHICS& GAMEMANAGER::getGraphics()
{
	return cGraphics;
}

UI & GAMEMANAGER::getUI()
{
	return getGraphics().getUI();
}

void GAMEMANAGER::setMousePos(POINT* _ptMousePos)
{
	ptMousePos = _ptMousePos;
	cGraphics.setMousePos(ptMousePos);
}

void GAMEMANAGER::LButtonDown()
{
	switch (eState)
	{
	case GAMEMANAGER::STATE::gameLobby:
		{
			UI::BUTTON eMenu = cGraphics.getUI().LButtonDown();
			switch (eMenu)
			{
			case UI::BUTTON::E_MAX:
				break;
			case UI::BUTTON::Start:
				transitionState(GAMEMANAGER::STATE::gamePlay);
				break;
			case UI::BUTTON::Quit:
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}
		break;
	default:
		return;
	}
	
}

SURVIVOR & GAMEMANAGER::getSurvivor()
{
	return cSurvivor;
}

MAP & GAMEMANAGER::getMap()
{
	return cMap;
}

ROPE & GAMEMANAGER::getRope()
{
	return cRope;
}