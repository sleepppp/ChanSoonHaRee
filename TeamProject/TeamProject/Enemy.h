#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
protected:
	//움직임의 타입.
	enum class MoveType
	{
		Top = 0, Left, Right, Bottom, End
	};
	enum class StateType
	{
		Chasing = 0, attack
	};

protected:
	float _speed;			//속도
	float _distance;		//직선거리를 구하기 위한 변수
	float _angle;			//앵글
	float _attackedAngle;	//공격을 받았을 시에 튕겨져 나갈 방향.
	int _damage;			//공격력
	int _hp;				//체력
	RECT _renderRect;		//이미지를 위해서 만든 렉트
	float _count;

	bool _attacked;
	bool _attackedColor;
	//에너미 방향상태 변수
	MoveType _move;		//방향에 관련된 이넘을 불러오기 위한 함수

	StateType _state;	//상태와 관련된 이넘을 불러오기 위한 함수

	//다른 사람의 클래스 불러오기
	class Player* _player;

public:
	virtual void AttackedDemege(int damage);
	//렉트 생성을 위한 변수
	RECT UpdateRect(Vector2 position, Vector2 size, Pivot::Enum _pivot);
	//에너미 움직이는 타입.
	void EnemyMoveType();
	bool IntersectReaction(RECT* moveRect, RECT* unMoveRect);
	RECT GetCollisionRect()const override {return _renderRect;}
	void ObjectCollision();

	float Distance(Vector2 pos);
	float Angle(Vector2 angle);

public:
	virtual void Init();
	virtual void Release() {}
	virtual void Update() {}
	virtual void Render() {}


public:
	Enemy();
	~Enemy();
};
