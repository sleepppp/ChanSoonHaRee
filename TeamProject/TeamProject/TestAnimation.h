#pragma once
#include "GameObject.h"
class TestAnimation : public GameObject
{
private:
	class Animation* _animation;
public:
	TestAnimation();
	~TestAnimation();

	void Init()override; 
	void Release()override; 
	void Update()override;
	void Render()override;

	class Animation* GetAnimation()const { return this->_animation; }
};

