#pragma once
#include "GameObject.h"
class Enemy :	public GameObject
{
private:
	float _speed;
	bool _isLeft;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

public:
	Enemy(Vector2 position);
	~Enemy();
};

