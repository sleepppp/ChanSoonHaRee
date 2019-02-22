/*********************************************************
## DefineHeader.h ##
Ŭ�������� ���������� ����� ��ó����(define)�� ���⿡ �߰�
**********************************************************/
#pragma once

#define LockingFPS 500.0f

#define WinSizeX 1280	//������â ���α���
#define WinSizeY 760	//������â ���α���

#define ZeroToASC 48	//���� 0 �ƽ�Ű��
#define NineToASC 57	//���� 9 �ƽ�Ű��

/*************************************************************
## SafeRelease ##
@@ p : Release �Լ��� �ִ� Ŭ���� 

SafeRelease�� ���� ���丮 ���ϱ��� Ŭ���� �Ǵ� ���̺귯���� ����� 
��� ����Ѵ�. ��� �츮�� ���ÿ� �� �� �����~
*************************************************************/
#define SafeRelease(p){ if(p){ (p)->Release(); (p) = NULL; } }
/*************************************************************
## SafeDelete ##
@@ p : ������

�Ҵ��� �޸𸮸� delete�� ���� ���� �ϰ� �ش� ������(p)�� NULL�� �ʱ�ȭ 
*************************************************************/
#define SafeDelete(p){ if(p){ delete (p); (p) = NULL; } }
/*************************************************************
## SafeDeleteArray ## 
@@ p : ���� �迭 ������ 

���� �迭�� �Ҵ��� �����͸� �޸� ���� �� NULL�� �ʱ�ȭ 
*************************************************************/
#define SafeDeleteArray(p){ if(p){ delete [] (p); (p) = NULL; } }
/*************************************************************
## CastingInt ## 
@@ n : ����,�Ǽ� �� ���� 

n�� int������ ��ȯ (float)1.0f�ϴ°Ŷ� ����
*************************************************************/
#define CastingInt(n) static_cast<int>(n)
/*************************************************************
## CastingFloat ##
@@ n : ����,�Ǽ� �� 

n�� float������ ��ȯ 
*************************************************************/
#define CastingFloat(n) static_cast<float>(n)
/*************************************************************
## CastingFloat ## 
@@ VarType : �ڷ���
@@ VarName : �����̸� 
@@ FuncName : �Լ��̸� 

����,������,������ ���ϰ� ����� ��ó����
*************************************************************/
#define Synthesize(VarType, VarName, FuncName)	\
protected:	VarType VarName;	\
public:	inline VarType Get##FuncName(void) const { return VarName; }	\
public:	inline void Set##FuncName(VarType value) { VarName = value; }

/*************************************************************
## HResult ##
@@ n : HRESULT ����� 

n�� ������� ���� ���� �޼��� �ڽ��� �Բ� �����Ϸ� �ߴ�
*************************************************************/
#if defined(DEBUG) | defined(_DEBUG)
#ifndef HResult
#define HResult(x)                                       \
   {                                             \
      HRESULT hr = (x);                              \
      if(FAILED(hr))                                 \
      {                                          \
         LPWSTR output;                              \
         FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |            \
         FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),   \
            (LPTSTR)&output, 0, NULL);                                             \
            MessageBox(NULL, output, L"Error", MB_OK);                                 \
      }                                                                     \
   }
#endif

#else
#ifndef HResult
#define HResult(x) (x)
#endif
#endif 
/*************************************************************
## Assert ##
@@ b : HRESULT �Ǵ� bool ��

assert�� �����Ϸ��� ���� ��Ű���� �� ��ó����� �����Ϸ� ���� ��� �����â�� �������� ���
*************************************************************/
#ifndef Assert
#if defined(DEBUG) || defined(_DEBUG)
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert : " #b "\n"); }} while (0)
#else
#define Assert(b)
#endif   //   DEBUG || _DEBUG
#endif
/*************************************************************
## Singleton ##
��ó���� �̱���
*************************************************************/
#define SingletonHeader(ClassName)	\
public:								\
	static ClassName* Get();		\
	static void Create();			\
	static void Delete();			\
private:							\
	ClassName();					\
	~ClassName();					\
	static ClassName* instance;		

#define SingletonCpp(ClassName)				\
ClassName* ClassName::instance = nullptr;	\
ClassName * ClassName::Get()				\
{											\
	assert(instance != nullptr);			\
	return instance;						\
}											\
void ClassName::Create()					\
{											\
	assert(instance == nullptr);			\
	instance = new ClassName();				\
}											\
void ClassName::Delete()					\
{											\
	SafeDelete(instance);					\
}			

