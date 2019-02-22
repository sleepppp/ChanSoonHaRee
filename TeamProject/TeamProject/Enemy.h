#pragma once
#include "GameObject.h"
class Enemy :	public GameObject
{
private:
	float _speed;
	bool _isLeft;
	int _count;
	float _angle;
	class Bullet* _bullet;
	class Player* _player;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	void EnemyMove();
	void EnemyFire();
	void EnemyInit();
public:
	Enemy(Vector2 position);
	~Enemy();
};

