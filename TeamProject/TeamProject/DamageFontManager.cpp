#include "stdafx.h"
#include "DamageFontManager.h"
#include "StringHelper.h"

SingletonCpp(DamageFontManager)

DamageFontManager::DamageFontManager() {}
DamageFontManager::~DamageFontManager() {}

void DamageFontManager::Init()
{
}

void DamageFontManager::Release()
{
}

void DamageFontManager::Update()
{
	MoveDamage();
}

void DamageFontManager::Render()
{
	//텍스트 렌더
	for (UINT i = 0; i < _vDamageFont.size(); ++i) 
	{
		_DXRenderer->RenderText(_vDamageFont.at(i).position.x, _vDamageFont.at(i).position.y, StringHelper::StringToWString(to_string(_vDamageFont.at(i).damage)), RGB(225, 42, 25), _vDamageFont.at(i).alpha, 25);
	}

}

void DamageFontManager::ShowDamage(Vector2 position, int damage)
{
	//구조체 데미지 폰트
	DamageFont sDamageFont;


	//x,y포지션
	sDamageFont.position = position;

	//데미지
	sDamageFont.damage = damage;

	sDamageFont.speed = 2.0f;

	sDamageFont.angle = Math::PI / 2;

	sDamageFont.alpha = 1.0f;

	//벡터 데미지 폰트에 폰트 정보 담기
	_vDamageFont.push_back(sDamageFont);
}

void DamageFontManager::MoveDamage()
{
	for (UINT i = 0; i < _vDamageFont.size(); ++i)
	{	
		//포지션 
		_vDamageFont.at(i).position.x += cosf(_vDamageFont.at(i).angle) * _vDamageFont.at(i).speed * _TimeManager->DeltaTime();
		_vDamageFont.at(i).position.y -= sinf(_vDamageFont.at(i).angle) * _vDamageFont.at(i).speed * _TimeManager->DeltaTime();

		_vDamageFont.at(i).alpha -= 0.8f * _TimeManager->DeltaTime();

		if (_vDamageFont.at(i).alpha <= 0.f) 
		{
			_vDamageFont.erase(_vDamageFont.begin() + i);
		}
	}

	
	
	
}
