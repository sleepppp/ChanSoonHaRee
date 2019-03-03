#pragma once
#include "Enemy.h"

class Golem : public Enemy
{
private:

	//공격 범위 렉트
	RECT		_attackTop;
	RECT		_attackLeft;
	RECT		_attackRight;
	RECT		_attackBottom;

	//공격 범위 크기
	Vector2		_sizeTop;
	Vector2		_sizeLeft;
	Vector2		_sizeRight;
	Vector2		_sizeBottom;

	//공격 범의 좌표
	Vector2 _positionLeft;
	Vector2 _positionRight;
	Vector2 _positionTop;
	Vector2 _positionBottom;

	//공격 장소 트루펄스
	bool		_isAttackTop;
	bool		_isAttackLeft;
	bool		_isAttackRight;
	bool		_isAttackBottom;

	//기본 움직이는것과 공격하는 것 이미지
	class Image* _golemMove;		//걷는 이미지
	class Image* _golemAttack;		//공격하는 이미지

	//각종 카운트
	float _countMove;				//타이밍을 맞추기 위해 넣어놓은 상시 카운트
	float _countAttack;				//공격 타이밍을 맞추기 위래 넣어놓은 카운트
	int	 _moveCount;			//이미지를 움직이기 위한 카운트
	int	 _attackCount;			//공격의 시작과 끝을 알려주기 위한 카운트 
	int	 _attackedCount;		//피격시 뒤로 밀리는 타이밍을 재기 위한 카운트

	bool _isAttack;			//공격여부를 확인하기 위한 불변수
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