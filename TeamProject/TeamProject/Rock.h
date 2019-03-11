#pragma once
#include "GameObject.h"
class Rock : public GameObject
{
private:
	class Image* _rock;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	Rock(Vector2 pos);
	~Rock();
};

