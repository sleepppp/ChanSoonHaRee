#pragma once
#include "GameObject.h"
class UIWeaponAndBag : public GameObject
{
private:
	class Image* _uIWeaponSwapIMG;			//���� ���� �̹���
	class Image* _uIBagIMG;					//���� �̹��� 

	class Animation* _uIswapAnimation;		//���� ���� �ִϸ��̼� ����

	bool _isSwap;							//���� ���� bool

	int _swapCount;							//���� ī��Ʈ


public:
	UIWeaponAndBag();
	~UIWeaponAndBag();

	void Init();
	void Release();
	void Update();
	void Render();
};

