#include "stdafx.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Timer.h"
#include "Enemy.h"
#include "MoveItem.h"
#include "Inventory.h"
#include "Effect.h"
#include "DamageFontManager.h"
#include "Boss.h"

using namespace Figure;


PlayerAni::PlayerAni()
{
}


PlayerAni::~PlayerAni()
{
}

/********************************************************************************/
//## Move ##
//Vector2 direction:����
/********************************************************************************/
void Player::Move(Vector2 direction)
{
	//�̵����� �ʾҴٸ� Float EQUAL�� �Ҽ������������� Ȯ���Ͽ� �̵��� ���� �ʾҴٸ� returnó���Ͽ� ����������.
	if (FLOAT_EQUAL(direction.x, 0.f) && FLOAT_EQUAL(direction.y, 0.f))
		return;

	//�� ��ǥ�� ����*���ǵ�*��ŸŸ��
	this->_position += direction.Normalize()*_speed*_TimeManager->DeltaTime();
	//�̵������� ���� �浹 ��Ʈ ��ġ�� �����Ѵ�.
	_collisionRect = RectMakeCenter(_position, Vector2(30.0f, 40.0f));

	//mainRect�� ��ġ�� ����
	this->UpdateMainRect();

	

	//=======================================
	//������Ʈ�� �浹(InterRect�Լ� ���)
	//=======================================
	const vector <class GameObject*>* object;
	object = _ObjectManager->GetObjectListPointer(ObjectType::Object);

	//��� ������Ʈ��  for������ �浹 �˻縦 ���ش�.
	for (int i = 0; i < object->size(); i++)
	{
		//�÷��̾� �ڽ��� �����ϱ� ���� ���ǹ�
		if (object->at(i)->GetName() != this->_name)
		{	
			//������ Ŭ���� ����ȯ���� ������Ʈ i�� �ҷ��´�.
			MoveItem* item = dynamic_cast<MoveItem*>(object->at(i));
			//���ʹ� Ŭ���� ����ȯ���� ������Ʈ i�� �ҷ��´�.
			Enemy* enemy = dynamic_cast<Enemy*>(object->at(i));				

			//���̳��� ĳ��Ʈ�� null���� ��ȯ�Ǵ� ���
			//�÷��̾� ���� �浹�˻�
			//������(�԰� ����ؾ��ؼ� �浹x) //���ʹ�(���� �˻�?

			
			//�������� �ƴ� ���, ���ʹ̰� �ƴ� ���->���� ������ ���
			if (item == nullptr || enemy == nullptr)// || boss!=nullptr)
			{	
				//���� �Լ� InterRee�� �÷��̾� �浹�� �Լ��� ��ü ������Ʈ�� �浹 �˻��Ѵ�.
				if (this->InterRee(&_collisionRect, &object->at(i)->GetCollisionRect()))
				{
					//�˻��ϴ� ������Ʈ i�� enemy�� ���, Roll �����϶� ����Ͽ� �Ѿ��.
					if (object->at(i)==enemy)
					{
						if (_state == Player::State::LeftRoll || _state == Player::State::RightRoll || _state == Player::State::UpRoll || _state == Player::State::DownRoll)
						{
							continue;
						}
					}
					//�������� ��� ������ ���
					if(object->at(i)==item)
					{
						continue;
					}
					
					//�浹�� ĳ���� �÷��̾ �ݴ�� �о��ָ鼭 ���ڸ��� �ӹ���ó�� �Ѵ�.
					_position.x = (_collisionRect.right - _collisionRect.left) / 2 + _collisionRect.left;
					_position.y = (_collisionRect.bottom - _collisionRect.top) / 2 + _collisionRect.top;
					_mainRect = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
				}
			}
		}
	}
	//�Ѹ��� ����ϱ� ���� bool��
	
	//���ʹ̿��� �浹	
	//this->SendCallbackMessage(TagMessage("PlayerHP",0.0f, this->_currentHp));

	//Enemy* enemy = dynamic_cast<Enemy*>(object[i]);
	//Enemy Ŭ������ ����Ű�� enemy�� ��´�.
	//dynamic_case���̳��� ĳ��(��Ӱ����� ��� ����ȯ(ex: (float)hp ), ������ null���� ��ȯ���༭ ��!)
	//<Enemy*> ������ Ÿ�Կ�... ���ʹ̸� ����Ű�� Ŭ������ ��ҳ�?
	//�ش� ������Ʈ �迭[i]�� ȣ��
}


