#include "stdafx.h"
#include "testYap.h"
#include "image.h"
#include "Animation.h"
#include "Arrow.h"

using namespace Figure;

testYap::testYap() //ÃÊ±âÈ­
{
	this->_name = "ÆÄ±«ÀÚ";
	this->_position = Vector2(100, 100);
	this->_size = Vector2(100, 100);

	this->_frameX = 0;
	this->_frameY = 0;

	this->_mainRect = RectMakePivot(_position.x, _position.y, _size.x, _size.y, Pivot::CENTER);
	
	_img->FrameRender(_position.x, _position.y, _frameX, _frameY);
	_img = _ImageManager->FindImage("ÆÄ±«ÀÚ");

	



}
testYap::~testYap()
{
}

void testYap::Init()
{

}

void testYap::Release()
{

}

void testYap::Update()
{

}

void testYap::Render()
{

}