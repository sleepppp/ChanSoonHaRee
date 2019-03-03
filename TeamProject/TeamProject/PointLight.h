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

	GameColor GetColor()const { return this->_color; }
	float GetOriginRange()const { return this->_originRange; }
	float GetIntensity()const { return this->_intensity; }
};