/********************************************************************************/
//## InterRee ##
//��� ������Ʈ�� �浹 �˻縸�� ���� �Լ�
/********************************************************************************/
bool Player::InterRee(RECT* moveRc, RECT* unMoveRc)
{
	RECT temp;
	if (!IntersectRect(&temp, moveRc, unMoveRc))
	{
		return false;
		//return false�� �������� �ʰ� ������ ��. �׷��� false�� ���� ���°� ����
		//reuturn�� ������ �����°� �߿�!
	}

	int tempWidth = temp.right - temp.left;
	int tempHeight = temp.bottom - temp.top;

	//���α��̰� �� �дٸ� //���Ϸ� �ε��� ����̴�.
	if (tempWidth > tempHeight)
	{
		//�÷��̾� ��->�Ϸ� �浹
		if (moveRc->bottom == temp.bottom)
		{
			//�浹���� ���̸�ŭ �÷��̾�� �����༭ ������ ������.
			//_position.y -= tempHeight;
			moveRc->top -= tempHeight;
			moveRc->bottom -= tempHeight;
		}

		//�÷��̾� ��->������ �浹
		if (moveRc->top == temp.top)
		{
			//�浹���� ���̸�ŭ �÷��̾�� ���༭ ���� �ø���.
			//_position.y += tempHeight;
			moveRc->top += tempHeight;
			moveRc->bottom += tempHeight;
		}
	}
	//���� ���� ���̰� �� ��ٸ� //�¿�� �ε��� ����̴�
	else if (tempHeight > tempWidth)
	{
		//return false;
		//�÷��̾� ��->�·� �浹
		if (moveRc->left == temp.left)
		{
			//���� �÷��̾� ��Ʈ�� �浹�������� �����ʿ��� �ִٸ�,�������̸�ŭ �����ش�.
			//_position.x += tempWidth;
			moveRc->left += tempWidth;
			moveRc->right += tempWidth;
		}

		//�÷��̾� ��->��� �浹
		else if (moveRc->right == temp.right)
		{
			//_position.x -= tempWidth;
			moveRc->left -= tempWidth;
			moveRc->right -= tempWidth;
		}
	}
	return true;
	//return true
}

//=======================================
//�÷��̾� ��ġ ���� �Լ� (�κ��� XY�� ����)
//=======================================
POINT Player::GetPlayerIndex()
{
	POINT IndexXY = { _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY() };
	return IndexXY;
}

//=======================================
//�÷��̾� �� + ���ʹ� = ���ʹ� ü�� ����
//=======================================
void Player::Attack()
{
	if (_isAttacked == false)
	{
		const vector <class GameObject*>* object;
		object = _ObjectManager->GetObjectListPointer(ObjectType::Object);

		for (int i = 0; i < object->size(); i++)
		{
			//�÷��̾� �ڽ��� �����ϱ� ���� ���ǹ�
			if (object->at(i)->GetName() != this->_name)
			{
				Enemy* enemy = dynamic_cast<Enemy*>(object->at(i));
				Boss* boss = dynamic_cast<Boss*>(object->at(i));

				//����� ���ʹ� �浹, ������ ������Ʈ�� ���� ���� ��츸 �˻�
				if (enemy != nullptr)
				{
					RECT temp;
					if (IntersectRect(&temp, &_swordRect, &object->at(i)->GetCollisionRect()))
					{
						//���������� �޾Ƽ� ü���� ��´�(����)
						enemy->AttackedDemege(_damage);						
						_isAttacked = true;
					}
				}
				
				if (boss != nullptr)
				{
					RECT temp;
					if (IntersectRect(&temp, &_swordRect, &object->at(i)->GetCollisionRect()))
					{
						//���������� �޾Ƽ� ü���� ��´�(����)
						boss->AttackedDamage(_damage);
						_isAttacked = true;
					}
				}
			}

			if (_isAttacked == true)
			{
				//�浹 ����Ʈ �߻�
				Effect::PlayEffect(EFFECT_SWORDATK, Vector2(_swordRect.left, _swordRect.top));						
			}
		}
	}
}


//=======================================
//�κ��丮 on/off ��ư�� �Լ�
//=======================================
void Player::InventoryOnOff()
{
	_isMoveStop = false;
}

//=======================================
//���ʹ� ���� + �÷��̾� ��ü = �÷��̾� ü�� ����
//=======================================
void Player::AttackedDamage(int damage)
{
	if (_isDelay == false)
	{
		//�˻��ϴ� ������Ʈ i�� enemy�� ���, Roll �����϶� ����Ͽ� �Ѿ��.
		if (_state == Player::State::LeftRoll || _state == Player::State::RightRoll || _state == Player::State::UpRoll || _state == Player::State::DownRoll)
		{
			this->_currentHp -= 0;
		}		
		else
		{						
			_isDelay = true;
			_blink = 0;
			this->_currentHp -= damage;
			//������ ��Ʈ ���
			_DamageFontManager->ShowDamage(Vector2(_position),_damage);
			_SoundManager->Play("will_damage", 0.6f);
		}
	}
}


//=======================================
//���ʹ̿� �浹��, �����ð� �ο�/�÷��̾� ������ �Լ�
//=======================================
void Player::AtkDelay2()
{
	if (_isDelay == true)
	{
		if (_currentHp > 0)
		{
			_count += _TimeManager->DeltaTime();
			
			if (_count > 0.2f)
			{
				_blink++;
				_count = 0;
				_alpha = !_alpha;
				_isDam = true;
				if (_blink == 6)
				{
					_isDelay = false;
					_alpha = 1.0f;
					_isDam = false;
				}
			}
		}
	}
}



	