#pragma once
#include "GameObject.h"

/***************************************************************************************
## Player ##
게임 오브젝트를 상속
****************************************************************************************/

class Player : public GameObject
{
	float _speed;					//플레이어 속도값	
	
	Vector2 _playerBullet;			//플레이어가 쏘는 총알의 사이즈
	
	class Bullet* _bullet;			//총알 클래스



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

