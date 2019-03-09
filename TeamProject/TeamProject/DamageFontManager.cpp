#include "stdafx.h"
#include "DamageFontManager.h"
#include "StringHelper.h"

SingletonCpp(DamageFontManager)

void DamageFontManager::Init()
{
}

void DamageFontManager::Release()
{
}

void DamageFontManager::Update()
{
	_position
}

void DamageFontManager::Render()
{
	//텍스트 렌더
	//_DXRenderer->RenderText(_position.x, _position.y, StringHelper::StringToWString(to_string(_damage)), RGB(225, 42, 25), _alpha, 25);
}

void DamageFontManager::ShowDamage(Vector2 position, int damage)
{
	//if()

	//x,y포지션
	_position = position;

	//데미지
	_damage = damage;
	



}

void DamageFontManager::MoveDamage()
{
	if (!ShowDamage == false) 
	{

	}
}
