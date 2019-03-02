#pragma once
#include "LoadingSceneBase.h"
class LoadingScene : public LoadingSceneBase
{
private:
	wstring  _loadingWString;
	float _frameCount;
public:
	LoadingScene();
	~LoadingScene();

	void Init()override; 
	void Release()override; 
	void Update()override; 
	void Render()override; 
};

