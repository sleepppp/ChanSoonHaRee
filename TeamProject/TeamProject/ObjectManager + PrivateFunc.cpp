#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"

#include <algorithm>

void ObjectManager::ZOrder()
{
	//오름차순 기준으로 zorder
	sort(_objectContainer[ObjectType::Object].begin(), _objectContainer[ObjectType::Object].end(),
		[this](GameObject* object1, GameObject* object2)
	{
		if (object1->GetMainRect().bottom < object2->GetMainRect().bottom)
			return true;
		return false;
	});
}