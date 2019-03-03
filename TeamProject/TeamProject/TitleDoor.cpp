#include "stdafx.h"
#include "TitleDoor.h"

#include "Image.h"
TitleDoor::TitleDoor(string key, Vector2 direction,Vector2 pos,Vector2 size)
	:GameObject("TitleDoor",pos,size,Pivot::LEFT_TOP),_direction(direction)
{
	_state = State::Close;
	_image = _ImageManager->FindImage(key);
	_delayTime = _moveRange = 0.f;
	_speed = 500.0f;

	this->AddCallbackMessage("Open", [this](TagMessage message) 
	{
		this->StateOpen(); 
	});
}

TitleDoor::~TitleDoor()
{
}

void TitleDoor::Update()
{
	GameObject::Update();

	switch (_state)
	{
	case TitleDoor::State::Close:
		break;
	case TitleDoor::State::OpenSlide0:
		_position.x += _direction.x * _speed * _TimeManager->DeltaTime();
		_moveRange += Math::Abs(_direction.x * _speed * _TimeManager->DeltaTime());
		this->UpdateMainRect();

		if (_moveRange >= 100.0f)
		{
			_state = State::OpenSlide1;
			_speed = 550.0f; 
			_moveRange = 0.f;
			_position.y = 0.f;
			this->UpdateMainRect();
		}
		break;
	case TitleDoor::State::OpenSlide1:
		_delayTime += _TimeManager->DeltaTime();
		if (_delayTime >= 0.2f)
		{
			_state = State::OpenSlide2;
		}
		break;
	case TitleDoor::State::OpenSlide2:
		_position.x += _direction.x * _speed * _TimeManager->DeltaTime();
		_moveRange += Math::Abs(_direction.x * _speed * _TimeManager->DeltaTime());
		this->UpdateMainRect();

		if (_moveRange >= 300.0f)
		{
			_state = State::Open;
			GameObject* flowObject = _ObjectManager->FindObject(ObjectType::Object, "TitleFlowObject");
			if (flowObject)
				flowObject->SendCallbackMessage(TagMessage("DoorOpened",1.0f));
			_position.y = 0.f;
			this->UpdateMainRect();
		}
		break;
	case TitleDoor::State::Open:
		break;
	default:
		break;
	}
}

void TitleDoor::Render()
{
	_image->SetSize(_size);
	_image->Render(CastingInt(_mainRect.left), CastingInt(_mainRect.top), Pivot::LEFT_TOP, false);
}
