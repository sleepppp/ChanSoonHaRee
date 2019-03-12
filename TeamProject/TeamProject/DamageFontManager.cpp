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
	//�ؽ�Ʈ ����
	for (UINT i = 0; i < _vDamageFont.size(); ++i) 
	{
		//�ؽ�Ʈ ����
		//(��Ʈ ������ x,y, ��Ʈ������:: �ش� �ε��� ������, ����, ����, ��Ʈ ũ��, ��µǴ� �ǹ�, ī�޶� ����, ��Ʈ ����)
		_DXRenderer->RenderText(_vDamageFont[i].position.x - 15, _vDamageFont[i].position.y - 90,
			StringHelper::StringToWString(to_string(_vDamageFont[i].damage)),
			RGB(25, 42, 225), _vDamageFont[i].alpha, 22, DWRITE_TEXT_ALIGNMENT_LEADING, true,L"Cooper Std");
	}

}

void DamageFontManager::ShowDamage(Vector2 position, int damage)
{
	//����ü ������ ��Ʈ
	DamageFont sDamageFont;

	//x,y������ ��
	sDamageFont.position = position;

	//������ ��
	sDamageFont.damage = damage;

	//���ǵ� ��
	sDamageFont.speed = 15.0f;

	//�ޱ� ��
	sDamageFont.angle = Math::PI / 2;

	//���� ��
	sDamageFont.alpha = 1.0f;

	//���� ������ ��Ʈ�� ��Ʈ ���� ���
	_vDamageFont.push_back(sDamageFont);
}

void DamageFontManager::MoveDamage()
{
	//�����ŭ for��
	for (UINT i = 0; i < _vDamageFont.size(); ++i)
	{	
		//������ 
		_vDamageFont.at(i).position.x += cosf(_vDamageFont.at(i).angle) * _vDamageFont.at(i).speed * _TimeManager->DeltaTime();
		_vDamageFont.at(i).position.y -= sinf(_vDamageFont.at(i).angle) * _vDamageFont.at(i).speed * _TimeManager->DeltaTime();

		//���� �� �ʴ� -0.9����
		_vDamageFont.at(i).alpha -= 0.9f * _TimeManager->DeltaTime();

		//���� ���� ���� 0���� ���ų� ������
		if (_vDamageFont.at(i).alpha <= 0.f) 
		{
			//�ش� �ε��� �����
			_vDamageFont.erase(_vDamageFont.begin() + i);
		}
	}

	
	
	
}
