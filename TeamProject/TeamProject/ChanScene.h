#pragma once
#include "SceneBase.h"
class ChanScene : public SceneBase
{
public:
	ChanScene();
	~ChanScene();

	void Init()override; 
	void Release()override; 
	void Update()override;
	void Render()override; 
};

