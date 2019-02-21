#pragma once
#include "GameObject.h"
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

