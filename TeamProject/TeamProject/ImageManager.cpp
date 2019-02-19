#include "stdafx.h"
#include "ImageManager.h"
#include "DXRenderer.h"
#include "Image.h"
#include "Path.h"
#include "StringHelper.h"
#include <io.h>

SingletonCpp(ImageManager)

/********************************************************************************
## ImageManager ## 
********************************************************************************/
ImageManager::ImageManager()
{
	
}
/********************************************************************************
## ~ImageManager ## 
��� ���ҽ� ���� 
********************************************************************************/

ImageManager::~ImageManager()
{
	this->DeleteAll();
}

/********************************************************************************
## AddImage ## 
�̹��� ���
@@ string key : �̹��� Ű��
@@ wstring file : ���ϰ��
@@ bool usePixelCollisiton : �ȼ� �浹�Ұ����� 

@@return Image* : ���� �߰��� �̹��� ��ȯ 
********************************************************************************/
Image * ImageManager::AddImage(string key, wstring file, bool usePixelCollision)
{
	Image* image = this->FindImage(key);
	if (image)
		return image;

	ID2D1Bitmap* bitmap = this->CreateD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::TagLoadedImageInfo loadInfo = { key,file };
		image = new Image;
		image->Init(bitmap, loadInfo);
		
		if (usePixelCollision)
		{
			HBITMAP hBit = (HBITMAP)LoadImageW(Window::GetWindowDesc().Instance, file.c_str(), IMAGE_BITMAP,
				bitmap->GetPixelSize().width, bitmap->GetPixelSize().height, LR_LOADFROMFILE);
			HDC memDC = CreateCompatibleDC(Window::GetWindowDesc().Hdc);

			SelectObject(memDC, hBit);
			DeleteObject(hBit);

			image->SetPixelDC(memDC);
		}
		imageList.insert(make_pair(key, image));
		return image;
	}
	else
		assert(E_FAIL);

	return nullptr;
}

/********************************************************************************
## AddFrameImage ##
������ �̹��� ��� 
@@ string key : Ű�� 
@@ wstring file : ���ϰ�� 
@@ int maxFrameX : ���������� �� 
@@ int maxFrameY : ���� ������ ��
@@ bool usePixel : �ȼ� �浹������ �������� 

@@ return Image* : ����� �̹��� ��ȯ
********************************************************************************/

Image * ImageManager::AddFrameImage(string key, wstring file, int maxFrameX, int maxFrameY, bool usePixelCollision)
{
	Image* image = this->FindImage(key);
	if (image)
		return image;

	ID2D1Bitmap* bitmap = CreateD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::TagLoadedImageInfo loadInfo = { key,file };
		image = new Image;
		image->Init(bitmap, loadInfo, maxFrameX, maxFrameY);

		if (usePixelCollision) {}

		this->imageList.insert(make_pair(key, image));
		return image;
	}

	return nullptr;
}

/********************************************************************************
## FineImage ## 
�̹��� Ű������ ã�� ��ȯ 
@@ string key : Ű��

@@ return Image* : ã�� �̹��� ��ȯ 
********************************************************************************/
Image * ImageManager::FindImage(string key)
{
	MapImageIter iter = imageList.find(key);
	if (iter != imageList.end())
		return iter->second;
	return nullptr;
}

/********************************************************************************
## GetImage ## 
�̹��� Ű�� �ٷ� �����ؼ� ��ȯ (Ű�� ���������� �����ϸ� ���� ���� Ű���� �� �ؽ��ʿ� ������� 
�����ϴ� ����) 
@@ string key : Ű�� 

@@ return Image* : ã�� �̹��� ��ȯ
********************************************************************************/
Image * ImageManager::GetImage(string key)
{
	return this->imageList[key];
}

/********************************************************************************
## CreateD2DBitmapFromFile ##
��ηκ��� ���丮�� ���ڴ��� ���� ��Ʈ���� ����
@@ wstring file : ���� ��� 

@@ return ID2D1Bitmap* : ������ ��Ʈ�� ��ȯ 
********************************************************************************/
ID2D1Bitmap * ImageManager::CreateD2DBitmapFromFile(wstring file)
{
	//���ڴ� ����
	IWICBitmapDecoder* ipDecoder = nullptr;
	wicFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &ipDecoder);
	//���ڴ����� �����Ӿ���
	IWICBitmapFrameDecode* ipFrame = nullptr;
	ipDecoder->GetFrame(0, &ipFrame);
	//�������� ������� ���� �����͸� �����.
	SafeRelease(convertedSrcBmp);
	wicFactory->CreateFormatConverter(&convertedSrcBmp);

	convertedSrcBmp->Initialize(
		ipFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
	//����Ʈ�� �����͸� ������� ���� Direct2D�� ��Ʈ���� ����
	ID2D1Bitmap* ipResult = nullptr;
	_DXRenderer->GetD2DRenderTarget()->CreateBitmapFromWicBitmap
	(
		convertedSrcBmp,
		nullptr,
		&ipResult
	);

	SafeRelease(ipDecoder);
	SafeRelease(ipFrame);

	

	return ipResult;
}

/********************************************************************************
## DeleteAll ## 
��ü �̹��� Ŭ���� �Ҵ� ���� 
********************************************************************************/
void ImageManager::DeleteAll()
{
	MapImageIter iter = imageList.begin();
	for (; iter != imageList.end(); ++iter)
	{
		if(iter->second)
			iter->second->Release();
		SafeDelete(iter->second);
	}
	imageList.clear();
}

/********************************************************************************
## OnGui ## 
********************************************************************************/
void ImageManager::OnGui()
{

}

/********************************************************************************
## LoadFolder ## 
�ش� ������ ��� png�� ã�� �̹����� ��� 
@@ const string path : ���� ���
@@ const string filter : ã�� ���� ���� 
********************************************************************************/
void ImageManager::LoadFolder(const string path, const string filter)
{
	std::string searching = path + filter;

	std::vector<std::string> return_;

	_finddata_t fd;
	long handle = _findfirst(searching.c_str(), &fd);  //���� ���� �� ��� ������ ã�´�.

	if (handle == -1)return;

	int result = 0;
	do
	{
		string filePath = path + fd.name;

		if (filter == "*.png")
			this->AddImage(Path::GetFileNameWithoutExtension(fd.name),StringHelper::StringToWString(filePath));

		result = _findnext(handle, &fd);
	} while (result != -1);

	_findclose(handle);
}

/********************************************************************************
## LoadAllResource ##
********************************************************************************/
void ImageManager::LoadAllResource()
{
	
}
