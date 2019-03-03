#pragma once
#include "SceneBase.h"
class TownScene : public SceneBase
{
private:

public:
	TownScene();
	~TownScene();

	void Init()override;
	void Release()override; 
	void Update()override; 
	void Render()override; 
};

