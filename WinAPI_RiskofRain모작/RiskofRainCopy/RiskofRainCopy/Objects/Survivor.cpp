#include "Survivor.h"

void SURVIVOR::Init()
{
	eState					= SURVIVOR::STATE::Idle;
	nMaxHP					= 100;
	nHP						= nMaxHP;
	nMaxEXP					= 100;
	nEXP					= 0;
	nLevel					= 1;
	nMoveSpeed				= 4;
	nJumpPower				= 12;
	nGravity				= 2;
	nGravityMax				= 24;
	nFacingDirection		= 1;
	ptPos					= POINT{ 1920 / 2, 1080 / 2 };
	ptImagePos				= POINT{ 1920 / 2, 1080 / 2 };
	nCollisionWidth			= 5;
	nCollisionHeight		= 10;
	nScale					= 3;
	ptVelocity				= POINT{ 0, 0 };
	bEnableMove				= true;
	bIsInAir				= false;
	bIsClimb				= false;
	bIsRopeOn				= false;
	nSpriteNum				= 0;
	nextAir = false;
	
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Idle]		= 1;
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Walk]		= 8;
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Jump]		= 1;
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Climb]	= 2;
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Skill1]	= 5;
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Skill2]	= 5;
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Skill3]	= 9;
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Skill4]	= 15;
	nSpriteMax[(unsigned int)SURVIVOR::STATE::Death]	= 5;

	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Idle]		= POINT{ 0, 0 };
	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Walk]		= POINT{ 0, 12 };
	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Jump]		= POINT{ 0, 23 };
	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Climb]		= POINT{ 0, 34 };
	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Skill1]	= POINT{ 0, 46 };
	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Skill2]	= POINT{ 0, 58 };
	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Skill3]	= POINT{ 0, 69 };
	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Skill4]	= POINT{ 0, 81 };
	ptSpriteStart[(unsigned int)SURVIVOR::STATE::Death]		= POINT{ 0, 107 };

	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Idle]		= 19;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Idle]		= 11;
	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Walk]		= 5;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Walk]		= 10;
	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Jump]		= 5;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Jump]		= 10;
	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Climb]		= 5;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Climb]		= 10;
	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Skill1]		= 19;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Skill1]	= 11;
	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Skill2]		= 31;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Skill2]	= 10;
	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Skill3]		= 11;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Skill3]	= 11;
	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Skill4]		= 37;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Skill4]	= 12;
	nSpriteWidth[(unsigned int)SURVIVOR::STATE::Death]		= 17;
	nSpriteHeight[(unsigned int)SURVIVOR::STATE::Death]		= 8;

	ptCharCenter[(unsigned int)SURVIVOR::STATE::Idle]	= POINT{ 5, 11 };
	ptCharCenter[(unsigned int)SURVIVOR::STATE::Walk]	= POINT{ 2, 10 };
	ptCharCenter[(unsigned int)SURVIVOR::STATE::Jump]	= POINT{ 2, 10 };
	ptCharCenter[(unsigned int)SURVIVOR::STATE::Climb]	= POINT{ 2, 10 };
	ptCharCenter[(unsigned int)SURVIVOR::STATE::Skill1]	= POINT{ 5, 11 };
	ptCharCenter[(unsigned int)SURVIVOR::STATE::Skill2] = POINT{ 4, 10 };
	ptCharCenter[(unsigned int)SURVIVOR::STATE::Skill3]	= POINT{ 6, 11 };
	ptCharCenter[(unsigned int)SURVIVOR::STATE::Skill4]	= POINT{ 18, 12 };
	ptCharCenter[(unsigned int)SURVIVOR::STATE::Death]	= POINT{ 15, 8 };
}

void SURVIVOR::Release()
{
}

int SURVIVOR::getHP()
{
	return nHP;
}

void SURVIVOR::setHP(int _nHP)
{
	nHP = _nHP;
}

int SURVIVOR::getMaxHP()
{
	return nMaxHP;
}

void SURVIVOR::setMaxHP(int _nMaxHP)
{
	nMaxHP = _nMaxHP;
}

