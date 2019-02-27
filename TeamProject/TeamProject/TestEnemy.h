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
	
	Vector2 _attackPosition;
	Vector2 _attackSize;
	RECT _attackRc;



	//�̳� Ÿ��
	MoveType _move;		//�⺻ �̵�����
	StateType _state;	//�ǰ� ��Ȳ

	class TestPlayer* _player;
public:
	void EnemyMove();
	void EnemyAttack();
	void EnemyMoveType();
public:
	TestEnemy(Vector2 position, Vector2 size, Pivot::Enum pivot, float speed);
	~TestEnemy();
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

};

