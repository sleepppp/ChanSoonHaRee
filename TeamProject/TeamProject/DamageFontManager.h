#pragma once
class DamageFontManager
{

	SingletonHeader(DamageFontManager)
public:
	DamageFontManager();
	~DamageFontManager();

	void Init();
	void Release();
	void Update();
	void Render();
};

#define _DamageFontManager DamageFontManager::Get()

