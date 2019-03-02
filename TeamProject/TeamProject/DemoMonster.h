#pragma once
#include "GameObject.h"
class DemoMonster : public GameObject
{
protected:
	enum class Direction
	{
		Left,Right,Top,Bottom
	};
protected:
	Direction _direction;
	RECT _renderRect;
	float _speed; 
	int _hp; 
	int _damage;
public:
	DemoMonster();
	~DemoMonster();

	virtual void Damage(int damage);
};

