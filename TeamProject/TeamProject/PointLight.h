#pragma once
#include "GameObject.h"
class PointLight : public GameObject
{
	GameColor _color;
	float _originRange;
	float _intensity;
public:
	PointLight();
	~PointLight();

	void Update();
};
