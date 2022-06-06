#include "Monster.h"

MONSTER::MONSTER()
{
	Init();
}

void MONSTER::Init()
{
	eState = MONSTER::STATE::Idle;
	nMaxHP = 100;
	nHP = nMaxHP;
	nMaxEXP = 100;
	nEXP = 0;
	nLevel = 1;
	nMoveSpeed = 4;
	nJumpPower = 12;
	nGravity = 2;
	nGravityMax = 24;
	nFacingDirection = 1;
	ptPos = POINT{ 1920 / 2, 1080 / 2 };
	nCollisionWidth = 17;
	nCollisionHeight = 21;
	nScale = 3;
	ptVelocity = POINT{ 0, 0 };
	bEnableMove = true;
	bIsInAir = false;
	nSpriteNum = 0;
	nextAir = false;
	bIsInScreen = false;

	nSpriteMax[(unsigned int)MONSTER::STATE::Idle] = 1;
	nSpriteMax[(unsigned int)MONSTER::STATE::Walk] = 6;
	nSpriteMax[(unsigned int)MONSTER::STATE::Jump] = 1;
	nSpriteMax[(unsigned int)MONSTER::STATE::Skill1] = 3;
	nSpriteMax[(unsigned int)MONSTER::STATE::Skill2] = 11;
	nSpriteMax[(unsigned int)MONSTER::STATE::Death] = 8;

	ptSpriteStart[(unsigned int)MONSTER::STATE::Idle] = POINT{ 0, 0 };
	ptSpriteStart[(unsigned int)MONSTER::STATE::Walk] = POINT{ 0, 21 };
	ptSpriteStart[(unsigned int)MONSTER::STATE::Jump] = POINT{ 0, 0 };
	ptSpriteStart[(unsigned int)MONSTER::STATE::Skill1] = POINT{ 0, 46 };
	ptSpriteStart[(unsigned int)MONSTER::STATE::Skill2] = POINT{ 0, 67 };
	ptSpriteStart[(unsigned int)MONSTER::STATE::Death] = POINT{ 0, 88 };

	nSpriteWidth[(unsigned int)MONSTER::STATE::Idle] = 16;
	nSpriteHeight[(unsigned int)MONSTER::STATE::Idle] = 20;
	nSpriteWidth[(unsigned int)MONSTER::STATE::Walk] = 17;
	nSpriteHeight[(unsigned int)MONSTER::STATE::Walk] = 24;
	nSpriteWidth[(unsigned int)MONSTER::STATE::Jump] = 16;
	nSpriteHeight[(unsigned int)MONSTER::STATE::Jump] = 20;
	nSpriteWidth[(unsigned int)MONSTER::STATE::Skill1] = 16;
	nSpriteHeight[(unsigned int)MONSTER::STATE::Skill1] = 20;
	nSpriteWidth[(unsigned int)MONSTER::STATE::Skill2] = 32;
	nSpriteHeight[(unsigned int)MONSTER::STATE::Skill2] = 20;
	nSpriteWidth[(unsigned int)MONSTER::STATE::Death] = 25;
	nSpriteHeight[(unsigned int)MONSTER::STATE::Death] = 20;

	ptCharCenter[(unsigned int)MONSTER::STATE::Idle] = POINT{ 8, 20 };
	ptCharCenter[(unsigned int)MONSTER::STATE::Walk] = POINT{ 8, 24 };
	ptCharCenter[(unsigned int)MONSTER::STATE::Jump] = POINT{ 8, 20 };
	ptCharCenter[(unsigned int)MONSTER::STATE::Skill1] = POINT{ 8, 20 };
	ptCharCenter[(unsigned int)MONSTER::STATE::Skill2] = POINT{ 16, 20 };
	ptCharCenter[(unsigned int)MONSTER::STATE::Death] = POINT{ 13, 20 };
}

void MONSTER::Release()
{
}

int MONSTER::getHP()
{
	return nHP;
}

void MONSTER::setHP(int _nHP)
{
	nHP = _nHP;
}

int MONSTER::getMaxHP()
{
	return nMaxHP;
}

void MONSTER::setMaxHP(int _nMaxHP)
{
	nMaxHP = _nMaxHP;
}

int MONSTER::getEXP()
{
	return nEXP;
}

void MONSTER::setEXP(int _nEXP)
{
	nEXP = _nEXP;
}

int MONSTER::getMaxEXP()
{
	return nMaxEXP;
}

