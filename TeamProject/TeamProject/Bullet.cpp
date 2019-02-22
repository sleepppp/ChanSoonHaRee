#include "stdafx.h"
#include "Bullet.h"


void Bullet::Init(int bulletMax, float range) 
{
	//변수 담기
	_bulletMax = bulletMax;	//최대 총알 갯수
	_range = range;			//사거리

	//최대 총알 갯수만큼 벡터에 총알 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//구조체 총알 선언
		TagBullet _bullet;	//구조체 총알
		
		//구조체 총알 전체 초기화해주기
		ZeroMemory(&_bullet, sizeof(TagBullet));

		//총알 발사 false선언
		_bullet.isfire = false;

		//벡터에 총알 담기
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
		//총알 사각형 그리기
		_DXRenderer->DrawRectangle(_vBullet.at(i).rc, DefaultBrush::green, false, 3.0f);
	}
	
}

//발사
void Bullet::Fire(Vector2 position, Vector2 size, float angle, float speed)
{
	//벡터 이터레이터 총알로 for문 돌리기
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		//만일 벡터 이터레이터 총알이 발사면 되돌리기
		if (_viBullet->isfire) continue;

		//벡터 이터레이터 발사 true
		_viBullet->isfire = true;

		//발사 좌표
		_viBullet->position.x = _viBullet->firePosition.x = position.x;
		_viBullet->position.y = _viBullet->firePosition.y = position.y;
		
		//총알 크기
		_viBullet->size.x = size.x;
		_viBullet->size.y = size.y;


		//발사 각도
		_viBullet->angle = angle;

		//발사 속도
		_viBullet->speed = speed;

		//총알 렉트 만들기
		_viBullet->rc = Figure::RectMakeCenter(_viBullet->position.x, _viBullet->position.y, _viBullet->size.x, _viBullet->size.y);

		//중복 체크를 피하기 위해 break
		break;
	}
}

//움직이기
void Bullet::Move() 
{
	//벡터 이터레이터 총알로 for문 돌리기
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		//만일 벡터 이터레이터 총알이 발사 상태가 아니면 되돌리기
		if (!_viBullet->isfire) continue;

		//발사!!
		//총알 움직이기
		//총알 x 포지션에 코싸인 총알 앵글 * 총알 스피드 * 델타 타임
		_viBullet->position.x += cosf(_viBullet->angle) * _viBullet->speed * _Time->DeltaTime();

		//총알 y 포지션에 싸인 총알 앵글 * 총알 스피드 * 델타 타임
		_viBullet->position.y -= sinf(_viBullet->angle)*_viBullet->speed * _Time->DeltaTime();

		//총알 렉트 만들기
		_viBullet->rc = Figure::RectMakeCenter(_viBullet->position.x, _viBullet->position.y, _viBullet->size.x, _viBullet->size.y);

		//총알 거리 구하기
		float distance = Math::GetDistance(_viBullet->firePosition.x, _viBullet->firePosition.y, _viBullet->position.x, _viBullet->position.y);

		//만약, 사정거리 보다 거리가 멀어지면 발사 막기 isfire 를 false 처리
		if (_range < distance) 
		{
			_viBullet->isfire = false;
		}
	}
}

//총알 충돌 처리 함수
bool Bullet::Intersect(RECT rc) 
{
	for (int i = 0; i < _vBullet.size(); i++) 
	{
		RECT temp;
		if (IntersectRect(&temp, &_vBullet.at(i).rc, &rc)) 
		{
			//충돌되면 fire를 false로
			_vBullet.at(i).isfire = false;

			return true;
		}
	}
	return false;
}