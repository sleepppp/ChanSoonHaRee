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

	Image* _itemImg;
	Image* _itemShadowImg;

	int _moveCount;

	float _angle;
	float _speed;

public:
	MoveItem(string name, Vector2 position);
	~MoveItem();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;


	void SprayItemEnemy();	//���ʹ� ������ �Ѹ��� �Լ�
};

