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
		//LeftSword2, RightSword2, UpSword2, DownSword2,
		end
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
	class Image* _imgAtkSword;	//플레이어 공격 스워드1
	//class Image* _imgAtkSword2;	//플레이어 공격 스워드2

	map<State, class Animation*> _animationList;	//상태별 애니를 관리하기 위해 맵 사용

	State _state;
	class Animation* _mainAnimation;
	RECT _collisionRect;	//충돌용 RECT
	RECT _swordRect;			//공격용 RECT
	RECT _shieldRect;		//방어용 RECT
	float _speed;
	
	int _currentHp;
	int _maxHp;
	int _damage;

	float _frameRun;
	float _frameIdle;
	float _frameRoll;

	bool _isMoveStop;
	bool _isChangeImg;

	int _swordWidth;
	int _swordHeight;
	
	bool _isAttacked;
	bool _isChangeWeapon;

	bool _isDelay;
	int _count;
public:
	Player(Vector2 pos);
	~Player();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void EndAnimation();
	void Attack();
public:
	void Move(Vector2 direction);
	void ChangeAnimation(State state);
	void ChangeState(State state);
	void CreateAnimation();	
	void IdleKeyInput();
	bool InterRect(RECT* moveRc, RECT* unMoveRc);

	
	//UI,인벤토리 클래스에 넘겨주기 위한 함수 3개	
	int GetPlayerCurrentHp() { return _currentHp; }
	int GetPlayerMaxHp() { return _maxHp; }
	POINT GetPlayerIndex();

	RECT GetCollisionRect()const override {	return _collisionRect;}
	
	//에너미 클래스에 넘겨주기 위한 함수
	int GetPlayerDamage() { return _damage; }
	
	void AttackedDamage(int damage);
	void InventoryOnOff();
	void AtkDelay();

	void BodyAttack();


	//데미지값전달
	//에너미와 충돌
};
