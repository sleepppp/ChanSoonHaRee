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
	
	float _distance;	//공격 가능 범위
	int _attackCount;	//공격을 사작할 카운트 + 공격 이미지 돌릴 카운트


	//이넘 타입
	MoveType _move;		//기본 이동상태
	StateType _state;	//피격 상황

	class TestPlayer* _player;	//플레이어 클래스 가져오기
public:
	void EnemyMove();			//에너미의 움직임
	void EnemyAttack();			//에너미의 공격움직임
	void EnemyMoveType();		//에너미의 움직임 방향
	void AttactDistance();		//에너미의 공격 사거리.
public:
	TestEnemy(Vector2 position, Vector2 size, Pivot::Enum pivot, float speed);
	~TestEnemy();
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

};

