#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
	//�������� Ÿ��.
	enum class MoveType
	{
		Top = 0, Left, Right, Bottom, End
	};

	enum class StateType
	{
		Chasing = 0, Attacked, attack
	};

private:
	int a;
	//���ʹ��� ���׾Ƹ� ������
	float _speed;		//�ӵ�
	float _angle;		//�ޱ�
	bool _isAttack;		//����
	bool _isAttacked;	//�ǰ�
	int _attackCount;	//���� �ð�
	int _demege;		//���ݷ�
	int _hp;			//ü��
	int _isAttackedCount;
	//���ʹ��� ���ݹ��� ������
	float _distance;
	RECT _attackRc;
	//���� ���� ��Ʈ
	RECT _attackTop;
	RECT _attackLeft;
	RECT _attackRight;
	RECT _attackBottom;
	//���� ���� ũ�� ��Ʈ
	Vector2 _sizeTop;
	Vector2 _sizeLeft;
	Vector2 _sizeRight;
	Vector2 _sizeBottom;
	//���� ��� Ʈ���޽�
	bool _isAttackTop;
	bool _isAttackLeft;
	bool _isAttackRight;
	bool _isAttackBottom;

	bool _isEnemyPlayerCollisiton;
	//���ʹ� ������� ����
	MoveType _move;
	StateType _state;
	//�ٸ� ����� Ŭ���� �ҷ�����
	class player* _player;

public:
	//������ �Լ�
	void Move();
	void Attack();
	void MoveType();
	void CardinalPointsAttack();
	void EnemyInit();
	void AttackRender();
	void Collision();
	void AttackedDemege(int damage);
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

public:
	Enemy();
	~Enemy();
};
