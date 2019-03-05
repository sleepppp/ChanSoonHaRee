#pragma once
#include "Enemy.h"
class BigSlime : public Enemy
{
private:
	enum SlimeStateType : int
	{
		Idle = 0, Create, Chasing, Attack, Attacked, Dead, End 
	};

private:
	typedef map<SlimeStateType, class Animation*>::iterator AnimationIter;
	map<SlimeStateType, class Animation*> _animationList;
	SlimeStateType _slimeType;

	class Animation* _mainAnimation;

private:

	class Image* _createSlimeImage;
	class Image* _SlimeMove;
	class Image* _SlimeAttack;

	//공격받을 사이즈 렉트
	RECT _attackedCollisionRc;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	void ChangeState(SlimeStateType state);
	void ChangeAnimation(SlimeStateType state);
	void UpdateState();
	void CreateAnimation();

	void SlimeCreateBigSlime();
	void SlimeChasingMove();
	void SlimeIdle();
	void SlimeAttack();
	RECT GetCollisionRect()const override { return _attackedCollisionRc; }
public:
	BigSlime(Vector2 pos);
	~BigSlime();
};

