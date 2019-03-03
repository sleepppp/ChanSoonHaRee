#pragma once
#include "Enemy.h"

class Golem : public Enemy
{
private:

	//공격 범위 렉트
	RECT		_attackTop;
	RECT		_attackLeft;
	RECT		_attackRight;
	RECT		_attackBottom;
	//공격 범위 크기 렉트
	Vector2		_sizeTop;
	Vector2		_sizeLeft;
	Vector2		_sizeRight;
	Vector2		_sizeBottom;
	//공격 장소 트루펄스
	bool		_isAttackTop;
	bool		_isAttackLeft;
	bool		_isAttackRight;
	bool		_isAttackBottom;

	//기본 움직이는것과 공격하는 것 이미지
	class Image* _golemMove;
	class Image* _golemAttack;

	//각종 카운트
	int _moveCount;
	int _attackCount;
	int _attackedCount;

	int _count;

	bool _isAttack;
public:
	void Move();
	void Attack();
	void AttackPosition();
	void AttackRender();
	void Collision();
	void ImageCount();

	void RectRender();
	void ImageRender();
public:
	void Init();
	void Release();
	void Update();
	void Render();

public:
	Golem();
	~Golem();
};