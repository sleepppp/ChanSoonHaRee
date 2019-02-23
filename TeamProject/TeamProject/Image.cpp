#include "stdafx.h"
#include "Image.h"

ID2D1RenderTarget* Image::renderTarget = nullptr;


/********************************************************************************
## Init ## 
������ ���� �̹��� �ʱ�ȭ
@@ ID2D1Bitmap* bitmap : ��Ʈ�� ������ (ResourceManagerŬ�������� ���� �� �־���) 
@@ TagLoadedImageInfo info : �̹��� Ű���� ��ΰ��� ���� ����ü
********************************************************************************/
void Image::Init(ID2D1Bitmap * bitmap, TagLoadedImageInfo loadinfo)
{
	this->bitmap = bitmap;
	this->loadInfo = loadinfo;

	this->size.x = (float)this->bitmap->GetPixelSize().width;
	this->size.y = (float)this->bitmap->GetPixelSize().height;

	this->scale.x = 1.0f;
	this->scale.y = 1.0f;
	this->alpha = 1.0f;
	this->angle = 0.0f;

	FrameRect rc;
	rc.X = 0;
	rc.Y = 0;
	rc.Width = size.x;
	rc.Height = size.y;
	this->frameInfo.push_back(rc);

	this->maxFrameX = this->maxFrameY = 1;
}

/********************************************************************************
## Init ## 
@@ ID2D1Bitmap* bitmap : ��Ʈ�� ������ (ResourceManagerŬ�������� ���� �� ���ڷ� �־���) 
@@ TagLoadImageInfo info : �̹��� Ű���� ��ΰ� ���� ����ü 
@@ int maxFrameX : ���� ������ �� 
@@ int maxFrameY : ���� ������ �� 
********************************************************************************/
void Image::Init(ID2D1Bitmap * bitmap, TagLoadedImageInfo loadinfo, int maxframeX, int maxframeY)
{
	this->bitmap = bitmap;
	this->loadInfo = loadinfo;
	
	this->size.x = (float)bitmap->GetPixelSize().width;
	this->size.y = (float)bitmap->GetPixelSize().height;

	this->scale.x = 1.0f;
	this->scale.y = 1.0f;
	this->alpha = 1.0f;
	this->angle = 0.0f;

	this->maxFrameX = maxframeX;
	this->maxFrameY = maxframeY;

	float frameX = size.x / this->maxFrameX;
	float frameY = size.y / this->maxFrameY;

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
		for (int i = 0; i < maxFrameX; ++i)
		{
			rc.X = (float)i * (frameX);
			rc.Y = (float)j * (frameY);
			rc.Width = frameX;
			rc.Height = frameY;
			this->frameInfo.push_back(rc);
		}
	}
}

/********************************************************************************
## Release ## 
��Ʈ�� ����
********************************************************************************/
void Image::Release()
{
	this->bitmap->Release();
	this->bitmap = nullptr;

	if (this->pixelCollisionDC)
		DeleteDC(this->pixelCollisionDC);
}

/********************************************************************************
## Render ## 
������ ���� �̹��� ������
@@ int x : ������ x��ǥ 
@@ int y : ������ y��ǥ
@@ Pivot::Enum pivot : ������ �� �Ǻ� ��
@@ bool isRelativePos : ī�޶��� ����
********************************************************************************/
void Image::Render(int x, int y, Pivot::Enum pivot, bool isRelativePos)
{
	size.x = size.x * scale.x;
	size.y = size.y * scale.y;

	Vector2 render = GetPivotPosition(x, y, pivot);

	if (isRelativePos)
	{
		//ī�޶�
		float zoom = _Camera->GetZoom();
		Vector2 zoomScale = Vector2(zoom, zoom);
		size.x = size.x * zoomScale.x;
		size.y = size.y * zoomScale.y;

		//ī�޶� �����ǥ
		render = _Camera->GetRelativeVector2(render);
	}
	//ī�޶� ������ ����x
	if (render.x - size.x > WinSizeX || render.x + size.x < 0 ||
		render.y - size.y > WinSizeY || render.y + size.y < 0)
	{
		ResetRenderOption();
		return;
	}
	
	D2D1::Matrix3x2F reverse = D2D1::Matrix3x2F::Scale(scale.x, scale.y);
	Vector2 offset(0, 0);
	if (this->reverseAxisX)
	{
		reverse = D2D1::Matrix3x2F::Scale(-scale.x, scale.y);
		offset.x = size.x;
	}
	if (reverseAxisY)
	{
		reverse = D2D1::Matrix3x2F::Scale(scale.x, -scale.y);
		offset.y = size.y;
	}

	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.x, size.y);
	Image::renderTarget->SetTransform(reverse * rotation *
		SetupRender((int)(render.x + offset.x), (int)(render.y + offset.y)));
	Image::renderTarget->DrawBitmap(bitmap, dxArea, alpha);

	this->ResetRenderOption();

	_DXRenderer->AddDrawCall();
}

