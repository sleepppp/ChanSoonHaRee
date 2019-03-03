#pragma once
#include "GameObject.h"
class PointLight : public GameObject
{
protected:
	GameColor _color;
	float _originRange;
	float _intensity;
public:
	PointLight(Vector2 pos,float range, float intensity, GameColor color);
	~PointLight();

	void Update()override;
	void Render()override;

	GameColor GetColor()const { return this->_color; }
	float GetOriginRange()const { return this->_originRange; }
	float GetIntensity()const { return this->_intensity; }
};

