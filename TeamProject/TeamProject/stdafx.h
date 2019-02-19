﻿// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <assert.h>
#include <functional>
#include <unordered_map>

using namespace std;

#include "LibraryHeader.h"
#include "DefineHeader.h"
#include "EnumStructHeader.h"
#include "ModuleHeader.h"

#define IsMouseOnGui ImGui::GetIO().WantCaptureMouse
//콘솔 창 출력
#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")