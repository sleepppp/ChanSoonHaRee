#pragma once
#include "FrameObject.h"
class Tree : public FrameObject
{
public:
	Tree(Vector2 pos);
	virtual ~Tree();

	void Release()override; 
	void Update()override;
	void Render()override; 

};

