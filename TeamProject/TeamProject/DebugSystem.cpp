#include "stdafx.h"
#include "DebugSystem.h"

#include "LightSystem.h"
DebugSystem::DebugSystem()
{
}


DebugSystem::~DebugSystem()
{
}

void DebugSystem::DebugRender()
{
	static float shakeStrength = CameraDefaultStrength;
	static float shakeTime = CameraDefaultShakeTime;

	if (_isDebug)
	{
		_TimeManager->Render();
		_LightingSystem->OnGui();
		_Camera->OnGui();
	}
}
