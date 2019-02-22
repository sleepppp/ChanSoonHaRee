#pragma once
#include "GameObject.h"
/***************************************************************************************
## Player ##
���� ������Ʈ�� ���
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

	void BulletFire();		//�Ѿ� �߻�
	void BulletMove();		//�Ѿ� �̵�
};

