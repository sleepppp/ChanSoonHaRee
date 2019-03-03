#pragma once
#include "Enemy.h"
class Weeds :	public Enemy
{

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	Weeds(Vector2 pos);
	~Weeds();
};

