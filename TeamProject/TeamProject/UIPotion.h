#pragma once
#include "GameObject.h"
class UIPotion : public GameObject
{
private:
	class Image* _uiPotionIMG;		//���� �̹���

public:
	UIPotion();
	~UIPotion();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

};