int SURVIVOR::getEXP()
{
	return nEXP;
}

void SURVIVOR::setEXP(int _nEXP)
{
	nEXP = _nEXP;
}

int SURVIVOR::getMaxEXP()
{
	return nMaxEXP;
}

void SURVIVOR::setMaxEXP(int _nMaxEXP)
{
	nMaxEXP = _nMaxEXP;
}

int SURVIVOR::getLevel()
{
	return nLevel;
}

void SURVIVOR::setLevel(int _nLevel)
{
	nLevel = _nLevel;
}

int SURVIVOR::getMoveSpeed()
{
	return nMoveSpeed;
}

void SURVIVOR::setMoveSpeed(int _nMoveSpeed)
{
	nMoveSpeed = _nMoveSpeed;
}

int SURVIVOR::getFacingDirection()
{
	return nFacingDirection;
}

void SURVIVOR::setFacingDirection(int _nFacingDirection)
{
	nFacingDirection = _nFacingDirection;
}

int SURVIVOR::getCollisionWidth()
{
	return nCollisionWidth;
}

void SURVIVOR::setCollisionWidth(int _nCollisionWidth)
{
	nCollisionWidth = _nCollisionWidth;
}

int SURVIVOR::getColiisionHeight()
{
	return nCollisionHeight;
}

void SURVIVOR::setCollisionHeight(int _nCollisionHeight)
{
	nCollisionHeight = _nCollisionHeight;
}

int SURVIVOR::getSpriteNum()
{
	return nSpriteNum;
}

void SURVIVOR::setSpriteNum(int _nSpriteNum)
{
	nSpriteNum = _nSpriteNum;
}

POINT* SURVIVOR::getPos()
{
	return &ptPos;
}

void SURVIVOR::setPos(POINT _ptPos)
{
	ptPos = _ptPos;
}

void SURVIVOR::DrawSurvivor(Graphics & graphics, Image* pSurvivorImg)
{
	ImageAttributes imgAttr;
	imgAttr.SetColorKey(Color(240, 0, 240), Color(255, 10, 255));
	Pen pen(Color(240, 240, 240));

	nSpriteNum %= nSpriteMax[(unsigned int)eState];
	graphics.DrawImage(pSurvivorImg, Rect(ptImagePos.x - (ptCharCenter[(unsigned int)eState].x + (nFacingDirection == -1)) * nScale * nFacingDirection,
		ptImagePos.y - ptCharCenter[(unsigned int)eState].y * nScale,
		nSpriteWidth[(unsigned int)eState] * nScale * nFacingDirection, nSpriteHeight[(unsigned int)eState] * nScale),
		ptSpriteStart[(unsigned int)eState].x + nSpriteNum * (nSpriteWidth[(unsigned int)eState] + 1), ptSpriteStart[(unsigned int)eState].y,
		nSpriteWidth[(unsigned int)eState], nSpriteHeight[(unsigned int)eState], UnitPixel, &imgAttr);
	//graphics.DrawRectangle(&pen, Rect(ptImagePos.x - ptCharCenter[(unsigned int)eState].x * nScale, ptImagePos.y - ptCharCenter[(unsigned int)eState].y * nScale,
	//	nSpriteWidth[(unsigned int)eState] * nScale, nSpriteHeight[(unsigned int)eState] * nScale));
	//graphics.DrawRectangle(&pen, Rect(ptImagePos.x - (nCollisionWidth / 2) * nScale, ptImagePos.y - nCollisionHeight * nScale,
	//	nCollisionWidth * nScale, nCollisionHeight * nScale));
}

void SURVIVOR::LevelUp()
{
	nHP += 10;
	nMaxHP += 10;
	nEXP = 0;
	nMaxEXP += 10;
	nLevel += 1;
}

void SURVIVOR::Update()
{
	if (bIsInAir && !bIsClimb && ptVelocity.y < nGravityMax)
	{
		printf_s("¶³¾îÁö´ÂÁß%d\n", bIsInAir);
		ptVelocity.y += nGravity;
	}
	survivorMove(ptVelocity.x, ptVelocity.y);
}

