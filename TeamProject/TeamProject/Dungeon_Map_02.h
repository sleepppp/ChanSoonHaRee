#pragma once
#include "SceneBase.h"
class Dungeon_Map_02 :	public SceneBase
{
private:
	RECT _doorRect;

	class Image* _map;
	class Image* _door;
	class GameObject* _object;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

public:
	Dungeon_Map_02();
	~Dungeon_Map_02();
};

