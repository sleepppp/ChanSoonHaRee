#include "stdafx.h"
#include "TestInventorySlot.h"

#include "StringHelper.h"
TestInventorySlot::TestInventorySlot(Vector2 pos, Vector2 size)
	:_offsetPosition(pos), _size(size), _itemCount(0)
{
}

TestInventorySlot::~TestInventorySlot()
{
}
/***********************************************************
## AddItem ##
@@ TestItem item : �߰��� ������ 
 ***********************************************************/
void TestInventorySlot::AddItem(TestItem item)
{
	//���� ������ ����ִ� ������ ���ٸ� ������ ������ �ش� ������ ������ �ʱ�ȭ 
	if (this->GetIsEmpty() == true)
		_item = item;
	//������ ���� �߰� 
	_itemCount++;
}
/***********************************************************
## UpdatePosition ##
@@ Vector2 parentPos : �κ��丮�� ��ǥ 
 ***********************************************************/
void TestInventorySlot::UpdatePosition(Vector2 parentPos)
{
	//�� ��ǥ�� �θ���ǥ + �����ǥ �Ÿ� 
	_position = parentPos + _offsetPosition;
	_rect = Figure::RectMake(_position, _size);
}
/***********************************************************
## Render ##
 ***********************************************************/
void TestInventorySlot::Render()
{
	//�������� �ִٸ�
	if (_itemCount > 0)
	{
		//�̹��� �׷���
		_item.GetImage()->SetSize(_size);
		_item.GetImage()->Render(CastingInt(_rect.left), CastingInt(_rect.top), Pivot::LEFT_TOP, false);
		//������ ���� 2�� �̻��ִٸ� ���� ���
		if (_itemCount > 1)
			_DXRenderer->RenderText(CastingInt(_rect.right - (LONG)(_size.x / 2.5f)), _rect.bottom - (LONG)(_size.y / 2.5f),
				StringHelper::StringToWString(to_string(_itemCount)), 30, DefaultBrush::white);
	}

	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_rect, DefaultBrush::red, false);
	}
}

bool TestInventorySlot::GetIsEmpty()
{
	if (_itemCount <= 0)
		return true;

	return false;
}
