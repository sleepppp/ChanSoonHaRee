#pragma once
#include "GameObject.h"
class Enemy :	public GameObject
{
private:

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

public:
	Enemy();
	~Enemy();
};

