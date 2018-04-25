//컴파일 하기 이전에 미리 한 번 메모리에 로드하는 곳
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>


using namespace std;

#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "txtData.h"
#include "iniDataManager.h"
#include "keyAniManager.h"
#include "CameraManager.h"
#include "utils.h"

using namespace NONA_UTIL;

//==============================
// ## Define ## 18.02.07 ##
//==============================

#define WINNAME (LPSTR)(TEXT("Nona API"))
#define WINSTARTX 50		//윈도우 시작좌표 X
#define WINSTARTY 50		//윈도우 시작좌표 Y
#define WINSIZEX 300		//윈도우 가로크기
#define WINSIZEY 250		//윈도우 세로크기
#define GAMESIZEX 687
#define GAMESIZEY 732
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define KEYMANAGER		keyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define KEYANIMANAGER	keyAniManager::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define INIDATA			iniDataManager::getSingleton()
#define CAMERA          CameraManager::getSingleton()

//===================================
// ## Macro ## 2018.02.27 ##
//===================================

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)= NULL;}}

//====================================
// ## 18.02.12 ## - Extern - ##
//====================================
extern POINT		_ptMouse;
extern HWND			_hWnd;
extern HINSTANCE	_hInstance;