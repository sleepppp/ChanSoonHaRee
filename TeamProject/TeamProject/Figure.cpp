#include "stdafx.h"
#include "Figure.h"

/*****************************************************************************
## CheckPointInRect ##
��Ʈ �ȿ� ���ִ��� �Ǵ� PtInRect�� ���� 
@@ RECT rc : ��Ʈ
@@ POINT pt : ����Ʈ 
******************************************************************************/
bool Figure::checkPointInRect(const RECT& rc, const POINT& pt)
{
	if ((rc.left <= pt.x && pt.x <= rc.right) && (rc.top <= pt.y && pt.y <= rc.bottom)) return true;
	return false;
}
/***********************************************************************
## CheckPointInRect ## 
��Ʈ �ȿ� ���� �ִ��� �Ǵ� 
@@ RECT rc : ��Ʈ
@@ int x : �� x��ǥ
@@ int y : �� y��ǥ
************************************************************************/
bool Figure::checkPointInRect(const RECT& rc, int x, int y)
{
	if ((rc.left <= x && x <= rc.right) && (rc.top <= y && y <= rc.bottom)) return true;
	return false;
}
/***********************************************************************
## CheckPointInRect ##
@@ MYRECT rc : �������� ��Ʈ ����ü
@@ float x : �� x
@@ float y : �� y 
************************************************************************/
bool Figure::checkPointInRect(const MYRECT& rc, float x, float y)
{
	if ((rc.left <= x && x <= rc.right) && (rc.top <= y && y <= rc.bottom)) return true;
	return false;
}
/***********************************************************************
## CheckPointInRect ##
@@ MYRECT rc : ��Ʈ
@ MYFLOATPOINT : ����Ʈ
************************************************************************/
bool Figure::checkPointInRect(const MYRECT& rc, const MYFLOATPOINT& pt)
{
	if ((rc.left <= pt.x && pt.x <= rc.right) && (rc.top <= pt.y && pt.y <= rc.bottom)) return true;
	return false;
}

/***********************************************************************
## CheckPointInCircle ##
���� ���ȿ� �ִ��� �Ǵ�
@@ float cx : �� �߽� X
@@ float cy : �� �߽� Y
@@ float cR : �� ������ 
@@ MYFLOATPOINT pt : ��
************************************************************************/
bool Figure::checkPointInCircle(float cX, float cY, float cR, const MYFLOATPOINT& pt)
{
	float deltaX = pt.x - cX;
	float deltaY = pt.y - cY;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radiusSquare = cR * cR;

	if (radiusSquare < distSquare) return false;

	return true;
}
/***********************************************************************
## CheckPointInCircle ## 
���� ���ȿ� �ִ��� �Ǵ� 
@@ float cx : �� �߽� X;
@@ float cy : �� �߽� Y;
@@ float cR : �� ������ 
@@ float x : �� X
@@ float y : �� Y
************************************************************************/
bool Figure::checkPointInCircle(float cX, float cY, float cR, float x, float y)
{
	float deltaX = x - cX;
	float deltaY = y - cY;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radiusSquare = cR * cR;

	if (radiusSquare < distSquare) return false;

	return true;
}
/***********************************************************************
## CheckPointInCircle ##
�ּ� �ޱ� ������ . . . ������� ������ ���� �Ʒ��� ���� �˰���???
************************************************************************/
bool Figure::checkPointInCircle(const MYCIRCLE& rc, float x, float y)
{
	float deltaX = x - rc.x;
	float deltaY = y - rc.y;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radiusSquare = rc.r * rc.r;

	if (radiusSquare < distSquare) return false;

	return true;
}

bool Figure::checkPointInCircle(const MYCIRCLE& rc, const MYFLOATPOINT& pt)
{
	float deltaX = pt.x - rc.x;
	float deltaY = pt.y - rc.y;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radiusSquare = rc.r * rc.r;

	if (radiusSquare < distSquare) return false;

	return true;
}

