#pragma once
#include "SceneBase.h"
class Dungeon_Map_01 :	public SceneBase
{
private:
	RECT collisionRc;
	class Image* map;
	class GameObject* _object;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	RECT Collision(RECT rc);
public:
	Dungeon_Map_01(Vector2 pos, Vector2 size);
	~Dungeon_Map_01();
};

