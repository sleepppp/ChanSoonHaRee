#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	class Image* _image;	//플레이어 이미지스프라이트
	float _frameCount;		//애니 프레임시간용
	float _frameIndexX;		//애니 프레임 가로
	float _frameIndexY;		//애니 프레임 세로
	float _speed;			//

	float _standRate;
	float _runRate;

	float _changeIndexX;
	bool _isRolling;

	RECT _colliRc;	//충돌판정용 네모



	//상하좌우 모션용 enum
	enum class StateMove
	{
		stand_L, stand_R, stand_U, stand_D,
		run_L, run_R, run_U, run_D,
		end
	};
	StateMove _stateMove;

	//구르기 공격하기 모션용 enum 
	//0301:검,방패만 추가함
	enum class StateAction
	{
		roll_L, roll_R, roll_U, roll_D,
		sword_L, sword_R, sword_U, sword_D,
		shield_L, shield_R, shield_U, shield_D,
		end
	};
	StateAction _stateAction;
	
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void State(StateMove stateMove);	//상태값 변경 함수


	RECT getPlayerCollisitionRc() { return _colliRc; }	//전달용




	Player();
	~Player();
};

