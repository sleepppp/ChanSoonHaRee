#pragma once
#include "SceneBase.h"
class TestScene0 : public SceneBase
{
private:

public:
	TestScene0();
	~TestScene0();

	void Init()override;
	void Release()override; 
	void Update()override; 
	void Render()override;
};

