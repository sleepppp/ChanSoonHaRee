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
	class Image* _golemMove_Red;	//�ȴµ��� �ǰ��̹���
	class Image* _golemMove_white;	//�ȴµ��� �ǰ��̹���

	class Image* _golemAttack;		//�����ϴ� �̹���
	class Image* _golemAttack_Red;	//���ݵ��� �ǰ��̹���
	class Image* _golemAttack_White;//���ݵ��� �ǰ��̹�¢

	//���� ī��Ʈ
	float _countMove;				//Ÿ�̹��� ���߱� ���� �־���� ��� ī��Ʈ
	float _countAttack;				//���� Ÿ�̹��� ���߱� ���� �־���� ī��Ʈ
	int	 _moveCount;			//�̹����� �����̱� ���� ī��Ʈ
	int	 _attackCount;			//������ ���۰� ���� �˷��ֱ� ���� ī��Ʈ 
	int	 _attackedCount;		//�ǰݽ� �ڷ� �и��� Ÿ�̹��� ��� ���� ī��Ʈ

	bool _isStop;
	bool _isAttack;			//���ݿ��θ� Ȯ���ϱ� ���� �Һ���
public:
	//���ݽ����Ǹ��� ���ؼ� �������� �Լ�.
	void Attack();
	//����������� �������� �������ִ� �Լ�.
	void AttackPosition();
	//���ݷ�Ʈ�� �������ִ� �Լ�.
	void AttackRender();
	//���� �浹������ ���ִ� �Լ�.
	void Collision();
	//�ǰ������� ���ִ� �Լ�
	void AttackedCollision();
	//�̹����� ������ ���ؼ� ������ �Լ�.
	void ImageCount();

	void Move();
	void ObjectCollision();
	//��Ʈ�� �������ϱ����� ����� ���� �Լ�.
	void RectRender();
	//�̹����� �������ϱ����� ����� ���� �Լ�.
	void ImageRender();

	void InvenStop(bool stop);
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

public:
	Golem(Vector2 pos);
	~Golem();
};