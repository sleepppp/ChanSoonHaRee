#pragma once
#include "Enemy.h"
class BigSlime : public Enemy
{
private:
	enum class StateType
	{
		//�⺻ ��� ����ϰ��ִ� ����, �÷��̾ �߰��ϰ� �����ǰ� �ִ� ����, �÷��̾ �߰��ϰ� �ִ� ����, �÷��̾ �����ϰ� �ִ� ����, �״»���
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
	class Image* _shadow;
	float shadowCount;
	RECT _attackRc;
	RECT _shadowRc;
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

