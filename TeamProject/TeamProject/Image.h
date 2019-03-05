#pragma once

class Image
{
public:
	struct TagLoadedImageInfo
	{
		string key;
		wstring directory;
	};
private:
	struct FrameRect
	{
		float X;
		float Y;
		float Width;
		float Height;
	};
private:
	static ID2D1RenderTarget*	renderTarget;

	ID2D1Bitmap*		bitmap;
	float				alpha;			//�̹��� ����

	Vector2				size;			//�̹��� ũ��
	Vector2				scale;			//x,y ũ�� Ȯ��,��� ����
	float				angle;

	TagLoadedImageInfo	loadInfo;		//�̹��� �ε� ����

										
	HDC	pixelCollisionDC;				//�ȼ� �浹�� DC

	//������ ���� ó���� ���� RECT���� ����
	vector<FrameRect>	frameInfo;
	int					maxFrameX;
	int					maxFrameY;

	//����
	bool				reverseAxisX;
	bool				reverseAxisY;


public:
	Image()
		:bitmap(nullptr), pixelCollisionDC(nullptr), reverseAxisX(false), reverseAxisY(false) {}
	virtual ~Image() {}

	void Init(ID2D1Bitmap* bitmap, TagLoadedImageInfo loadinfo);
	void Init(ID2D1Bitmap* bitmap, TagLoadedImageInfo loadinfo, int maxframeX, int maxframeY);

	void Release();
	void Render(int x, int y, Pivot::Enum pivot = Pivot::CENTER, bool isRelativePos = false);
	void FrameRender(int x, int y, int frameX, int frameY, Pivot::Enum pivot = Pivot::CENTER, bool isRelativePos = false);
	//void aniRender(int x, int y, animation* ani, Pivot::Enum pivot = Pivot::CENTER, bool isRelativePos = TRUE, bool sizeSet = FALSE);

	//�ɼ�
	void SetSize(Vector2 vec);
	void SetAlpha(float alpha);
	void SetScale(float scale);
	void SetAngle(float angle);
	void ResetRenderOption();

	int GetMaxFrameX() { return maxFrameX; }
	int GetMaxFrameY() { return maxFrameY; }
	ID2D1Bitmap* GetBitMap()const { return this->bitmap; }
	string GetKey() { return this->loadInfo.key; }

	UINT GetWidth() { return bitmap->GetPixelSize().width; }
	UINT GetHeight() { return bitmap->GetPixelSize().height; }
	Vector2 GetSize()const { return this->size; }
	Vector2 GetFrameSize(int frame) { return Vector2(frameInfo[frame].Width, frameInfo[frame].Height); }
	bool IsFrameImage()
	{
		if (frameInfo.size() == 1) return false;
		else if (frameInfo.size() > 1)return true;
	}

	TagLoadedImageInfo GetLoadInfo() { return loadInfo; }

	//�ȼ��浹��
	void SetPixelDC(HDC pixelDC) { pixelCollisionDC = pixelDC; }
	COLORREF GetPixelColor(int x, int y);
	HDC GetPixelDC() { return pixelCollisionDC; }
	void RenderPixel(HDC hdc, int x, int y);
	void SetReverse(bool x, bool y){reverseAxisX = x;reverseAxisY = y;}
	void SetReverseX(bool x) { reverseAxisX = x; }
	void SetReverseY(bool y) { reverseAxisY = y; }
public:
	static void SetRenderTarget(ID2D1RenderTarget* rt){ renderTarget = rt; }

private:
	D2D1::Matrix3x2F SetupRender(int x, int y);
	Vector2 GetPivotPosition(int x, int y, Pivot::Enum pivot);
};

