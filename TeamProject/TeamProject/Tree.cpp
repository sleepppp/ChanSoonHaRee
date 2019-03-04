#include "stdafx.h"
#include "Tree.h"


Tree::Tree(Vector2 pos)
	:FrameObject("tree",pos)
{
	_collisionRect = Figure::RectMakeBottom(_position, Vector2(100,50));
}

Tree::~Tree()
{
}

void Tree::Release()
{
	FrameObject::Release();
}

void Tree::Update()
{
	FrameObject::Update();
}

void Tree::Render()
{
	FrameObject::Render();
}
