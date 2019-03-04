#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	enum class State : int
	{
		LeftIdle = 0, RightIdle, UpIdle, DownIdle,
		LeftRun, RightRun, UpRun, DownRun,
		LeftRoll, RightRoll, UpRoll, DownRoll
	};

	struct TestBullet
	{
		Vector2 pos;
		Vector2 directrion;
		float speed;
		bool bFire;
	};

private:
	//애니메이션을 담을 맵의 반복자
	typedef map<State, class Animation*>::iterator AnimationIter;
private:
	class Image* _image;	//플레이어
	map<State, class Animation*> _animationList;	//상태별 애니를 관리하기 위해 맵 사용

	State _state;
	class Animation* _mainAnimation;
	RECT _collisionRect;
	float _speed;
	//Vector2 _speed;
	float _frameRun;
	float _frameIdle;
	float _frameRoll;



public:
	Player() {}
	~Player() {}

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;


	void EndAnimation();
private:
	void Move(Vector2 direction);
	void ChangeAnimation(State state);
	void ChangeState(State state);
	void CreateAnimation();

	void IdleKeyInput();
};
