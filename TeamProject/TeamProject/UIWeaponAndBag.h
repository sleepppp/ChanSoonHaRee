#pragma once
#include "GameObject.h"
class UIWeaponAndBag : public GameObject
{
private:
	class Image* _uIWeaponSwapIMG;
	class Image* _uIBagIMG;

	int _FrameX;
	int _FrameY;


public:
	UIWeaponAndBag();
	~UIWeaponAndBag();

	void Init();
	void Release();
	void Update();
	void Render();
};

