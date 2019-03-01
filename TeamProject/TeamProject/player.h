#pragma once
#include "GameObject.h"
class player :	public GameObject
{
private:
	float _speed;
public:
	void PlayerMove();
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	player();
	~player();
};

