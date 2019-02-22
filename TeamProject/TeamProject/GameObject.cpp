#include "stdafx.h"
#include "GameObject.h"

//RectMake,RectMakeCenter등등 쌤의 코드에서 있던 commonMacroFunction.h와 같은 역할을 한다. 
//만약 Figure::RectMake 같이 코드를 계속 치기 귀찮다면 해당 cpp에서 
//아래와 같이 using namespace Figure를 쳐주게 되면 전처럼 바로 RectMake함수를 호출할 수 있게된다. 
using namespace Figure;

/********************************************************************************************
## GameObject ##
생성자 

멤버 이니셜라이즈~
게임오브젝트가 할당 될 때 멤버변수(클래스 변수)들의 생성자도 함께 호출해주기 때문에 이런식으로 
기본값을 초기화 해주면 더 빠르다. 
**********************************************************************************************/
GameObject::GameObject()
	:_pivot(Pivot::LEFT_TOP),_position(0.f,0.f),_size(0.f,0.f),_isActive(true),_isLive(true)
{
	//기본값으로 렉트 설정 
	this->UpdateRect();
}

/***************************************************************************************
## ~GameObject ##
소멸자
****************************************************************************************/
GameObject::~GameObject()
{
}
/***************************************************************************************
## SetPosition ## 
@@ Vector2 pos : 설정할 좌표 값 

좌표가 변경 사항이 있으면 렉트를 갱신해라
****************************************************************************************/
void GameObject::SetPosition(Vector2 pos)
{
	this->_position = pos;
	this->UpdateRect();
}
/***************************************************************************************
## SetSize ## 
@@ Vector2 size : 설정할 사이즈 값 

사이즈 변경 사항이 있으면 렉트를 갱신해라 
****************************************************************************************/
void GameObject::SetSize(Vector2 size)
{
	this->_size = size;
	this->UpdateRect();
}
/***************************************************************************************
## SetPivot ##
@@ Pivot::Enum pivot : 설정할 렉트 피봇값 

만약 피봇이 변경되었다면 렉트를 갱신하라
****************************************************************************************/
void GameObject::SetPivot(Pivot::Enum pivot)
{
	this->_pivot = pivot;
	this->UpdateRect();
}
/***************************************************************************************
## UpdateRect ##
렉트를 피봇에 따라 갱신
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
