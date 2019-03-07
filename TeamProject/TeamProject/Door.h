#pragma once
#include "GameObject.h"
class Door :
	public GameObject
{
private:
	RECT rc;
	Vector2 rcPosition;
	Vector2 rcSize;

	float _timeCount;
	int _doorCount;

	class Image* _door;
	class Player* _player;

public:
	Door(Vector2 pos, Vector2 size);
	virtual ~Door();

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

};

