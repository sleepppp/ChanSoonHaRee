#include "stdafx.h"
#include "LoadingScene.h"

#include "Loading.h"
LoadingScene::LoadingScene()
	:_loadingWString(L"로딩중"), _frameCount(0.f)
{

}


LoadingScene::~LoadingScene()
{
	
}

void LoadingScene::Init()
{
	if (_loading)
		_loading->Start();
}

void LoadingScene::Release()
{
	SafeDelete(_loading);
}

void LoadingScene::Update()
{
	_frameCount += _TimeManager->DeltaTime();
	if (_frameCount >= 1.0f)
	{
		while (_frameCount >= 1.0f)
		{
			_frameCount -= 1.0f;
		}
		if (_loadingWString.length() <= 6)
		{
			_loadingWString += L".";
		}
		else
		{
			_loadingWString = L"로딩중";
		}
	}

	if (_loading->GetIsLoadEnd() == true)
	{
		_SceneManager->LoadScene(_nextSceneName, false);
	}
}

void LoadingScene::Render()
{
	_DXRenderer->FillRectangle(Figure::RectMake(0, 0, WinSizeX, WinSizeY));

	_DXRenderer->RenderText(WinSizeX / 2, WinSizeY/2 + 200, _loadingWString, 30, DefaultBrush::white, DWRITE_TEXT_ALIGNMENT_LEADING);
}