bool Figure::isCollision(const MYRECT& rc1, const MYRECT& rc2)
{
	if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
		(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;

	return false;
}

bool Figure::isCollision(const RECT& rc1, const RECT& rc2)
{
	if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
		(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;

	return false;
}


bool Figure::isCollision(const MYCIRCLE& cir1, const MYCIRCLE& cir2)
{
	float deltaX = cir2.x - cir1.x;
	float deltaY = cir2.y - cir1.y;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radius = cir1.r + cir2.r;
	float radiusSquare = radius * radius;

	if (radiusSquare < distSquare) return false;

	return true;
}

bool Figure::isCollision(const MYCIRCLE& cir1, const RECT& rc)
{
	int centerX = FLOAT_TO_INT(cir1.x);
	int centerY = FLOAT_TO_INT(cir1.y);
	int radius = FLOAT_TO_INT(cir1.r);

	//�簢�� ���� �ȿ� ���� �߽��� �ִٸ�
	if ((rc.left <= centerX && centerX <= rc.right) ||
		(rc.top <= centerY && centerY <= rc.bottom))
	{
		//�簢���� �����ϴ� ���� ���� �簢�� ���� ����
		RECT exRect;
		exRect.left = rc.left - radius;
		exRect.right = rc.right + radius;
		exRect.top = rc.top - radius;
		exRect.bottom = rc.bottom + radius;
		//�� �簢�� �����ȿ� ���� �߽��� �ִٸ� �浹�ߴٴ� �� 
		if ((exRect.left <= centerX && centerX <= exRect.right) &&
			(exRect.top <= centerY && centerY <= exRect.bottom))
		{
			return true;
		}
	}
	//�簢�� ���� �ۿ� ���� �߽��� �ִٸ�
	else
	{
		//4�������� ���� ������ �浹�� �ǽ��Ѵ�.
		if (checkPointInCircle(cir1, (float)rc.left, (float)rc.top)) return true;
		if (checkPointInCircle(cir1, (float)rc.right, (float)rc.top)) return true;
		if (checkPointInCircle(cir1, (float)rc.left, (float)rc.bottom)) return true;
		if (checkPointInCircle(cir1, (float)rc.right, (float)rc.bottom)) return true;
	}

	return false;
}

bool Figure::isCollision(const MYCIRCLE& cir, const MYRECT& rc)
{
	int centerX = FLOAT_TO_INT(cir.x);
	int centerY = FLOAT_TO_INT(cir.y);
	int radius = FLOAT_TO_INT(cir.r);

	if ((rc.left <= centerX && centerX <= rc.right) ||
		(rc.top <= centerY && centerY <= rc.bottom))
	{
		RECT exRect;
		exRect.left =(LONG)( rc.left - radius);
		exRect.right = (LONG)(rc.right + radius);
		exRect.top = (LONG)(rc.top - radius);
		exRect.bottom = (LONG)(rc.bottom + radius);

		if ((exRect.left <= centerX && centerX <= exRect.right) &&
			(exRect.top <= centerY && centerY <= exRect.bottom))
		{
			return true;
		}
	}
	else
	{
		if (checkPointInCircle(cir, (float)rc.left, (float)rc.top)) return true;
		if (checkPointInCircle(cir, (float)rc.right, (float)rc.top)) return true;
		if (checkPointInCircle(cir, (float)rc.left, (float)rc.bottom)) return true;
		if (checkPointInCircle(cir, (float)rc.right, (float)rc.bottom)) return true;
	}

	return false;
}


bool Figure::isCollisionReaction(const RECT& rcHold, RECT& rcMove)
{
	RECT rcInter;

	if (!IntersectRect(&rcInter, &rcHold, &rcMove)) return false;

	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	if (interW > interH)
	{
		//��
		if (rcInter.top == rcHold.top)
		{
			OffsetRect(&rcMove, 0, -interH);
		}
		//�Ʒ�
		else if (rcInter.bottom == rcHold.bottom)
		{
			OffsetRect(&rcMove, 0, interH);
		}
	}
	else
	{
		if (rcInter.left == rcHold.left)
		{
			OffsetRect(&rcMove, -interW, 0);
		}
		else if (rcInter.right == rcHold.right)
		{
			OffsetRect(&rcMove, interW, 0);
		}
	}

	return true;
}

bool Figure::isCollisionReaction(const MYRECT& mrcHold, MYRECT& mrcMove)
{
	RECT rcHold;
	rcHold.left = FLOAT_TO_INT(mrcHold.left);
	rcHold.top = FLOAT_TO_INT(mrcHold.top);
	rcHold.right = FLOAT_TO_INT(mrcHold.right);
	rcHold.bottom = FLOAT_TO_INT(mrcHold.bottom);

	RECT rcMove;
	rcMove.left = FLOAT_TO_INT(mrcMove.left);
	rcMove.top = FLOAT_TO_INT(mrcMove.top);
	rcMove.right = FLOAT_TO_INT(mrcMove.right);
	rcMove.bottom = FLOAT_TO_INT(mrcMove.bottom);

	RECT rcInter;
	if (!IntersectRect(&rcInter, &rcHold, &rcMove)) return false;

	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	if (interW > interH)
	{
		if (rcInter.top == rcHold.top)
		{
			OffsetRect(&rcMove, 0, -interH);
		}
		else if (rcInter.bottom == rcHold.bottom)
		{
			OffsetRect(&rcMove, 0, interH);
		}
	}
	else
	{
		if (rcInter.left == rcHold.left)
		{
			OffsetRect(&rcMove, -interW, 0);
		}
		else if (rcInter.right == rcHold.right)
		{
			OffsetRect(&rcMove, interW, 0);
		}
	}

	mrcMove.left = static_cast<float>(rcMove.left);
	mrcMove.top = static_cast<float>(rcMove.top);
	mrcMove.right = static_cast<float>(rcMove.right);
	mrcMove.bottom = static_cast<float>(rcMove.bottom);


	return true;
}

bool Figure::isCollisionReaction(const MYCIRCLE& cirHold, MYCIRCLE& cirMove)
{
	float deltaX = cirMove.x - cirHold.x;
	float deltaY = cirMove.y - cirHold.y;
	float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);

	float radius = cirHold.r + cirMove.r;

	if (distance < radius)
	{
		float angle = Math::GetAngle(cirHold.x, cirHold.y, cirMove.x, cirMove.y);

		float moveDelta = radius - distance;
		float moveX = cosf(angle) * moveDelta;
		float moveY = -sinf(angle) * moveDelta;

		cirMove.Move(moveX, moveY);

		return true;
	}

	return false;
}


