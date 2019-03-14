#pragma once
#include "Enemy.h"
class BigSlime : public Enemy
{
private:
	enum class StateType
	{
		//기본 숨어서 대기하고있는 상태, 플레이어를 발견하고 생성되고 있는 상태, 플레이어를 추격하고 있는 상태, 플레이어를 공격하고 있는 상태, 죽는상태
		Idle, Create, Chasing_L, 
		Chasing_R, Attack_L, Attack_R, 
		Dead, End
	};
	struct Ani
	{
		class Image* _CreateImage;
		class Animation* _animation;
	};
private:
	typedef map <StateType, Ani*>::iterator _aniIter;
	map <StateType, Ani*> _aniList;

	StateType _state;
	Ani* _ani;

	RECT _attackRc;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	void ChangeState(StateType state);
	void ChangeAnimation(StateType state);
	void CreateAnimation();
	void UpdateState();
	void Move();

	void ChasingMove();
public:
	BigSlime(Vector2 pos);
	~BigSlime();
};

