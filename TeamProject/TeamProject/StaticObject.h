#pragma once
#include "GameObject.h"
class StaticObject : public GameObject
{
	class Image* _image;
	float _angle;
public:
	StaticObject(string imageKey, Vector2 pos,float angle = 0.f);
	~StaticObject();

	void Release()override; 
	void Render()override; 
};

