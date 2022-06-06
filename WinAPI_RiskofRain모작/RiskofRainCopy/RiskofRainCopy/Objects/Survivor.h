#pragma once
#include "../framework.h"
#include <vector>
using std::vector;

class SURVIVOR
{
public:
	enum class STATE
	{
		Idle = 0,
		Walk,
		Jump,
		Climb,
		Skill1,
		Skill2,
		Skill3,
		Skill4,
		Death,
		Max
	};

private:
	SURVIVOR::STATE eState;
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
	POINT	ptImagePos;
	POINT	ptVelocity;
	int		nCollisionWidth;
	int		nCollisionHeight;
	int		nScale;
	bool	bEnableMove;
	bool	bIsInAir;
	bool	bIsClimb;
	bool	bIsRopeOn;
	bool    nextAir;
	int		nSpriteNum;
	int		nSpriteMax[(unsigned int)SURVIVOR::STATE::Max];
	POINT	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Max];
	int		nSpriteWidth[(unsigned int)SURVIVOR::STATE::Max];
	int		nSpriteHeight[(unsigned int)SURVIVOR::STATE::Max];
	POINT	ptCharCenter[(unsigned int)SURVIVOR::STATE::Max];

public:
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

	void	DrawSurvivor(Graphics &graphics, Image* pSurvivorImg);
	void	LevelUp();
	void	UpdateFrame();
	void	transitionState(STATE _eState);
	void	survivorDo();
	void	survivorMove(int nX, int nY);
	void	survivorIsInAir(vector<Rect>* vec_CollisionMap);
	void	survivorIsOnRope(vector<Rect>* vec_rope, int nRopeNum);

	void	checkLeftKey();
	void	checkRightKey();
	void	checkUpKey();
	void	checkDownKey();
	void	checkSpaceKey();
	void	checkZKey();
	void	checkXKey();
	void	checkCKey();
	void	checkVKey();

	bool collisionRect(const Rect & rect1, const Rect& rect2) const;
};