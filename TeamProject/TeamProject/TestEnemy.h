#pragma once
#include "GameObject.h"
class TestEnemy : public GameObject
{
	enum class StateType
	{
		Idle, Attack, Attacked, End
	};
	enum class MoveType
	{
		Back, Left, Rigth, Front, End
	};
	enum class AttackType
	{
		Back, Left, Rigth, Front, End
	};

private:
	float _speed;		//�ӵ�
	float _angle;		//�ޱ�
	bool _isAttack;		//���ݿ���
	bool _isAttacked;	//�ǰݿ���
	
	float _distance;	//���� ���� ����
	int _attackCount;	//������ ������ ī��Ʈ + ���� �̹��� ���� ī��Ʈ


	//�̳� Ÿ��
	MoveType _move;		//�⺻ �̵�����
	StateType _state;	//�ǰ� ��Ȳ

	class TestPlayer* _player;	//�÷��̾� Ŭ���� ��������
public:
	void EnemyMove();			//���ʹ��� ������
	void EnemyAttack();			//���ʹ��� ���ݿ�����
	void EnemyMoveType();		//���ʹ��� ������ ����
	void AttactDistance();		//���ʹ��� ���� ��Ÿ�.
public:
	TestEnemy(Vector2 position, Vector2 size, Pivot::Enum pivot, float speed);
	~TestEnemy();
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

};

