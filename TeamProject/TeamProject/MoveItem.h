#pragma once
#include "GameObject.h"
class MoveItem : public GameObject
{
	enum class ItemState
	{
		Follow = 0,
		MoveItem,
		Inven


	};

private:
	ItemState _itemState;	//������ ���� ���� ����

	Image* _itemBrenchImg;

	int _moveCount;

	float _angle;
	float _speed;
public:
	MoveItem();
	~MoveItem();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;



};

