#include "stdafx.h"
#include "GameObject.h"

//RectMake,RectMakeCenter��� ���� �ڵ忡�� �ִ� commonMacroFunction.h�� ���� ������ �Ѵ�. 
//���� Figure::RectMake ���� �ڵ带 ��� ġ�� �����ٸ� �ش� cpp���� 
//�Ʒ��� ���� using namespace Figure�� ���ְ� �Ǹ� ��ó�� �ٷ� RectMake�Լ��� ȣ���� �� �ְԵȴ�. 
using namespace Figure;

/********************************************************************************************
## GameObject ##
������ 

��� �̴ϼȶ�����~
���ӿ�����Ʈ�� �Ҵ� �� �� �������(Ŭ���� ����)���� �����ڵ� �Բ� ȣ�����ֱ� ������ �̷������� 
�⺻���� �ʱ�ȭ ���ָ� �� ������. 
**********************************************************************************************/
GameObject::GameObject()
	:_pivot(Pivot::LEFT_TOP),_position(0.f,0.f),_size(0.f,0.f),_isActive(true),_isLive(true)
{
	//�⺻������ ��Ʈ ���� 
	this->UpdateRect();
}

/***************************************************************************************
## ~GameObject ##
�Ҹ���
****************************************************************************************/
GameObject::~GameObject()
{
}
/***************************************************************************************
## SetPosition ## 
@@ Vector2 pos : ������ ��ǥ �� 

��ǥ�� ���� ������ ������ ��Ʈ�� �����ض�
****************************************************************************************/
void GameObject::SetPosition(Vector2 pos)
{
	this->_position = pos;
	this->UpdateRect();
}
/***************************************************************************************
## SetSize ## 
@@ Vector2 size : ������ ������ �� 

������ ���� ������ ������ ��Ʈ�� �����ض� 
****************************************************************************************/
void GameObject::SetSize(Vector2 size)
{
	this->_size = size;
	this->UpdateRect();
}
/***************************************************************************************
## SetPivot ##
@@ Pivot::Enum pivot : ������ ��Ʈ �Ǻ��� 

���� �Ǻ��� ����Ǿ��ٸ� ��Ʈ�� �����϶�
****************************************************************************************/
void GameObject::SetPivot(Pivot::Enum pivot)
{
	this->_pivot = pivot;
	this->UpdateRect();
}
/***************************************************************************************
## UpdateRect ##
��Ʈ�� �Ǻ��� ���� ����
****************************************************************************************/
void GameObject::UpdateRect()
{
	switch (_pivot)
	{
	case Pivot::LEFT_TOP:
		this->_rc = RectMake(_position.x, _position.y, _size.x, _size.y);
		break;
	case Pivot::CENTER:
		this->_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
		break;
	case Pivot::BOTTOM:
		this->_rc = RectMakeBottom(_position.x, _position.y, _size.x, _size.y);
		break;
	default:
		break;
	}
}
