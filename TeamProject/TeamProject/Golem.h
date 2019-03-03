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

	//���� ���� ũ��
	Vector2		_sizeTop;
	Vector2		_sizeLeft;
	Vector2		_sizeRight;
	Vector2		_sizeBottom;

	//���� ���� ��ǥ
	Vector2 _positionLeft;
	Vector2 _positionRight;
	Vector2 _positionTop;
	Vector2 _positionBottom;

	//���� ��� Ʈ���޽�
	bool		_isAttackTop;
	bool		_isAttackLeft;
	bool		_isAttackRight;
	bool		_isAttackBottom;

	//�⺻ �����̴°Ͱ� �����ϴ� �� �̹���
	class Image* _golemMove;		//�ȴ� �̹���
	class Image* _golemAttack;		//�����ϴ� �̹���

	//���� ī��Ʈ
	float _countMove;				//Ÿ�̹��� ���߱� ���� �־���� ��� ī��Ʈ
	float _countAttack;				//���� Ÿ�̹��� ���߱� ���� �־���� ī��Ʈ
	int	 _moveCount;			//�̹����� �����̱� ���� ī��Ʈ
	int	 _attackCount;			//������ ���۰� ���� �˷��ֱ� ���� ī��Ʈ 
	int	 _attackedCount;		//�ǰݽ� �ڷ� �и��� Ÿ�̹��� ��� ���� ī��Ʈ

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
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

public:
	Golem();
	~Golem();
};