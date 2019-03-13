#pragma once
#include "GameObject.h"
class NpcKids : public GameObject
{
private:
	class Image* _kids;


public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	NpcKids();
	~NpcKids();
};

