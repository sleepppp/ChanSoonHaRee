#pragma once
#include "SceneBase.h"
class TestScene1 : public SceneBase
{

public:
	TestScene1();
	~TestScene1();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
};

