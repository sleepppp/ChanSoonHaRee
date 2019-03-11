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
		LeftSword2, RightSword2, UpSword2, DownSword2,
		LeftBow,RightBow,UpBow,DownBow,
		end
	};

private:
	//�ִϸ��̼��� ���� ���� �ݺ���
	typedef map<State, class Animation*>::iterator AnimationIter;
private:
	class Image* _imgMove;		//�÷��̾� �⺻ ������
	class Image* _imgAtkSword;	//�÷��̾� ���� ������ �̹���
	class Image* _imgAtkBow;	//�÷��̾� ���� Ȱ �̹���

	class UIWeaponAndBag* _UIWeaponSwap;

	class Animation* _mainAnimation;
	
	//vector <Arrow> _arrow;//ȭ�� Ŭ���� ����� ���� ����


	map<State, class Animation*> _animationList;	//���º� �ִϸ� �����ϱ� ���� �� ���
	State _state;
	
	RECT _collisionRect;	//�浹�� RECT
	RECT _swordRect;			//���ݿ� RECT
	RECT _shieldRect;		//���� RECT
	
	float _speed;
	
	int _currentHp;
	int _maxHp;
	int _damage;

	float _frameRun;
	float _frameIdle;
	float _frameBow;

	bool _isMoveStop;
	bool _isChangeSword;		//Į �̹����� ���ĵ� ���� ��ȯ�� bool��
	bool _isChangeBow;
	bool _isStandardMove;

	int _swordWidth;
	int _swordHeight;
	
	bool _isAttacked;
	bool _isChangeWeapon;
	bool _isTwice;
	bool _isEnemy;

	int _alpha;

	bool _isDelay;
	float _count;
	int _blink;

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
	//void IdleKeyInput();
	bool InterRee(RECT* moveRc, RECT* unMoveRc);

	
	//UI,�κ��丮 Ŭ������ �Ѱ��ֱ� ���� �Լ� 3��	
	int GetPlayerCurrentHp() { return _currentHp; }
	int GetPlayerMaxHp() { return _maxHp; }
	POINT GetPlayerIndex();

	RECT GetCollisionRect()const override {	return _collisionRect;}
	
	//���ʹ� Ŭ������ �Ѱ��ֱ� ���� �Լ�
	int GetPlayerDamage() { return _damage; }
	
	void AttackedDamage(int damage);
	void InventoryOnOff();
	//void AtkDelay();

	
	void AtkDelay2();
	//void BodyAttack();
	
	//���� enum�� ���� �Լ�
	State GetState() { return _state;}

};

class PlayerAni
{
public:
	PlayerAni();
	~PlayerAni();
};
