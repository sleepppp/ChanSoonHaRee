#include "stdafx.h"
#include "Time.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "StringHelper.h"

SingletonCpp(Time)

Time::Time()
{
	//���� �ϵ��� �����ϴ��� �˻��Ѵ�. 
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&this->periodFrequency))
	{
		//���� �ϵ���� ���� true
		this->isHighHardware = true;
		//������ Ÿ�� �޾ƿ� 
		QueryPerformanceFrequency((LARGE_INTEGER*)&lastTime);

		this->timeScale = 1.0f / this->periodFrequency;
	}
	else
	{
		this->isHighHardware = false;
		this->lastTime = timeGetTime();
		this->timeScale = 0.001f;
	}

	this->frameRate = this->fpsFrameCount = 0;
	this->fpsTimeElapsed = this->worldTime = 0.0f;
}


Time::~Time()
{
}

void Time::Tick(float lockFPS)
{
	static bool isFirstChecking = false;

	//���� �ϵ��� �����Ѵٸ� �и������� �̻��� ������ �޾ƿ´�.
	if (this->isHighHardware)
		QueryPerformanceCounter((LARGE_INTEGER*)&this->curTime);
	//�ƴ϶�� �и������� ������ ����Ÿ���� �޾ƿ´�.
	else
		this->curTime = timeGetTime();
	//deltaTimedms = (���� �ð� - ���� �����ӿ� üŷ�� �ð�) * timeScale;
	this->timeElapsed = (this->curTime - this->lastTime) * timeScale;
	//������ ���� ���� �Ǿ� �ִٸ�
	if (lockFPS > 0.0f)
	{
		//deltaTime�� ���� �����ӽð� ���� ���� ������ ����
		while (this->timeElapsed < (1.0f / lockFPS))
		{
			//���� �ϵ���� �����ϸ� �и������� �̻��� ������ �޾ƿ´�. 
			if (this->isHighHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&this->curTime);
			//�ƴ϶�� ���� �ð��� �и������� ������ ���� �ð��޾ƿ´�. 
			else
				this->curTime = timeGetTime();
			//deltaTime�ٽ� ����
			this->timeElapsed = (this->curTime - this->lastTime) * this->timeScale;
		}
	}
	//������ ������ �ð� ����ð����� �ʱ�ȭ 
	this->lastTime = this->curTime;
	//������ ����
	this->fpsFrameCount++;
	//������ ��Ÿ Ÿ�� ���� 
	this->fpsTimeElapsed += this->timeElapsed;
	//���μ��� ���� �� �ð� ����
	this->worldTime += this->timeElapsed;
	//�ʴ� ������ Ÿ���� 1�ʰ� �Ѿ��ٸ� ��ҵ� �ٽ� �ʱ�ȭ 
	if (this->fpsTimeElapsed > 1.0f)
	{
		this->frameRate = this->fpsFrameCount;
		this->fpsFrameCount = 0;
		this->fpsTimeElapsed = 0.0f;
	}
	//worldTime ���� ������ �߰�
	if (isFirstChecking == false)
	{
		this->worldTime = 0.0f;
		isFirstChecking = true;
	}
}

void Time::Init()
{
	this->frameRate = this->fpsFrameCount = 0;
	this->fpsTimeElapsed = this->worldTime = 0.0f;
}

void Time::Update()
{
	this->Tick(500.0f);
}

void Time::Render()
{
#ifdef _DEBUG
	{
		_DXRenderer->RenderText(5, 5, L"WorldTime : " + StringHelper::StringToWString(to_string(this->worldTime)), 20, DefaultBrush::white);
		_DXRenderer->RenderText(5, 30, L"DeltaTime : " + StringHelper::StringToWString(to_string(this->timeElapsed)), 20, DefaultBrush::white);
		_DXRenderer->RenderText(5, 55, L"FPS : " + StringHelper::StringToWString(to_string(this->frameRate)), 20, DefaultBrush::white);
	}
#else
	{
	}
#endif
}