/********************************************************************************
## FrameRender ## 
@@ int x : ������ �� x��ǥ
@@ int y : ������ �� y��ǥ 
@@ int frameX : ���� ������
@@ int frameY : ���� ������ 
@@ Pivot::Enum pivot : ������ �� �Ǻ� 
@@ bool isRelativePos : ī�޶� ���� ���� 
********************************************************************************/
void Image::FrameRender(int x, int y, int frameX, int frameY, Pivot::Enum pivot, bool isRelativePos)
{
	if (frameX >= this->maxFrameX || frameY >= this->maxFrameY)
	{
		ResetRenderOption();
		return;
	}
	int frame = frameY * maxFrameX + frameX;
	//this->size = GetFrameSize(frame);

	size.x = size.x * scale.x;
	size.y = size.y * scale.y;

	Vector2 render = GetPivotPosition(x, y, pivot);

	if (isRelativePos)
	{
		//ī�޶�
		float zoom = _Camera->GetZoom();
		Vector2 zoomScale = Vector2(zoom, zoom);
		size.x = size.x * zoomScale.x;
		size.y = size.y * zoomScale.y;

		//ī�޶� �����ǥ
		render = _Camera->GetRelativeVector2(render);
	}
	//ī�޶� ������ ����x
	if (render.x - size.x > WinSizeX || render.x + size.x < 0 ||
		render.y - size.y > WinSizeY || render.y + size.y < 0)
	{
		ResetRenderOption();
		return;
	}

	D2D1::Matrix3x2F reverse = D2D1::Matrix3x2F::Scale(scale.x, scale.y);
	Vector2 offset(0, 0);
	if (this->reverseAxisX)
	{
		reverse = D2D1::Matrix3x2F::Scale(-scale.x, scale.y);
		offset.x = size.x;
	}
	if (reverseAxisY)
	{
		reverse = D2D1::Matrix3x2F::Scale(scale.x, -scale.y);
		offset.y = size.y;
	}

	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.x, size.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)frameInfo[frame].X,(float) frameInfo[frame].Y,
		(float)(frameInfo[frame].X + frameInfo[frame].Width),
		(float)(frameInfo[frame].Y + frameInfo[frame].Height));

	Image::renderTarget->SetTransform(reverse * rotation *
		SetupRender((int)(render.x + offset.x),(int)(render.y + offset.y)));
	Image::renderTarget->DrawBitmap(bitmap, dxArea, alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);

	this->ResetRenderOption();

	_DXRenderer->AddDrawCall();
}

/********************************************************************************
## SetSize ## 
@@ Vector2 vec : ������
********************************************************************************/
void Image::SetSize(Vector2 vec)
{
	this->size = vec;
}
/********************************************************************************
## SetAlpha ## 
@@ float alpha : ���İ�
********************************************************************************/
void Image::SetAlpha(float alpha)
{
	this->alpha = alpha;
}
/********************************************************************************
## SetScale ##
@@ float scale : �����ϸ� ���� 
********************************************************************************/
void Image::SetScale(float scale)
{
	this->scale = Vector2(scale, scale);
}
/********************************************************************************
## SetAngle ## 
ȸ���� ���� 
@@ flaot angle : ��׸� ������ �־�����
********************************************************************************/
void Image::SetAngle(float angle /*��׸�*/)
{
	this->angle = angle;
}
/********************************************************************************
## ResetRenderOption ## 
��ü ������ ���� ���� �ʱ�ȭ (������ �Լ� ȣ�� �Ŀ� �ڵ����� ȣ��ȴ�.)
********************************************************************************/
void Image::ResetRenderOption()
{
	this->alpha = 1.0f;
	this->scale.x = 1.0f;
	this->scale.y = 1.0f;
	this->size.x =(float) bitmap->GetPixelSize().width;
	this->size.y = (float)bitmap->GetPixelSize().height;
	this->reverseAxisX = this->reverseAxisY = false;
}
/********************************************************************************
## GetPixel ## 
********************************************************************************/
COLORREF Image::GetPixel(int imageLeft, int imageTop, int x, int y)
{
	if (pixelCollisionDC != nullptr)
	{

	}
	return COLORREF();
}

COLORREF Image::GetPixel(int x, int y)
{
	return COLORREF();
}

/********************************************************************************
## SetupRender ## 
@@ int x : ���������� ȭ�鿡 ������ �� ��ǥ
@@ int y : ���������� ȭ�鿡 ������ �� ��ǥ
********************************************************************************/
D2D1::Matrix3x2F Image::SetupRender(int x, int y)
{
	POINT pt = { (LONG)x,(LONG)y };
	this->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	return D2D1::Matrix3x2F::Translation((float)pt.x,(float) pt.y);
}

/********************************************************************************
## GetPivotPosition ## 
@@ int x : ������ �� x��ǥ
@@ int y : ������ �� y��ǥ
@@ Pivot::Enum pivot : ������ �� �Ǻ�
********************************************************************************/
Vector2 Image::GetPivotPosition(int x, int y, Pivot::Enum pivot)
{
	if (pivot == Pivot::LEFT_TOP) return Vector2(x, y);

	Vector2 pos = { x,y };

	switch (pivot)
	{
	case Pivot::CENTER:
		pos.x -= size.x * scale.x * 0.5f;
		pos.y -= size.y * scale.y * 0.5f;
		break;

	case Pivot::BOTTOM:
		pos.x -= size.x * scale.x * 0.5f;
		pos.y -= size.y * scale.y;
		break;
	}

	return pos;
}
