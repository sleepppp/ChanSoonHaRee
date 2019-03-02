#include "stdafx.h"
#include "DemoMonster.h"


DemoMonster::DemoMonster()
{
}


DemoMonster::~DemoMonster()
{
}

void DemoMonster::Damage(int damage)
{
	this->_hp -= damage;
	if (_hp <= 0)
	{
		
	}
	else
	{

	}

}
