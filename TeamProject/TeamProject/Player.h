#pragma once
#include "GameObject.h"
/***************************************************************************************
## Player ##
게임 오브젝트를 상속
****************************************************************************************/
class Player : public GameObject
{
	float _speed;
public:
	Player();
	~Player();
	
	void Init()override; 
	void Release()override;
	void Update()override;
	void Render()override;

	void BulletFire();		//총알 발사
	void BulletMove();		//총알 이동
};

