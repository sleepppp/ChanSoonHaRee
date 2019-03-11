#include "stdafx.h"
#include "Image.h"
#include "Enemy.h"
#include "MoveItem.h"
#include "Player.h"
Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
	this->_player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");
	_count = 0;
	_attacked = false;
}

//�� ������ �ѱ�� ���� �Լ�.
void Enemy::AttackedDemege(int damage)
{
	//������ �������� �Ѱ��ָ� ��������ŭ �� ü���� ��´�.
	_hp -= damage;
	//hp�� 0���� �۰ų� ������
	if (_hp <= 0)
	{
		//�������. �ٸ� �״� ����� ������ ��� �����Լ� ����� ���ؼ� ������ �ٲ� ���� �ִ�.
		this->Destroy();
	}
	//���� �ʾҴٸ�
	else
	{
		//�ǰ��� ���ߴٴ� ������ Ʈ��� ����� �ְ�
		_attacked = true;
		//�ڷ� �з�����. �÷��̾��� �ޱ��� ���� �־��ָ� ������ �߰��ϸ� ���⿡�� �ݴ�� �ޱ۰��� �����Ƿ� �ݴ�������� �з��� �� �ִ�.
		this->_attackedAngle = Math::GetAngle(_player->GetPosition().x, _player->GetPosition().y, _position.x, _position.y);
	}
}

//��Ʈ������Ʈ�� ���� ����
RECT Enemy::UpdateRect(Vector2 position, Vector2 size, Pivot::Enum _pivot)
{
	RECT rc;
	switch (_pivot)
	{
	case Pivot::LEFT_TOP:
		rc = Figure::RectMake(position, size);
		break;
	case Pivot::CENTER:
		rc = Figure::RectMakeCenter(position, size);
		break;
	case Pivot::BOTTOM:
		rc = Figure::RectMakeBottom(position, size);
		break;
	default:
		break;
	}

	return rc;
}

//�ޱ۰��� ���� ���� Ÿ���� ����.
void Enemy::EnemyMoveType()
{
	//45�� ~ 135���� ���⿡���� ž�� �ٶ󺸰� �Ѵ�.
	if (_angle > Math::PI / 4.f && _angle < ((3 * Math::PI) / 4.f))
	{
		_move = MoveType::Top;
	}
	//135�� ~ 225���� ���⿡���� ����Ʈ�� �ٶ󺸰� �Ѵ�. 
	else if (_angle > ((3.f * Math::PI) / 4.f) && _angle < (Math::PI + (Math::PI / 4.f)))
	{
		_move = MoveType::Left;
	}
	//225�� ~ 315���� ���⿡���� ������ �ٶ󺸰� �Ѵ�.
	else if (_angle > (Math::PI + (Math::PI / 4.f)) && _angle < (Math::PI + ((3.f * Math::PI) / 4.f)))
	{
		_move = MoveType::Bottom;
	}
	//���� ������ �ƴ϶�� ����Ʈ�� �ٶ󺸰��Ѵ�.
	else
	{
		_move = MoveType::Right;
	}
}

bool Enemy::IntersectReaction(RECT * moveRect, RECT * unMoveRect)
{

	RECT rc = { 0 };

	//�浹�� �ȵǾ��ٸ� ����������
	if (IntersectRect(&rc, moveRect, unMoveRect) == false)
		return false;

	int x = rc.right - rc.left;
	int y = rc.bottom - rc.top;
	if (x > y)
	{
		if (rc.bottom == unMoveRect->bottom)
		{
			moveRect->bottom = moveRect->bottom + y;
			moveRect->top = moveRect->top + y;
		}
		else if (rc.top == unMoveRect->top)
		{
			moveRect->bottom = moveRect->bottom - y;
			moveRect->top = moveRect->top - y;
		}
	}
	else
	{
		if (rc.left == unMoveRect->left)
		{
			moveRect->left = moveRect->left - x;
			moveRect->right = moveRect->right - x;
		}
		else if (rc.right == unMoveRect->right)
		{
			moveRect->left = moveRect->left + x;
			moveRect->right = moveRect->right + x;
		}
	}
	return true;
}


void Enemy::ObjectCollision()
{
	//=======================================
	//������Ʈ�� �浹
	//=======================================
	const vector <class GameObject*>* object;
	object = _ObjectManager->GetObjectListPointer(ObjectType::Object);
	for (int i = 0; i < object->size(); i++)
	{

		MoveItem* item = dynamic_cast<MoveItem*>((*object)[i]);
		Player* player = dynamic_cast<Player*>((*object)[i]);

		if (item == nullptr && player == nullptr && this != (*object)[i])
		{
			if (this->IntersectReaction(&_renderRect, &(*object)[i]->GetCollisionRect()))
			{
				_position.x = (_renderRect.right - _renderRect.left) / 2 + _renderRect.left;
				_position.y = (_renderRect.bottom - _renderRect.top) / 2 + _renderRect.top;
				this->_renderRect = UpdateRect(_position, _size, _pivot);
			}
		}
	}
}


//�����Ÿ� ���� ���ϴ� ����.
float Enemy::Distance(Vector2 position)
{
	//�����Ÿ��� ���ϰ�
	float distance = Math::GetDistance(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//��ȯ��
	return distance;
}

//�ޱ۰����ϴ� ����.
float Enemy::Angle(Vector2 position)
{
	//�ޱ۰��� ���ϰ�
	float angle = Math::GetAngle(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//��ȯ��
	return angle;
}