void MONSTER::setMaxEXP(int _nMaxEXP)
{
	nMaxEXP = _nMaxEXP;
}

int MONSTER::getLevel()
{
	return nLevel;
}

void MONSTER::setLevel(int _nLevel)
{
	nLevel = _nLevel;
}

int MONSTER::getMoveSpeed()
{
	return nMoveSpeed;
}

void MONSTER::setMoveSpeed(int _nMoveSpeed)
{
	nMoveSpeed = _nMoveSpeed;
}

int MONSTER::getFacingDirection()
{
	return nFacingDirection;
}

void MONSTER::setFacingDirection(int _nFacingDirection)
{
	nFacingDirection = _nFacingDirection;
}

int MONSTER::getCollisionWidth()
{
	return nCollisionWidth;
}

void MONSTER::setCollisionWidth(int _nCollisionWidth)
{
	nCollisionWidth = _nCollisionWidth;
}

int MONSTER::getColiisionHeight()
{
	return nCollisionHeight;
}

void MONSTER::setCollisionHeight(int _nCollisionHeight)
{
	nCollisionHeight = _nCollisionHeight;
}

int MONSTER::getSpriteNum()
{
	return nSpriteNum;
}

void MONSTER::setSpriteNum(int _nSpriteNum)
{
	nSpriteNum = _nSpriteNum;
}

POINT* MONSTER::getPos()
{
	return &ptPos;
}

void MONSTER::setPos(POINT _ptPos)
{
	ptPos = _ptPos;
}

void MONSTER::DrawMonster(Graphics & graphics, Image* pSurvivorImg, POINT * ptCamera, Rect * clientRect, int nMagnification)
{
	if (bIsInScreen)
	{
		ImageAttributes imgAttr;
		imgAttr.SetColorKey(Color(240, 0, 240), Color(255, 10, 255));
		Pen pen(Color(240, 240, 240));

		nSpriteNum %= nSpriteMax[(unsigned int)eState];
		POINT ptPosToCamera{ (ptPos.x - ptCamera->x) * nMagnification + (clientRect->Width / 2),
			(ptPos.y - ptCamera->y) * nMagnification + (clientRect->Height / 2) };
		graphics.DrawImage(pSurvivorImg, Rect(ptPosToCamera.x - (ptCharCenter[(unsigned int)eState].x + (nFacingDirection == -1)) * nScale * nFacingDirection,
			ptPosToCamera.y - ptCharCenter[(unsigned int)eState].y * nScale,
			nSpriteWidth[(unsigned int)eState] * nScale * nFacingDirection, nSpriteHeight[(unsigned int)eState] * nScale),
			ptSpriteStart[(unsigned int)eState].x + nSpriteNum * (nSpriteWidth[(unsigned int)eState] + 1), ptSpriteStart[(unsigned int)eState].y,
			nSpriteWidth[(unsigned int)eState], nSpriteHeight[(unsigned int)eState], UnitPixel, &imgAttr);
		//graphics.DrawRectangle(&pen, Rect(ptPosToCamera.x - ptCharCenter[(unsigned int)eState].x * nScale, ptPosToCamera.y - ptCharCenter[(unsigned int)eState].y * nScale,
		//	nSpriteWidth[(unsigned int)eState] * nScale, nSpriteHeight[(unsigned int)eState] * nScale));
		//graphics.DrawRectangle(&pen, Rect(ptPosToCamera.x - (nCollisionWidth / 2) * nScale, ptPosToCamera.y - nCollisionHeight * nScale,
		//	nCollisionWidth * nScale, nCollisionHeight * nScale));
	}
}

void MONSTER::LevelUp()
{
	nHP += 10;
	nMaxHP += 10;
	nEXP = 0;
	nMaxEXP += 10;
	nLevel += 1;
}

void MONSTER::Update()
{
	if (bIsInAir && ptVelocity.y < nGravityMax)
	{
		printf_s("����������%d\n", bIsInAir);
		ptVelocity.y += nGravity;
	}
	monsterMove(ptVelocity.x, ptVelocity.y);
}

void MONSTER::UpdateFrame()
{
	nSpriteNum++;
	monsterDo();
}

void MONSTER::transitionState(STATE _eState)
{
	eState = _eState;
}

