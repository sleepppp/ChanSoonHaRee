#pragma once
#include "GameObject.h"

class TestPlayer : public GameObject
{
	
private:
	Vector2 _direction;
	RECT _attackRc;
	float _attackTime;
	float _attackActiveTime;
	bool _isAttackActive;
public:
	TestPlayer();
	~TestPlayer();

	void Init()override;
	void Release()override;
	void Update()override; 
	void Render()override; 

	void SaveData();
	void LoadData();
};

