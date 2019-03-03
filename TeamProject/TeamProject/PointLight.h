#pragma once
#include "GameObject.h"
class PointLight : public GameObject
{
private:
	class RectTransform* transform;
	GameColor color;
	float originRange;
	float intensity;
public:
	PointLight();
	~PointLight();

	void Update();
};

