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
	:pivot(Pivot::LEFT_TOP),position(0.f,0.f),size(0.f,0.f),isActive(true),isLive(true)
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
	this->position = pos;
	this->UpdateRect();
}
/***************************************************************************************
## SetSize ## 
@@ Vector2 size : ������ ������ �� 

������ ���� ������ ������ ��Ʈ�� �����ض� 
****************************************************************************************/
void GameObject::SetSize(Vector2 size)
{
	this->size = size;
	this->UpdateRect();
}
/***************************************************************************************
## SetPivot ##
@@ Pivot::Enum pivot : ������ ��Ʈ �Ǻ��� 

���� �Ǻ��� ����Ǿ��ٸ� ��Ʈ�� �����϶�
****************************************************************************************/
void GameObject::SetPivot(Pivot::Enum pivot)
{
	this->pivot = pivot;
	this->UpdateRect();
}
/***************************************************************************************
## UpdateRect ##
��Ʈ�� �Ǻ��� ���� ����
****************************************************************************************/
void GameObject::UpdateRect()
{
	switch (pivot)
	{
	case Pivot::LEFT_TOP:
		this->rc = RectMake(position.x, position.y, size.x, size.y);
		break;
	case Pivot::CENTER:
		this->rc = RectMakeCenter(position.x, position.y, size.x, size.y);
		break;
	case Pivot::BOTTOM:
		this->rc = RectMakeBottom(position.x, position.y, size.x, size.y);
		break;
	default:
		break;
	}
}
