#pragma once
#include "GameObject.h"
class UIMoneyPoket : public GameObject
{
private:
	//�̹��� Ŭ���� ���� - �� �ָӴ�
	class Image* _moneyPoketIMG;
	


public:
	UIMoneyPoket();
	~UIMoneyPoket();

	void Init();
	void Release();
	void Update();
	void Render();
};