void MONSTER::monsterDo()
{
	switch (eState)
	{
	case MONSTER::STATE::Idle:
	{
	}
	break;
	case MONSTER::STATE::Walk:
	{
		//if (!(GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000))
		//{
		//	ptVelocity.x = 0;
		//	transitionState(MONSTER::STATE::Idle);
		//}
	}
	break;
	case MONSTER::STATE::Jump:
	{
		if (!bIsInAir)
		{
			ptVelocity.x = 0;
			ptVelocity.y = 0;
			transitionState(MONSTER::STATE::Idle);
		}
	}
	break;
	case MONSTER::STATE::Skill1:
	{
		if (!bIsInAir)
		{
			ptVelocity.x = 0;
		}
		if (nSpriteNum == nSpriteMax[(unsigned int)eState])
		{
			bEnableMove = true;
			if (bIsInAir)
			{
				transitionState(MONSTER::STATE::Jump);
			}
			else
			{
				transitionState(MONSTER::STATE::Idle);
			}
		}
	}
	break;
	case MONSTER::STATE::Skill2:
	{
		if (!bIsInAir)
		{
			ptVelocity.x = 0;
		}
		if (nSpriteNum == nSpriteMax[(unsigned int)eState])
		{
			bEnableMove = true;
			if (bIsInAir)
			{
				transitionState(MONSTER::STATE::Jump);
			}
			else
			{
				transitionState(MONSTER::STATE::Idle);
			}
		}
	}
	break;
	case MONSTER::STATE::Death:
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

void MONSTER::monsterMove(int nX, int nY)
{
	ptPos.x += nX;
	ptPos.y += nY;
}

void MONSTER::monsterIsInAir(vector<Rect>* vec_CollisionMap)
{
	int nCollisionRectNum = vec_CollisionMap->size();
	Rect survivorRect(ptPos.x - (nCollisionWidth / 2), ptPos.y - nCollisionHeight, nCollisionWidth, nCollisionHeight);
	nextAir = true;
	for (int nRectNum = 0; nRectNum < nCollisionRectNum; nRectNum++)
	{
		if (collisionRect(survivorRect, (*vec_CollisionMap)[nRectNum]))
		{
			// �浹 ����

			// ���̶� �ε��� ��
			// ���̶� �ε����� ���
			// 1. �ɾ�� �ε���
			// 2. �������� �ε���
			// 3. �����ϴٰ� �Ӹ��� �ε���

			// ���߿��� �ε��� y�� �ӵ����� ���� ��
			//

			if (!bIsInAir) {
				// �ɾ�ٴ� ��
				//printf_s("�ɾ�ٴѴ�. \n");
				if (survivorRect.GetBottom() == (*vec_CollisionMap)[nRectNum].GetTop()) {
					nextAir = false;
					continue;
				}
				if (ptVelocity.x > 0 && survivorRect.GetRight() > (*vec_CollisionMap)[nRectNum].GetLeft()) {
					ptPos.x = (*vec_CollisionMap)[nRectNum].GetLeft() - (nCollisionWidth / 2) * nScale;
					//printf_s("���� ���� �ε�����.\n", survivorRect.GetRight(), (*vec_CollisionMap)[nRectNum].GetLeft());
					return;
				}
				else if (ptVelocity.x < 0 && survivorRect.GetLeft() < (*vec_CollisionMap)[nRectNum].GetRight()) {
					ptPos.x = (*vec_CollisionMap)[nRectNum].GetRight() + (nCollisionWidth / 2 - 1) * nScale;
					//printf_s("���� ���� �ε�����.\n");
					return;
				}
				else {
					continue;
				}
			}
			else {
				//printf_s("���� �� ���� �浹. \n");
				// �Ÿ� = �ð�(������) * �ӵ�
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
					if (nX < 0)
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
		//printf_s("���� �Ⱥپ�����. \n");
		bIsInAir = true;
		return;
	}
}

void MONSTER::monsterIsInScreen(POINT * ptCamera, Rect * clientRect, int nMagnification)
{
	Rect monsterRect(ptPos.x - (nCollisionWidth / 2), ptPos.y - nCollisionHeight, nCollisionWidth, nCollisionHeight);
	if (collisionRect(Rect(ptCamera->x - clientRect->Width / (nMagnification * 2), ptCamera->y - clientRect->Height / (nMagnification * 2),
		clientRect->Width / nMagnification, clientRect->Height / nMagnification), monsterRect))
	{
		bIsInScreen = true;
	}
	else
	{
		bIsInScreen = false;
	}
}

bool MONSTER::collisionRect(const Rect & rect1, const Rect& rect2) const
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
