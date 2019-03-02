#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
	//움직임의 타입.
	enum class MoveType
	{
		Top = 0, Left, Right, Bottom, End
	};

	enum class StateType
	{
		Chasing = 0, Attacked, attack
	};

private:
	//골렘의 기본 움직임//골램의 공격 움직임
	class Image* _golemTopMove;			//47개
	class Image* _golemLeftMove;
	class Image* _golemRightMove;
	class Image* _golemBottomMove;
	
	class Image* _golemTopAttack;		//13개
	class Image* _golemLeftAttack;
	class Image* _golemRightAttack;
	class Image* _golemBottomAttack;

	int _golemTopMoveCount;
	int _golemLeftMoveCount;
	int _golemRightMoveCount;
	int _golemBottomMoveCount;

	int _golemTopAttackCount;
	int _golemLeftAttackCount;
	int _golemRightAttackCount;
	int _golemBottomAttackCount;


	//에너미의 몸뚱아리 변수들
	float _speed;		//속도
	float _angle;		//앵글
	bool _isAttack;		//공격
	bool _isAttacked;	//피격
	int _attackCount;	//공격 시간
	int _demege;		//공격력
	int _hp;			//체력
	int _isAttackedCount;
	int _count;
	//에너미의 공격범위 변수들
	float _distance;
	RECT _attackRc;
	//공격 범위 렉트
	RECT _attackTop;
	RECT _attackLeft;
	RECT _attackRight;
	RECT _attackBottom;
	//공격 범위 크기 렉트
	Vector2 _sizeTop;
	Vector2 _sizeLeft;
	Vector2 _sizeRight;
	Vector2 _sizeBottom;
	//공격 장소 트루펄스
	bool _isAttackTop;
	bool _isAttackLeft;
	bool _isAttackRight;
	bool _isAttackBottom;

	bool _isEnemyPlayerCollisiton;
	//에너미 방향상태 변수
	MoveType _move;
	StateType _state;
	//다른 사람의 클래스 불러오기
	class Player* _player;

public:
	//움직임 함수
	void GolemImageInit();
	void GolemImageCount();
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
