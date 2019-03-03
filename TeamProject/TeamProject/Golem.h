#pragma once
#include "Enemy.h"

class Golem : public Enemy
{
private:

	//���� ���� ��Ʈ
	RECT		_attackTop;
	RECT		_attackLeft;
	RECT		_attackRight;
	RECT		_attackBottom;
	//���� ���� ũ�� ��Ʈ
	Vector2		_sizeTop;
	Vector2		_sizeLeft;
	Vector2		_sizeRight;
	Vector2		_sizeBottom;
	//���� ��� Ʈ���޽�
	bool		_isAttackTop;
	bool		_isAttackLeft;
	bool		_isAttackRight;
	bool		_isAttackBottom;

	//�⺻ �����̴°Ͱ� �����ϴ� �� �̹���
	class Image* _golemMove;
	class Image* _golemAttack;

	//���� ī��Ʈ
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