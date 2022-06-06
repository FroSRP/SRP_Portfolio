#pragma once
#include "framework.h"
#include "./Graphics/Graphics.h"
#include "./Objects/Survivor.h"
#include "Map.h"
#include "Rope.h"
#include "./Objects/Monster.h"

class GAMEMANAGER
{
public:
	enum class STATE
	{
		gameLobby = 0,
		gamePlay,
		E_MAX
	};

private:
	STATE				eState;
	GRAPHICS			cGraphics;
	HWND*				pHWnd;
	POINT*				ptMousePos;
	SURVIVOR			cSurvivor;
	MAP					cMap;
	ROPE				cRope;
	vector<MONSTER>		vec_cMonster;
	int					nMonsterNum;

private:
	GAMEMANAGER();

public:
	~GAMEMANAGER();
	static GAMEMANAGER*	getInstance();
	void		Init(HWND* _pHWnd);
	void		Update();
	void		Render();
	void		transitionState(STATE _eStatus);
	void		Release();
	void		UpdateFrame();
	STATE		getState();
	GRAPHICS&	getGraphics();
	UI&			getUI();
	void		setMousePos(POINT* _ptMousePos);
	void		LButtonDown();
	SURVIVOR&	getSurvivor();
	MAP&		getMap();
	ROPE&		getRope();
	MONSTER&	getMonster();
};

#define g_pGameManager GAMEMANAGER::getInstance()