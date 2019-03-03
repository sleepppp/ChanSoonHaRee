#pragma once
#include "GameObject.h"
class TestPlayer : public GameObject
{
	enum class State : int
	{
		LeftIdle = 0 ,RightIdle,UpIdle,DownIdle, 
		LeftRun,RightRun,UpRun,DownRun
	};
private:
	typedef map<State, class Animation*>::iterator AnimationIter;
private:
	class Image* _image;
	map<State, class Animation*> _animationList;

	State _state;
	class Animation* _mainAnimation;
	float _speed; 
public:
	TestPlayer();
	~TestPlayer();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
private:
	void Move(Vector2 direction);
	void ChangeAnimation(State state);
	void ChangeState(State state);
	void CreateAnimation();

	void IdleKeyInput();
};

