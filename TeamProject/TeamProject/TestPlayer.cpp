#include "stdafx.h"
#include "TestPlayer.h"

#include "TestEenemy.h"
#include "TextFile.h"
TestPlayer::TestPlayer()
{
}


TestPlayer::~TestPlayer()
{
}

void TestPlayer::Init()
{
	this->_name = "TestPlayer";
	this->_pivot = Pivot::CENTER;
	this->_position = Vector2(WinSizeX / 2, WinSizeY/2);
	this->_size = Vector2(50, 50);
	this->UpdateRect();
	_isAttackActive = false;
	_attackTime = 0.f;
	_attackActiveTime = 0.5f;
}

void TestPlayer::Release()
{
}

void TestPlayer::Update()
{
	if (_isAttackActive == false)
	{
		if (_Input->GetKey('A'))
		{
			this->_position.x -= 200.0f * _Time->DeltaTime();
			this->_direction = Vector2(-1, 0);
			this->UpdateRect();
		}
		if (_Input->GetKey('D'))
		{
			this->_position.x += 200.0f * _Time->DeltaTime();
			this->_direction = Vector2(1, 0);
			this->UpdateRect();
		}
		if (_Input->GetKey('W'))
		{
			this->_position.y -= 200.0f * _Time->DeltaTime();
			this->_direction = Vector2(0, -1);
			this->UpdateRect();
		}
		if (_Input->GetKey('S'))
		{
			this->_position.y += 200.0f * _Time->DeltaTime();
			this->_direction = Vector2(0, 1);
			this->UpdateRect();
		}

		if (_Input->GetKeyDown(VK_SPACE))
		{
			_isAttackActive = true;
			_attackRc = Figure::RectMakeCenter(_position.x + _direction.x * 50, _position.y + _direction.y * 50, 50, 50);
		}
	}
	if (_isAttackActive)
	{
		vector<GameObject*> objectList = _ObjectManager->FindObjects(ObjectType::Object, "TestEnemy");

		for (UINT i = 0; i < objectList.size(); ++i)
		{
			RECT temp;
			if (IntersectRect(&temp, &_attackRc, &objectList[i]->GetRect()))
			{
				((TestEenemy*)objectList[i])->Damage(0);
				_attackTime = _attackActiveTime;
			}
		}

		_attackTime += _Time->DeltaTime();
		if (_attackTime >= _attackActiveTime)
		{
			_attackTime = 0.f;
			_isAttackActive = false;
		}
	}
	
}

void TestPlayer::Render()
{
	_DXRenderer->FillRectangle(_rc, DefaultBrush::blue, false);
	if(_isAttackActive)
		_DXRenderer->DrawRectangle(_attackRc, DefaultBrush::green, false,3.0f);

	ImGui::Begin("TestPlayer");
	{
		if (ImGui::Button("Save"))
			this->SaveData();
		if (ImGui::Button("Load"))
			this->LoadData();
	}
	ImGui::End();
}

void TestPlayer::SaveData()
{	
	TextWriter* w = new TextWriter;
	if (w->Open("TestPlayer.txt"))
	{
		w->Float(_position.x);
		w->Float(_position.y);
		w->EndLine();

		w->Close();
	}
	SafeDelete(w);
	
}

void TestPlayer::LoadData()
{
	TextReader* r = new TextReader;
	if (r->Open("TestPlayer.txt"))
	{
		_position.x = r->Float();
		_position.y = r->Float();
		
		this->UpdateRect();

		r->Close();
	}
	SafeDelete(r);
}
