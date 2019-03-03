#include "stdafx.h"
#include "PointLight.h"

#include "LightSystem.h"
PointLight::PointLight()
	:_color(1.f,1.f,1.f,1.f),_originRange(100.f),_intensity(1.f)
{
	
}


PointLight::~PointLight()
{
}

void PointLight::Update()
{
	_LightingSystem->RequestLighting(this);
}
