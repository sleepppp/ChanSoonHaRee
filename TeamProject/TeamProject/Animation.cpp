#include "stdafx.h"
#include "Animation.h"

#include "Image.h"
#include "StringHelper.h"
#include "BinaryFile.h"
#include "SceneManager.h"

/*****************************************************************************
## Animation ##
******************************************************************************/
Animation::Animation()
	:isPlay(false), isLoop(true), currentFrameIndex(0),
	currentFrameTime(0.f), frameUpdateTime(0.3f), image(nullptr),
	isReverseX(false), isReverseY(false),func(nullptr)
{

}

/*****************************************************************************
## ~Animation ##
******************************************************************************/
Animation::~Animation()
{
	this->frameList.clear();
}


/*****************************************************************************
## UpdateFrame ##
******************************************************************************/
void Animation::UpdateFrame()
{
	//���� �÷����ߴٸ�
	if (this->isPlay)
	{
		//������ ���� �ð��� ��Ÿ Ÿ�Ӹ�ŭ ���� 
		this->currentFrameTime += _Time->DeltaTime();
		//���� �����Ӱ��� �ð��� ������ ������Ʈ �Ǵ� �ð����� Ŀ���ٸ� 
		if (this->currentFrameTime >= this->frameUpdateTime)
		{
			//������ ���� �ð� �Ѿ �ð���ŭ ����ְ� 
			while (currentFrameTime >= frameUpdateTime)
			{
				this->currentFrameTime -= frameUpdateTime;
			}
			//������ �ε��� ����
			++currentFrameIndex;
			//������ �ε����� ������ ������ ������� Ŀ������ �Ѵٸ�
			if (currentFrameIndex >= CastingInt(this->frameList.size()))
			{
				//������ �ε����� 0
				this->currentFrameIndex = 0;
				//���� ���� �� �ƴ϶�� �÷��� ���� ���ְ� 
				if (isLoop == false)
					isPlay = false;
				//���� �����ų �Լ��� �ִٸ� ������Ѷ� 
				if (func)
					func();
			}

		}
	}
}

/******************************************************************************
## Render ##
*******************************************************************************/
void Animation::Render(RECT rc)
{
	//�̹��� Ű���� �ִٸ�
	if (this->image)
	{
		Vector2 size = Vector2(CastingFloat(rc.right - rc.left), CastingFloat(rc.bottom - rc.top));
		this->image->SetSize(size);					//������ ����
		this->image->SetReverseX(isReverseX);		//���η� ��������
		this->image->SetReverseY(isReverseY);		//���η� �������� 
		//������ ������ ���Ϳ� pair�� ��� �ִµ� first���� x ������ ���� second���� y������ ����
		this->image->FrameRender(CastingInt(rc.left), CastingInt(rc.top), 
			frameList[currentFrameIndex].first, frameList[currentFrameIndex].second, Pivot::LEFT_TOP, true);
	}
}
/*****************************************************************************
## Start ##
******************************************************************************/
void Animation::Start()
{
	this->isPlay = true;
}
/*****************************************************************************
## Stop ##
******************************************************************************/
void Animation::Stop()
{
	this->isPlay = false;
	this->currentFrameIndex = 0;
	this->currentFrameTime = 0.f;
}
/*****************************************************************************
## Pause ##
******************************************************************************/
void Animation::Pause()
{
	this->isPlay = false;
}

/*****************************************************************************
## SetVectorFrame ##
@@ vector<pair<int,int>> playFrame : �÷��� ����Ʈ
******************************************************************************/
void Animation::SetVectorFrame(vector<pair<int, int>> playFrame)
{
	this->frameList.clear();
	this->frameList = playFrame;
}
/*****************************************************************************
## SetStartEndFrame ##
@@ int startX : ���� �ε��� x
@@ int startY : ���� �ε��� y
@@ int endX : �� �ε��� x
@@ int endY : �P �ε��� y
@@ bool reverse : ������ ������ �Ұ�����
@@ FrameDirection direction : ������ ����(��,Ⱦ)
*****************************************************************************/
void Animation::SetStartEndFrame(int startX, int startY, int endX, int endY,
	bool reverse, FrameDirection direction)
{
	this->frameList.clear();

	if (direction == FrameDirection::Horizontal)
	{
		for (int y = startY; y < endY + 1; ++y)
		{
			for (int x = startX; x < endX + 1; ++x)
			{
				this->frameList.push_back(make_pair(x, y));
			}
		}

		if (reverse)
		{
			for (int y = endY ; y >= startY; --y)
			{
				for (int x = endX; x >= startX; --x)
				{
					this->frameList.push_back(make_pair(x, y));
				}
			}
		}

	}
	else if (direction == FrameDirection::Vertical)
	{
		for (int x = startX; x < endX + 1; ++x)
		{
			for (int y = startY; y < endY + 1; ++y)
			{
				this->frameList.push_back(make_pair(x, y));
			}
		}

		if (reverse)
		{
			for (int x = endX ; x >= startX; --x)
			{
				for (int y = endY; y >= startY; --y)
				{
					this->frameList.push_back(make_pair(x, y));
				}
			}
		}
	}
}
/*****************************************************************************
## SetCallbackFunc ##
@@ function<void()> func : �ִϸ��̼� ���� �� ������ �ݹ��Լ� 
******************************************************************************/
void Animation::SetCallbackFunc(function<void()> func)
{
	this->func = func;
}


/******************************************************************************
## SetImage ##
@@ Image* image : �̹���
*******************************************************************************/
void Animation::SetImage(Image * image)
{
	this->imageKey = image->GetLoadInfo().key;
	this->image = image;
}
/******************************************************************************
## SetImage ##
@@ Image* image : �̹��� Ű��
*******************************************************************************/
void Animation::SetImage(string name)
{
	this->imageKey = name;
	this->image = _ImageManager->FindImage(name);
}

/*****************************************************************************
## GetNowFrameData ##
���� ������ ������ ��ȯ
******************************************************************************/
pair<int, int> Animation::GetNowFrameData() const
{
	return this->frameList[currentFrameIndex];
}
/*****************************************************************************
## GetNowFrameX ##
���� ������ X
******************************************************************************/
int Animation::GetNowFrameX() const
{
	return this->frameList[currentFrameIndex].first;
}
/*****************************************************************************
## GetNowFrameY ##
���� ������ ������ Y
******************************************************************************/
int Animation::GetNowFrameY() const
{
	return this->frameList[currentFrameIndex].second;
}

