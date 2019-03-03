#pragma once
#include "GameObject.h"
class TownObject : public GameObject
{
	class Image* _image;
public:
	TownObject(string imageKey, Vector2 pos);
	~TownObject();

	void Init()override; 
	void Release()override; 
	void Render()override; 
};