void SURVIVOR::UpdateFrame()
{
	nSpriteNum++;
	survivorDo();
}

void SURVIVOR::transitionState(STATE _eState)
{
	eState = _eState;
}

void SURVIVOR::survivorDo()
{
	switch (eState)
	{
	case SURVIVOR::STATE::Idle:
		{
			checkLeftKey();
			checkRightKey();
			checkUpKey();
			checkDownKey();
			checkSpaceKey();
			checkZKey();
			checkXKey();
			checkCKey();
			checkVKey();
		}
		break;
	case SURVIVOR::STATE::Walk:
		{
			checkLeftKey();
			checkRightKey();
			checkUpKey();
			checkDownKey();
			checkSpaceKey();
			checkZKey();
			checkXKey();
			checkCKey();
			checkVKey();

			if (!(GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000))
			{
				ptVelocity.x = 0;
				transitionState(SURVIVOR::STATE::Idle);
			}
		}
		break;
	case SURVIVOR::STATE::Jump:
		{
			checkUpKey();
			checkDownKey();
			//checkSpaceKey();
			checkZKey();
			checkXKey();
			checkCKey();
			checkVKey();

			if (!bIsInAir)
			{
				ptVelocity.x = 0;
				ptVelocity.y = 0;
				transitionState(SURVIVOR::STATE::Idle);
			}
		}
		break;
	case SURVIVOR::STATE::Climb:
		{
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				nFacingDirection = -1;
				ptVelocity.x = nMoveSpeed * nFacingDirection;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				nFacingDirection = 1;
				ptVelocity.x = nMoveSpeed * nFacingDirection;
			}
			checkUpKey();
			checkDownKey();
			checkSpaceKey();

			bIsInAir = false;
			if (eState != SURVIVOR::STATE::Jump)
			{
				ptVelocity.y = 0;
				ptVelocity.x = 0;
			}
			if (!(GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000))
			{
				nSpriteNum = 0;
			}
			if (!bIsRopeOn)
			{
				transitionState(SURVIVOR::STATE::Idle);
			}
		}
		break;
	case SURVIVOR::STATE::Skill1:
		{
			if (!bIsInAir)
			{
				ptVelocity.x = 0;
			}

			if (nSpriteNum == 0 || nSpriteNum == 2)
			{

			}
			else if (nSpriteNum == nSpriteMax[(unsigned int)eState])
			{
				bEnableMove = true;
				if (bIsInAir)
				{
					transitionState(SURVIVOR::STATE::Jump);
				}
				else
				{
					transitionState(SURVIVOR::STATE::Idle);
				}
			}
		}
		break;
	case SURVIVOR::STATE::Skill2:
		{
			if (!bIsInAir)
			{
				ptVelocity.x = 0;
			}

			if (nSpriteNum == 0)
			{

			}
			else if (nSpriteNum == nSpriteMax[(unsigned int)eState])
			{
				bEnableMove = true;
				if (bIsInAir)
				{
					transitionState(SURVIVOR::STATE::Jump);
				}
				else
				{
					transitionState(SURVIVOR::STATE::Idle);
				}
			}
		}
		break;
	case SURVIVOR::STATE::Skill3:
		{
			ptVelocity.x = nFacingDirection;
			if (nSpriteNum == nSpriteMax[(unsigned int)eState])
			{
				bEnableMove = true;
				ptVelocity.x = 0;
				if (bIsInAir)
				{
					transitionState(SURVIVOR::STATE::Jump);
				}
				else
				{
					transitionState(SURVIVOR::STATE::Idle);
				}
			}
			else
			{
				survivorMove((nSpriteMax[(unsigned int)eState] - nSpriteNum) * 2 * nFacingDirection, 0);
			}
		}
		break;
	case SURVIVOR::STATE::Skill4:
		{
			if (!bIsInAir)
			{
				ptVelocity.x = 0;
			}

			if (nSpriteNum == 1 || nSpriteNum == 3 || nSpriteNum == 5 || nSpriteNum == 7 || nSpriteNum == 9 || nSpriteNum == 11)
			{

			}
			else if (nSpriteNum == nSpriteMax[(unsigned int)eState])
			{
				bEnableMove = true;
				if (bIsInAir)
				{
					transitionState(SURVIVOR::STATE::Jump);
				}
				else
				{
					transitionState(SURVIVOR::STATE::Idle);
				}
			}
		}
		break;
	case SURVIVOR::STATE::Death:
		{
			ptVelocity.x = 0;
			ptVelocity.y = 0;
			bEnableMove = false;
			if (nSpriteNum == nSpriteMax[(unsigned int)eState])
			{
				nSpriteNum = nSpriteMax[(unsigned int)eState] - 1;
			}
		}
		break;
	}
}

