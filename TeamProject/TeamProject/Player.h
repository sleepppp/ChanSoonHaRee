#pragma once
#include "GameObject.h"
/***************************************************************************************
## Player ##
���� ������Ʈ�� ���
****************************************************************************************/
class Player : public GameObject
{
public:
	Player();
	~Player();

	void Init()override; 
	void Release()override;
	void Update()override;
	void Render()override; 
};

