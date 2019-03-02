#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	class Image* _image;
	float _frameCount;
	float _frameIndexX;
	float _frameIndexY;
	float _speed;

	float _standRate;
	float _runRate;

	float _changeIndexX;
	bool _isRolling;

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

	Player();
	~Player();
};