void SURVIVOR::survivorMove(int nX, int nY)
{
	ptPos.x += nX;
	ptPos.y += nY;
}

void SURVIVOR::survivorIsInAir(vector<Rect>* vec_CollisionMap)
{
	int nCollisionRectNum = vec_CollisionMap->size();
	Rect survivorRect(ptPos.x - (nCollisionWidth / 2), ptPos.y - nCollisionHeight, nCollisionWidth, nCollisionHeight);
	nextAir = true;
	for (int nRectNum = 0; nRectNum < nCollisionRectNum; nRectNum++)
	{
		if (collisionRect(survivorRect, (*vec_CollisionMap)[nRectNum]))
		{
			// Ãæµ¹ ½ÃÁ¡

			// º®ÀÌ¶û ºÎµúÈú ¶§
			// º®ÀÌ¶û ºÎµúÈ÷´Â °æ¿ì
			// 1. °É¾î°¡¼­ ºÎµúÈû
			// 2. ¶³¾îÁö´Ù ºÎµúÈû
			// 3. Á¡ÇÁÇÏ´Ù°¡ ¸Ó¸®°¡ ºÎµúÈû

			// °øÁß¿¡¼­ ºÎµúÈû yÀÇ ¼Óµµ°ªÀÌ ÀÖÀ» ¶§
			//

			if (!bIsInAir) {
				// °É¾î´Ù´Ò ¶§
				printf_s("°É¾î´Ù´Ñ´Ù. \n");
				if (survivorRect.GetBottom() == (*vec_CollisionMap)[nRectNum].GetTop()) {
					nextAir = false;
					continue;
				}
				if (ptVelocity.x > 0 && survivorRect.GetRight() > (*vec_CollisionMap)[nRectNum].GetLeft()) {
					ptPos.x = (*vec_CollisionMap)[nRectNum].GetLeft() - (nCollisionWidth / 2) * nScale;
					printf_s("¿ìÃø º®¿¡ ºÎµúÇû´Ù.\n", survivorRect.GetRight(), (*vec_CollisionMap)[nRectNum].GetLeft());
					return;
				}
				else if (ptVelocity.x < 0 && survivorRect.GetLeft() < (*vec_CollisionMap)[nRectNum].GetRight()) {
					ptPos.x = (*vec_CollisionMap)[nRectNum].GetRight() + (nCollisionWidth / 2 - 1) * nScale;
					printf_s("ÁÂÃø º®¿¡ ºÎµúÇû´Ù.\n");
					return;
				}
				else {
					continue;
				}
			}
			else {
				printf_s("³«ÇÏ Áß º®°ú Ãæµ¹. \n");
				// °Å¸® = ½Ã°£(ÀÏÁ¤ÇÔ) * ¼Óµµ
				if (ptVelocity.y == 0)
				{
					ptVelocity.x = 0;
					return;
				}
				else if (ptVelocity.x > 0)
				{
					int nDx = survivorRect.GetRight() - (*vec_CollisionMap)[nRectNum].GetLeft();
					int nDy = survivorRect.GetBottom() - (*vec_CollisionMap)[nRectNum].GetTop();
					int nX = nDx - ptVelocity.x * (nDy / ptVelocity.y);
					if (nX < 0)
					{
						ptVelocity.x = 0;
						return;
					}
				}
				else if (ptVelocity.x < 0)
				{
					int nDx = survivorRect.GetLeft() - (*vec_CollisionMap)[nRectNum].GetRight();
					int nDy = survivorRect.GetBottom() - (*vec_CollisionMap)[nRectNum].GetTop();
					int nX = nDx + ptVelocity.x * (nDy / ptVelocity.y);
					if (nX > 0)
					{
						ptVelocity.x = 0;
						return;
					}
				}

				ptPos.y = (*vec_CollisionMap)[nRectNum].GetTop();
				ptVelocity.y = 0;
				bIsInAir = false;
				return;
			}
		}
	}
	if (nextAir) {
		printf_s("º®¿¡ ¾ÈºÙ¾îÀÖÀ½. \n");
		bIsInAir = true;
		return;
	}
}

