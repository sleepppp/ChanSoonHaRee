#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"

#include <algorithm>

void ObjectManager::ZOrder()
{
	//�������� �������� zorder
	sort(_objectContainer[ObjectType::Object].begin(), _objectContainer[ObjectType::Object].end(),
		[this](GameObject* object1, GameObject* object2)
	{
		if (object1->GetCollisionRect().bottom < object2->GetCollisionRect().bottom)
			return true;
		return false;
	});
}