#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	enum class State : int
	{
		LeftIdle = 0, RightIdle, UpIdle, DownIdle,
		LeftRun, RightRun, UpRun, DownRun,
		LeftRoll, RightRoll, UpRoll, DownRoll,
		LeftSword1, RightSword1, UpSword1, DownSword1,
		LeftSword2, RightSword2, UpSword2, DownSword2
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
	class Image* _imgMove;		//플레이어 기본 움직임
	class Image* _imgAtkSword1;	//플레이어 공격 스워드1
	class Image* _imgAtkSword2;	//플레이어 공격 스워드2

	map<State, class Animation*> _animationList;	//상태별 애니를 관리하기 위해 맵 사용

	State _state;
	class Animation* _mainAnimation;
	RECT _collisionRect;
	float _speed;
	
	int _currentHp;
	int _maxHp;

	float _frameRun;
	float _frameIdle;
	float _frameRoll;

	bool _moveStop;


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
	bool InterRect(RECT* moveRc, RECT* unMoveRc);

	//UI,인벤토리 클래스에 넘겨주기 위한 함수 3개	
	int GetPlayerCurrentHp() { return _currentHp; }
	int GetPlayerMaxHp() { return _maxHp; }
	POINT GetPlayerIndex();		//퉤 프레임XY
};

//에너미와 충돌