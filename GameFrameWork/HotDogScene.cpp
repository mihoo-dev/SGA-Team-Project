#include "stdafx.h"
#include "HotDogScene.h"
#include "PlayerManager.h"


HotDogScene::HotDogScene()
	:_loopX(0)
	, _pressX(false), _Xframe(0), _Xcount(0)
	, _scriptX(WINSIZEX), _scriptState(0)
	, _count(0), _alpha(255)
{
}


HotDogScene::~HotDogScene()
{
}

HRESULT HotDogScene::init()
{
	_sceneStart = true;

	CAMERA->SetSize(WINSIZEX, WINSIZEY);
	CAMERA->SetPos(0, 0);
	IMAGEMANAGER->addImage("STAGE_HOTDOG", "STAGE_HOTDOG.bmp", 674, 510, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_HOTDOG_PIXEL", "STAGE_HOTDOG_PIXEL.bmp", 674, 510, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_HOTDOG_CLOUD", "STAGE_HOTDOG_CLOUD.bmp", 1200, 510, false, NULL);
	IMAGEMANAGER->addFrameImage("NPC_HOTDOG", "NPC_HOTDOG.bmp", 728, 64, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TALK_HOTDOG", "TALK_HOTDOG.bmp", 556, 154, true, RGB(255,0,255));

	_pm = new PlayerManager;
	_pm->init(151, 437);
	
	SOUNDMANAGER->allStop();
	SOUNDMANAGER->play("HOTDOG", 0.5f);

	int hotdog[] = { 0, 1, 2, 3, 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("NPC_HOTDOG_IDLE", "NPC_HOTDOG", hotdog, 7, 7, true);
	KEYANIMANAGER->findAnimation("NPC_HOTDOG_IDLE")->start();
	return S_OK;
}

void HotDogScene::release()
{
	_pm->release();
}

void HotDogScene::update()
{
	SceneStart();

	KEYANIMANAGER->update();
	_loopX += 0.2;

	_pm->GetPlayer()->GroundCollision("STAGE_HOTDOG_PIXEL");
	
	if (_scriptState == 0 || _scriptState == 7)	_pm->update();

	if (KEYMANAGER->isOnceKeyDown('M') && _pressX)
	{
		if (_scriptState == 0)	_scriptState = 1;
		else if (_scriptState == 2)	_scriptState = 3;
		else if (_scriptState == 3) _scriptState = 4;
		else if (_scriptState == 6) _scriptState = 7;
	}

	OutStage();
	button();
	MoveScript();


}

void HotDogScene::render()
{
	

	RECT temp = RectMake(CAMERA->GetX(), CAMERA->GetY(), WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE_HOTDOG_CLOUD")->loopRender(getMemDC(), &temp, _loopX, 0);
	IMAGEMANAGER->findImage("STAGE_HOTDOG")->render(getMemDC()
		, CAMERA->GetX(), CAMERA->GetY()
		, CAMERA->GetX(), CAMERA->GetY()
		,WINSIZEX, WINSIZEY);
	
	IMAGEMANAGER->findImage("TALK_HOTDOG")->render(getMemDC(), _scriptX, 100);

	IMAGEMANAGER->findImage("NPC_HOTDOG")->aniRender(getMemDC(), CAMERA->GetX() + 470, CAMERA->GetY() + 417, KEYANIMANAGER->findAnimation("NPC_HOTDOG_IDLE"));

	_pm->render();

	if (_pressX && _scriptState == 0)
	{
		IMAGEMANAGER->findImage("PRESS_X")->frameRender(getMemDC(), 504, 400, _Xframe, 0);
	}
	
	Script();

	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);

	//CheckStatus();
}

void HotDogScene::OutStage()
{
	if (_pm->GetPlayer()->GetX() < 100)
	{
		FadeIn(&_alpha);
	}
	if (_alpha == 255 && _sceneStart == false)
	{
		WORLDXY->SetWorldX(2490);
		WORLDXY->SetWorldY(1143);
		SCENEMANAGER->changeScene("WorldScene", "LoadingScene");
	}
}

void HotDogScene::SceneStart()
{
	if (_sceneStart)
	{
		FadeOut(&_alpha);
		if (_alpha == 0) _sceneStart = false;
	}
}

void HotDogScene::Script()
{
	HFONT font, oldFont;

	font = CreateFont(20, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("휴먼매직체"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);

	char talk[256];
	char talk2[256];
	if (_scriptState == 0 || _scriptState == 1)
	{
		sprintf_s(talk, "");
		sprintf_s(talk2, "");
	}
	else if (_scriptState == 2)
	{
		sprintf_s(talk, "안녕 나는 핫도그 공주야.");
		sprintf_s(talk2, "");
	}
	else if (_scriptState == 3)
	{
		sprintf_s(talk, "우리 숲을 막고 있는 괴물을 해치워서 고마워.");
		sprintf_s(talk2, "답례로 우리 종족의 고유 능력을 전수해줄께.!");
	}
	else if (_scriptState == 4)
	{
		sprintf_s(talk, "");
		sprintf_s(talk2, "");
		SOUNDMANAGER->play("GETBRIDGE");
		WORLDXY->SetMeetDog(true);
		_scriptState = 5;
	}
	else if (_scriptState == 5)
	{
		sprintf_s(talk, "길어져라! 허리허리!!");
		sprintf_s(talk2, "");
		_count++;
		if (_count > 350) _scriptState = 6;
	}
	else if (_scriptState == 6)
	{
		sprintf_s(talk, "이제 너는 서쪽에 있는");
		sprintf_s(talk2, "부서진 다리를 건널 수 있을거야.");
	}
	else if (_scriptState == 7)
	{
		sprintf_s(talk, "너의 여정에 행운이 함께 하기를 기도할께.");
		sprintf_s(talk2, "");
	}
	TextOut(getMemDC(), _scriptX + 20, 130, talk, strlen(talk));
	TextOut(getMemDC(), _scriptX + 20, 160, talk2, strlen(talk2));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	SetBkMode(getMemDC(), OPAQUE);

	if (_scriptState == 0 || _scriptState == 1 || _scriptState == 4 || _scriptState == 5 || _scriptState == 7) return;
	IMAGEMANAGER->findImage("PRESS_X")->frameRender(getMemDC(), 35, 212, _Xframe, 0);
}

void HotDogScene::MoveScript()
{
	if (_scriptState == 1)
	{
		_scriptX -= 20;
		if (_scriptX < 30) _scriptState = 2;
	}
}


void HotDogScene::CheckStatus()
{
	char status[128];
	sprintf_s(status, "_x : %0.f, _y : %0.f", _pm->GetPlayer()->GetX(), _pm->GetPlayer()->GetY());
	TextOut(getMemDC(), CAMERA->GetX(), CAMERA->GetY() + WINSIZEY - 300, status, strlen(status));
}

void HotDogScene::button()
{
	if (_pressX)
	{
		_Xcount++;
		if (_Xcount > 20)
		{
			_Xcount = 0;
			_Xframe++;
		}
		if (_Xframe > 1) _Xframe = 0;
	}

	if (_pm->GetPlayer()->GetX() > 400) _pressX = true;
	else _pressX = false;
}