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
	class Image* _golemMove;		//�ȴ� �̹���
	class Image* _golemAttack;		//�����ϴ� �̹���

	//���� ī��Ʈ
	int _count;				//Ÿ�̹��� ���߱� ���� �־���� ��� ī��Ʈ
	int _moveCount;			//�̹����� �����̱� ���� ī��Ʈ
	int _attackCount;		//������ ���۰� ���� �˷��ֱ� ���� ī��Ʈ 
	int _attackImageCount;	//�������� ���� Ÿ�̹��� �ֱ����� ī��Ʈ
	int _attackedCount;		//�ǰݽ� �ڷ� �и��� Ÿ�̹��� ��� ���� ī��Ʈ

	bool _isAttack;			//���ݿ��θ� Ȯ���ϱ� ���� �Һ���
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