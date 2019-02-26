#pragma once
#include "GameObject.h"
class TestEenemy : public GameObject
{
	enum class State
	{
		Chasing,Attacked
	}_state;
	float _attackedSpeed;
	int _hp;
public:
	TestEenemy(Vector2 pos,Vector2 size);
	~TestEenemy();

	void Init();
	void Release();
	void Update();
	void Render();

	void Damage(int damage);
};

