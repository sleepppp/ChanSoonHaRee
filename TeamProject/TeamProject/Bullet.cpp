#include "stdafx.h"
#include "Bullet.h"


void Bullet::Init(int bulletMax, float range) 
{
	//���� ���
	_bulletMax = bulletMax;	//�ִ� �Ѿ� ����
	_range = range;			//��Ÿ�

	//�ִ� �Ѿ� ������ŭ ���Ϳ� �Ѿ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//����ü �Ѿ� ����
		TagBullet _bullet;	//����ü �Ѿ�
		
		//����ü �Ѿ� ��ü �ʱ�ȭ���ֱ�
		ZeroMemory(&_bullet, sizeof(TagBullet));

		//�Ѿ� �߻� false����
		_bullet.isfire = false;

		//���Ϳ� �Ѿ� ���
		_vBullet.push_back(_bullet);
	}
}

void Bullet::Release() 
{

}

void Bullet::Update() 
{
	this->Move();
}

void Bullet::Render() 
{
	for (int i = 0; i < _vBullet.size(); i++) 
	{
		//�Ѿ� �簢�� �׸���
		_DXRenderer->DrawRectangle(_vBullet.at(i).rc, DefaultBrush::green, false, 3.0f);
	}
	
}

//�߻�
void Bullet::Fire(Vector2 position, Vector2 size, float angle, float speed)
{
	//���� ���ͷ����� �Ѿ˷� for�� ������
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		//���� ���� ���ͷ����� �Ѿ��� �߻�� �ǵ�����
		if (_viBullet->isfire) continue;

		//���� ���ͷ����� �߻� true
		_viBullet->isfire = true;

		//�߻� ��ǥ
		_viBullet->position.x = _viBullet->firePosition.x = position.x;
		_viBullet->position.y = _viBullet->firePosition.y = position.y;
		
		//�Ѿ� ũ��
		_viBullet->size.x = size.x;
		_viBullet->size.y = size.y;


		//�߻� ����
		_viBullet->angle = angle;

		//�߻� �ӵ�
		_viBullet->speed = speed;

		//�Ѿ� ��Ʈ �����
		_viBullet->rc = Figure::RectMakeCenter(_viBullet->position.x, _viBullet->position.y, _viBullet->size.x, _viBullet->size.y);

		//�ߺ� üũ�� ���ϱ� ���� break
		break;
	}
}

//�����̱�
void Bullet::Move() 
{
	//���� ���ͷ����� �Ѿ˷� for�� ������
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		//���� ���� ���ͷ����� �Ѿ��� �߻� ���°� �ƴϸ� �ǵ�����
		if (!_viBullet->isfire) continue;

		//�߻�!!
		//�Ѿ� �����̱�
		//�Ѿ� x �����ǿ� �ڽ��� �Ѿ� �ޱ� * �Ѿ� ���ǵ� * ��Ÿ Ÿ��
		_viBullet->position.x += cosf(_viBullet->angle) * _viBullet->speed * _Time->DeltaTime();

		//�Ѿ� y �����ǿ� ���� �Ѿ� �ޱ� * �Ѿ� ���ǵ� * ��Ÿ Ÿ��
		_viBullet->position.y -= sinf(_viBullet->angle)*_viBullet->speed * _Time->DeltaTime();

		//�Ѿ� ��Ʈ �����
		_viBullet->rc = Figure::RectMakeCenter(_viBullet->position.x, _viBullet->position.y, _viBullet->size.x, _viBullet->size.y);

		//�Ѿ� �Ÿ� ���ϱ�
		float distance = Math::GetDistance(_viBullet->firePosition.x, _viBullet->firePosition.y, _viBullet->position.x, _viBullet->position.y);

		//����, �����Ÿ� ���� �Ÿ��� �־����� �߻� ���� isfire �� false ó��
		if (_range < distance) 
		{
			_viBullet->isfire = false;
		}
	}
}

//�Ѿ� �浹 ó�� �Լ�
bool Bullet::Intersect(RECT rc) 
{
	for (int i = 0; i < _vBullet.size(); i++) 
	{
		RECT temp;
		if (IntersectRect(&temp, &_vBullet.at(i).rc, &rc)) 
		{
			//�浹�Ǹ� fire�� false��
			_vBullet.at(i).isfire = false;

			return true;
		}
	}
	return false;
}