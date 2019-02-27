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
	float _speed;		//속도
	float _angle;		//앵글
	bool _isAttack;		//공격여부
	bool _isAttacked;	//피격여부
	
	Vector2 _attackPosition;
	Vector2 _attackSize;
	RECT _attackRc;



	//이넘 타입
	MoveType _move;		//기본 이동상태
	StateType _state;	//피격 상황

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

