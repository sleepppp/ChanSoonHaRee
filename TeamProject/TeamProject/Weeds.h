#pragma once
#include "Enemy.h"
class Weeds :	public Enemy
{
private:
	class Image* _weeds;
	class Image* _weeds_Red;
	class Image* _weeds_White;
	class Image* _shadow;
	int _imageCount;
	float _count;
	bool _isAttack;
	int	 _attackedCount;		//피격시 뒤로 밀리는 타이밍을 재기 위한 카운트
	float _attackTime;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	void Collision();
	void Move();
public:
	Weeds(Vector2 pos);
	~Weeds();
};

