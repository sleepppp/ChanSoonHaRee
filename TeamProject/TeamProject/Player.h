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



	//플레이어 움직임을 위한 enum값
	enum class State
	{
		stand_L,
		stand_R,
		stand_U,
		stand_D,
		run_L,
		run_R,
		run_U,
		run_D,
		//rolling_L,
		end
	};

	State _state;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	RECT getPlayerCollisitionRc() { return _colliRc; }

	Player();
	~Player();
};

