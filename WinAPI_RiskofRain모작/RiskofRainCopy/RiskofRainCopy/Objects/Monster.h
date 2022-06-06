#pragma once
#include "../framework.h"
#include <vector>
using std::vector;

class MONSTER
{
public:
	enum class STATE
	{
		Idle = 0,
		Walk,
		Jump,
		Skill1,
		Skill2,
		Death,
		Max
	};

private:
	MONSTER::STATE eState;
	int		nHP;
	int		nMaxHP;
	int		nEXP;
	int		nMaxEXP;
	int		nLevel;
	int		nMoveSpeed;
	int		nJumpPower;
	int		nGravity;
	int		nGravityMax;
	int		nFacingDirection;
	POINT	ptPos;
	POINT	ptVelocity;
	int		nCollisionWidth;
	int		nCollisionHeight;
	int		nScale;
	bool	bEnableMove;
	bool	bIsInAir;
	bool    nextAir;
	bool	bIsInScreen;
	int		nSpriteNum;
	int		nSpriteMax[(unsigned int)MONSTER::STATE::Max];
	POINT	ptSpriteStart[(unsigned int)MONSTER::STATE::Max];
	int		nSpriteWidth[(unsigned int)MONSTER::STATE::Max];
	int		nSpriteHeight[(unsigned int)MONSTER::STATE::Max];
	POINT	ptCharCenter[(unsigned int)MONSTER::STATE::Max];

public:
	MONSTER();
	void Init();
	void Update();
	void Release();

	int		getHP();
	void	setHP(int _nHP);
	int		getMaxHP();
	void	setMaxHP(int _nMaxHP);
	int		getEXP();
	void	setEXP(int _nEXP);
	int		getMaxEXP();
	void	setMaxEXP(int _nMaxEXP);
	int		getLevel();
	void	setLevel(int _nLevel);
	int		getMoveSpeed();
	void	setMoveSpeed(int _nMoveSpeed);
	int		getFacingDirection();
	void	setFacingDirection(int _nFacingDirection);
	int		getCollisionWidth();
	void	setCollisionWidth(int _nCollisionWidth);
	int		getColiisionHeight();
	void	setCollisionHeight(int _nCollisionHeight);
	int		getSpriteNum();
	void	setSpriteNum(int _nSpriteNum);
	POINT*	getPos();
	void	setPos(POINT _ptPos);

	void	DrawMonster(Graphics &graphics, Image* pSurvivorImg, POINT * ptCamera, Rect * clientRect, int nMagnification);
	void	LevelUp();
	void	UpdateFrame();
	void	transitionState(STATE _eState);
	void	monsterDo();
	void	monsterMove(int nX, int nY);
	void	monsterIsInAir(vector<Rect>* vec_CollisionMap);
	void	monsterIsInScreen(POINT* ptCamera, Rect* clientRect, int nMagnification);

	bool collisionRect(const Rect & rect1, const Rect& rect2) const;
};