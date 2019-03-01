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
	ItemState _itemState;		//아이템 상태 변수 선언 (enum)
	
	int _moveCount;				//무브 카운트

	float _angle;				//아이템 앵글 값
	float _speed;				//아이템 속도

public:
	Item();
	~Item();

	void Init();
	void Release();
	void Update();
	void Render();
};

