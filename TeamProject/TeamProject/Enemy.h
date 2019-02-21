#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();

	void Init()override; 
	void Release()override; 
	void Update()override; 
	void Render()override; 
};

