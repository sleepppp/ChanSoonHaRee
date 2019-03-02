#include "stdafx.h"
#include "GameObject.h"

#include <functional>
#include <unordered_map>

/*************************************************************************
## GameObject ##
**************************************************************************/
GameObject::GameObject()
	:_name(""), _pivot(Pivot::CENTER),_position(0,0),_size(0,0),_isActive(true),_isLive(true)
{
	this->UpdateMainRect();
}
/*************************************************************************
## GameObject ##
@@ string name : ��ü �̸� 
@@ Vector2 pos : ��ü ��ǥ
@@ Vector2 size : ��ü ������ 
@@ Pivot::Enum pivot : ��ü �Ǻ� 
**************************************************************************/
GameObject::GameObject(string name, Vector2 pos, Vector2 size, Pivot::Enum pivot)
	:_name(name),_position(pos),_size(size),_pivot(pivot),_isActive(true),_isLive(true)
{
	this->UpdateMainRect();
}

/*************************************************************************
## ~GameObject ##
**************************************************************************/
GameObject::~GameObject()
{
	this->_callbackList.clear();
	this->_reserveMessageList.clear();
}

/*************************************************************************
## Release ##
**************************************************************************/
void GameObject::Release()
{
	_reserveMessageList.clear();
}
/*************************************************************************
## Update ##
���� �޼����� �ִٸ� ����ð��� ��ٰ� �ð��� �ٵǾ��ٸ� �ش� �޼����� �Լ��� ȣ��
**************************************************************************/
void GameObject::Update()
{
	float deltaTime = _TimeManager->DeltaTime();
	for (UINT i = 0; i < _reserveMessageList.size(); ++i)
	{
		//����� �޼����� ����ð��� deltaTime��ŭ ���ش�
		_reserveMessageList[i].delayTime -= deltaTime;
		//���� ����� �ð��� �ٵǾ��ٸ� 
		if (_reserveMessageList[i].delayTime <= 0.f)
		{
			//�ش� �޼����� �Լ��� ��������ش�. 
			this->SendCallbackMessage(_reserveMessageList[i]);
			_reserveMessageList.erase(_reserveMessageList.begin() + i--);
		}
	}
}
/*************************************************************************
## SendCallbackMessage ##
@@ TagMessage message : �ش� ��ü�� ���� �޼���
**************************************************************************/
void GameObject::SendCallbackMessage(const TagMessage message)
{
	//���� ������ Ÿ���� ���ٸ� 
	if (message.delayTime <= 0.0f)
	{ 
		//�ٷ� �ش� �޼����� �̸��� ���� �Լ��� ã�Ƽ� ��������ش�. 
		CallbackHashmapIter iter = _callbackList.find(message.name);
		if (iter != _callbackList.end())
		{
			iter->second(message);
		}
	}
	//���� �޼����� ������ Ÿ���� �ִٸ�
	else
	{
		//���� �޼�������Ʈ�� �־�д�. 
		//GameObject�� ������Ʈ���� ���� �޼����� �ð��� ��ٰ� �ð��� �ٵǾ��ٸ� ȣ��
		_reserveMessageList.push_back(message);
	}
}
/*************************************************************************
## AddCallbackMessage ##
�޼��� ��ſ� ����� �Լ��� �̸� ����Ѵ�. 
@@ string name : ����� �Լ��� �̸�
@@ function<void(TagMessage)> func : ����� �Լ� 
**************************************************************************/
void GameObject::AddCallbackMessage(const string name,const function<void(struct TagMessage)> func)
{
	if (_callbackList.find(name) == _callbackList.end())
	{
		_callbackList.insert(make_pair(name, func));
	}
}

/*************************************************************************
## SetPivot ##
@@ Pivot::Enum pivot : �Ǻ�
**************************************************************************/
void GameObject::SetPivot(const Pivot::Enum pivot)
{
	this->_pivot = pivot; 
	this->UpdateMainRect();
}
/*************************************************************************
## SetPosition ##
@@ Vector2 pos : �ٲ��� ��ǥ
**************************************************************************/
void GameObject::SetPosition(const Vector2 position)
{
	this->_position = position;
	this->UpdateMainRect();
}
/*************************************************************************
## SetSize ##
@@ Vector2 size : �ٲ��� ������
**************************************************************************/
void GameObject::SetSize(const Vector2 size)
{
	this->_size = size; 
	this->UpdateMainRect();
}
/*************************************************************************
## SetActive ##
Ȱ�����¸� �ٲ��ְ� Ȱ��,��Ȱ���ɶ��� ����Ǿ�� �� �Լ��� ȣ��
@@ bool b : Ȱ�� ���� 
**************************************************************************/
void GameObject::SetActive(const bool b)
{
	this->_isActive = b; 
	if (_isActive)
		this->Enable();
	else
		this->Disable();
}
/*************************************************************************
## UpdateMainRect ##
�Ǻ��� ���� ��Ʈ�� ������ �������ش�.
**************************************************************************/
void GameObject::UpdateMainRect()
{
	switch (_pivot)
	{
	case Pivot::LEFT_TOP:
		this->_mainRect = Figure::RectMake(_position, _size);
		break;
	case Pivot::CENTER:
		this->_mainRect = Figure::RectMakeCenter(_position, _size);
		break;
	case Pivot::BOTTOM:
		this->_mainRect = Figure::RectMakeBottom(_position, _size);
		break;
	default:
		break;
	}
}
