#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	RECT _colliRc;	//충돌판정용 네모
	RECT _weaponRc;	//공격(무기) 네모
	RECT _shieldRc;	//방패 네모

	class Image* _image;	//플레이어 이미지스프라이트
	float _frameCount;		//애니 프레임시간용
	float _frameIndexX;		//애니 프레임 가로
	float _frameIndexY;		//애니 프레임 세로
	float _speed;			//

	float _standRate;
	float _runRate;

	float _changeIndexX;
	bool _isRolling;


	//상하좌우 모션용 enum
	enum class StateMove
	{
		stand_L, stand_R, stand_U, stand_D,
		run_L, run_R, run_U, run_D,
		roll_L, roll_R, roll_U, roll_D,
		sword_L, sword_R, sword_U, sword_D,
		shield_L, shield_R, shield_U, shield_D,
		end
	};
	StateMove _stateMove;
		
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void Move(StateMove _move);	//상태값 변경 함수


	RECT getPlayerCollisitionRc() { return _colliRc; }	//전달용
	//void PlayerAtk();									//무기와 에너미 충돌 판정
														//에너미 무기와 내 몸 충돌 판정

	Player();
	~Player();
};

