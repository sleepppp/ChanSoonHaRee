#pragma once
#include "SceneBase.h"
class PlayerTestScene : public SceneBase
{
public:
	PlayerTestScene();
	~PlayerTestScene();

	void Init();
	void Release();
	void Update()override; 
	void Render()override; 
};

