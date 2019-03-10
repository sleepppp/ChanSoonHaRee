#pragma once
#include "GameObject.h"

class testYap :	public GameObject
{
	class Image* _img;
	float _speed;
	float _soon;
	float _chan;
	float _hak;

	int _frameX;
	int _frameY;




public:
	testYap();
	~testYap();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
};

