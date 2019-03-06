#pragma once
#include "Enemy.h"
class Weeds :	public Enemy
{
private:
	class Image* _weeds;
	int _imageCount;
	float _count;
	bool _isAttack;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	void Collision();

	bool IntersectReaction(RECT* moveRect,RECT* unMoveRect);
public:
	Weeds(Vector2 pos);
	~Weeds();
};

