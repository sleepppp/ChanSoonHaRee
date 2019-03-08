#pragma once
#include "GameObject.h"
class Boss : public GameObject
{
private:
	//보스의 상태 종류 , 플레이어를 마주치기 전, 마주치고나서  깨어날때, 죽을때, 손떨구기, 주먹발사, 돌떨구기., 
	enum class StateType
	{
		Idle, Create,Dead, 
		Rock_Shoot_First, Rock_Shoot_Second, Rock_Shoot_Last,
		Hand_Shoot_First, Hand_Shoot_Second, Hand_Shoot_Last, 
		Fist_Shoot_First, Fist_Shoot_Second, Fist_Shoot_Last, 
		End
	};
	
private:
	//애니매이션 실행을 위한 반복자 이터레이터
	typedef map<StateType, class Animation*>::iterator  StateAnimationIter;
	//애니메이션을 담을 리스트
	map <StateType, class Animation*> _stateAnimationList;
	//이넘의 상태
	StateType _state;

	//애니매이션은 한가지 상태만을 가져야하기에 현재의 상태를 담아줄 상태값.
	class Animation* _mainAnimation;
private:
	//플레이어를 불러오자.
	class Player* _player;

	//이미지들도 만들어지면 넣어야 할것이고,

	int _hp;					//체력이 있어야 할 거고
	int _demage;				//플레이어를 공격해야하니까 데미지도 있을 것이고,
	float _speed;				//각 공격들은 속도를 가져야하니까 속도도 들어가겠지 뭐
	float _angle;				//각도를 계산해야하니까 앵글값도 있을 것이고,
	float _distance;			//플레이어가 일정거리 안에 들어서면 움직여야하니까 플레이어의 거리를 재기 위해서 디스턴스도 있어야 하고,
	
	Vector2 _rockPosition;		//돌들마다 충돌이 되어야 하고 각자의 좌표를 뿌려줘야하니까 얘들의 좌표를 주기위해서 좌표가있어야겠지?
	Vector2 _rockSize;			//돌들도 크기가 있을거 아녀 그럼 사이즈가잇어야겠지
	RECT _rockRc;				//좌표 있고 크기 있으면 그려줘야지
	
	Vector2 _fistPosition;		//플레이어의 렉트와 내 슬라임의 쬰쬬니가 충돌시켜야하니까 쬰쬬니의 선을 그려주고, 
	Vector2 _fistSize;			//쬰쪼니에 달린 주먹 크기도 있어야 할거 아녀
	RECT _fistRc;				//쬰쬬니에 달린 주먹의 렉트도 있어야 겠지?

	RECT _handRc;				//오른손주먹도 맞으면 아프니까 렉트가있어야 하고,
	RECT _attackedRc;			//공격을 맞기 위한 렉트가 있어야 하고,
	
public:
	void ChangeState(StateType state);
	void ChangeAnimation(StateType state);
	void CreateAnimation();

	float Distance(Vector2 position);
	float Angle(Vector2 position);
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

public:
	Boss();
	~Boss();
};

