#pragma once
#include "GameObject.h"
class Bullet :	public GameObject
{
	vector <RECT> _bullet;
	_fire;
	_isCameraOut;

public:
	Bullet();
	~Bullet();


};

//new 처리로 한발씩 불렛