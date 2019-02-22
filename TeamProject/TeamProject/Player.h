#pragma once
#include "GameObject.h"

/***************************************************************************************
## Player ##
���� ������Ʈ�� ���
****************************************************************************************/

class Player : public GameObject
{
	class Bullet* _bullet;			//�Ѿ� Ŭ����

	float _speed;					//�÷��̾� �ӵ���		
	Vector2 _playerBullet;			//�÷��̾ ��� �Ѿ��� ������(x,y)		

public:
	Player();
	~Player();
	
	void Init()override; 
	void Release()override;
	void Update()override;
	void Render()override;

	void Collision();
};

