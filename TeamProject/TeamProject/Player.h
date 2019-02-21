#pragma once
#include "GameObject.h"
/***************************************************************************************
## Player ##
게임 오브젝트를 상속
****************************************************************************************/
class Player : public GameObject
{
private:
	float speed; 
public:
	Player();
	~Player();

	void Init()override; 
	void Release()override;
	void Update()override;
	void Render()override; 

	void Move(Vector2 moveValue);
};

