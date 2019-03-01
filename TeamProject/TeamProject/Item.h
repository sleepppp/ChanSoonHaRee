#pragma once
#include "GameObject.h"

enum class ItemState
{
	Follow = 0,
	MoveInven,
	End
};

class Item : public GameObject
{
private:
	ItemState _itemState;		//������ ���� ���� ���� (enum)
	
	int _moveCount;				//���� ī��Ʈ

	float _angle;				//������ �ޱ� ��
	float _speed;				//������ �ӵ�

public:
	Item();
	~Item();

	void Init();
	void Release();
	void Update();
	void Render();
};