void SURVIVOR::survivorIsOnRope(vector<Rect>* vec_rope, int nRopeNum)
{
	Rect survivorRect(ptPos.x - (nCollisionWidth / 2), ptPos.y - nCollisionHeight, nCollisionWidth, nCollisionHeight);
	for (int nRectNum = 0; nRectNum < nRopeNum; nRectNum++)
	{
		if (collisionRect(survivorRect, (*vec_rope)[nRectNum]))
		{
			bIsRopeOn = true;
			return;
		}
	}

	bIsRopeOn = false;
	return;
}

void SURVIVOR::checkLeftKey()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		transitionState(SURVIVOR::STATE::Walk);
		nFacingDirection = -1;
		ptVelocity.x = nMoveSpeed * nFacingDirection;
	}
}

void SURVIVOR::checkRightKey()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		transitionState(SURVIVOR::STATE::Walk);
		nFacingDirection = 1;
		ptVelocity.x = nMoveSpeed * nFacingDirection;
	}
}

void SURVIVOR::checkUpKey()
{
	if (bIsRopeOn && GetAsyncKeyState(VK_UP) & 0x8000)
	{
		transitionState(SURVIVOR::STATE::Climb);
		survivorMove(0, -nMoveSpeed);
	}
}

void SURVIVOR::checkDownKey()
{
	if (bIsRopeOn && GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		transitionState(SURVIVOR::STATE::Climb);
		survivorMove(0, nMoveSpeed);
	}
}

void SURVIVOR::checkSpaceKey()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		ptVelocity.y = -nJumpPower;
		transitionState(SURVIVOR::STATE::Jump);
	}
}

void SURVIVOR::checkZKey()
{
	if (GetAsyncKeyState(0x5A) & 0x8000) // Z
	{
		bEnableMove = false;
		nSpriteNum = 0;
		transitionState(SURVIVOR::STATE::Skill1);
	}
}

void SURVIVOR::checkXKey()
{
	if (GetAsyncKeyState(0x58) & 0x8000) // X
	{
		bEnableMove = false;
		nSpriteNum = 0;
		transitionState(SURVIVOR::STATE::Skill2);
	}
}

void SURVIVOR::checkCKey()
{
	if (GetAsyncKeyState(0x43) & 0x8000) // C
	{
		bEnableMove = false;
		nSpriteNum = 0;
		transitionState(SURVIVOR::STATE::Skill3);
	}
}

void SURVIVOR::checkVKey()
{
	if (GetAsyncKeyState(0x56) & 0x8000) // V
	{
		bEnableMove = false;
		nSpriteNum = 0;
		transitionState(SURVIVOR::STATE::Skill4);
	}
}

bool SURVIVOR::collisionRect(const Rect & rect1, const Rect& rect2) const
{
	if (rect2.GetRight() >= rect1.GetLeft() && rect2.GetLeft() <= rect1.GetRight() &&
		rect2.GetBottom() >= rect1.GetTop() && rect2.GetTop() <= rect1.GetBottom())
	{
		return true;
	}
	else
	{
		return false;
	}
}