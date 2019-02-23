#pragma once
#include "GameObject.h"
class TestAnimation : public GameObject
{
private:
	//class Animation* _animation;
	class Image* _image;
	float _frameCount; 
	float _frameRate;
	int _frameY;
	int _frameX;
public:
	TestAnimation();
	~TestAnimation();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

};

