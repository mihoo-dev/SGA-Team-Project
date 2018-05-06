#include "stdafx.h"
#include "FountainScene.h"
#include "PlayerManager.h"


FountainScene::FountainScene()
	:_dance(false), _endingCreditY(600)
{
}


FountainScene::~FountainScene()
{
}

HRESULT FountainScene::init()
{
	SOUNDMANAGER->allStop();

	CAMERA->SetSize(600, 500);
	CAMERA->SetPos(0, 0);

	_pm = new PlayerManager;
	_pm->init(543, 416);

	_background = IMAGEMANAGER->addImage("STAGE_FOUNTAIN_BACKGROUND", "STAGE_FOUNTAIN_BACKGROUND.bmp", 988, 507, false, NULL);
	IMAGEMANAGER->addImage("STAGE_FOUNTAIN_BACKGROUND_PIXEL", "STAGE_FOUNTAIN_BACKGROUND_PIXEL.bmp", 988, 507, false, NULL);
	_fountain = IMAGEMANAGER->addFrameImage("STAGE_FOUNTAIN", "STAGE_FOUNTAIN.bmp", 1168, 145, 4, 1, true, RGB(255, 0, 255));
	_nymph1 = IMAGEMANAGER->addFrameImage("NYMPH1", "NYMPH1.bmp", 600, 122, 6, 1, true, RGB(255, 0, 255));
	_nymph2 = IMAGEMANAGER->addFrameImage("NYMPH2", "NYMPH2.bmp", 720, 148, 6, 1, true, RGB(255, 0, 255));
	_nymph1Idle = IMAGEMANAGER->addFrameImage("NYMPH1_IDLE", "NYMPH1_IDLE.bmp", 420, 88, 6, 1, true, RGB(255, 0, 255));
	_nymph2Idle = IMAGEMANAGER->addFrameImage("NYMPH2_IDLE", "NYMPH2_IDLE.bmp", 720, 94, 6, 1, true, RGB(255, 0, 255));


	_aniFountain = new animation;
	_aniFountain->init(1168, 145, 292, 145);
	_aniFountain->setDefPlayFrame(false, true);
	_aniFountain->setFPS(6);
	_aniFountain->start();

	_aniNymph1Idle = new animation;
	_aniNymph1Idle->init(420, 88, 70, 88);
	_aniNymph1Idle->setDefPlayFrame(false, true);
	_aniNymph1Idle->setFPS(6);
	_aniNymph1Idle->start();

	_aniNymph2Idle = new animation;
	_aniNymph2Idle->init(720, 94, 120, 94);
	_aniNymph2Idle->setDefPlayFrame(false, true);
	_aniNymph2Idle->setFPS(6);
	_aniNymph2Idle->start();

	_aniNymph1 = new animation;
	_aniNymph1->init(600, 122, 100, 122);
	_aniNymph1->setDefPlayFrame(false, true);
	_aniNymph1->setFPS(6);
	_aniNymph1->start();

	_aniNymph2 = new animation;
	_aniNymph2->init(720, 148, 120, 148);
	_aniNymph2->setDefPlayFrame(false, true);
	_aniNymph2->setFPS(6);
	_aniNymph2->start();

	_alpha = 255;
	_sceneStart = true;
	_sceneChange = false;

	return S_OK;
}

void FountainScene::release()
{
	SAFE_DELETE(_pm);
	SAFE_RELEASE(_aniFountain);
	SAFE_RELEASE(_aniNymph1);
	SAFE_RELEASE(_aniNymph2);
	SAFE_RELEASE(_aniNymph1Idle);
	SAFE_RELEASE(_aniNymph2Idle);
}

void FountainScene::update()
{
	SceneStart();

	_aniFountain->frameUpdate(TIMEMANAGER->getElapsedTime());
	_aniNymph1->frameUpdate(TIMEMANAGER->getElapsedTime());
	_aniNymph2->frameUpdate(TIMEMANAGER->getElapsedTime());
	_aniNymph1Idle->frameUpdate(TIMEMANAGER->getElapsedTime());

	if (_pm->GetPlayer()->GetX() < 200 && !_dance)
	{
		KEYANIMANAGER->findAnimation("PlayerDance")->setDefPlayFrame(false, true);
		SOUNDMANAGER->play("FOUNTAIN", 0.5f);
		_pm->GetPlayer()->SetPlayerDance();
		_dance = true;
	}

	CreditEnd();
	GoEndScene();

	if (_alpha != 255)
	{
		_pm->update();
		_pm->GetPlayer()->GroundCollision("STAGE_FOUNTAIN_BACKGROUND_PIXEL");
	}
}

void FountainScene::render()
{
	_background->render(getMemDC(), 0, 0);
	_fountain->aniRender(getMemDC(), 50, 320, _aniFountain);
	if (_dance)
	{
		_nymph1->aniRender(getMemDC(), 50, 418 - _nymph1->getFrameHeight(), _aniNymph1);
		_nymph2->aniRender(getMemDC(), 230, 416 - _nymph2->getFrameHeight(), _aniNymph2);
	}
	else
	{
		_nymph1Idle->aniRender(getMemDC(), 50, 418 - _nymph1Idle->getFrameHeight(), _aniNymph1Idle);
		_nymph2Idle->aniRender(getMemDC(), 230, 418 - _nymph2Idle->getFrameHeight(), _aniNymph2Idle);
	}

	_pm->render();

	UpCredit();

	IMAGEMANAGER->findImage("fade")->alphaRender(getMemDC(), CAMERA->GetRC().left, CAMERA->GetRC().top, _alpha);

	char x[128];
	sprintf_s(x, "x : %0.f, y : %0.f", _pm->GetPlayer()->GetX(), _pm->GetPlayer()->GetY());
	TextOut(getMemDC(), 0, 100, x, strlen(x));
}

void FountainScene::UpCredit()
{
	if (_dance) _endingCreditY--;


	RECT credit = RectMake(400, _endingCreditY, 200, 600);

	HFONT font, oldFont;

	font = CreateFont(30, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("휴먼매직체"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);

	char talk[256];

	sprintf_s(talk, "감사합니다\n플레이어 : 강동훈\n월드맵 : 권준형\n상점 : 남경태\n좀비 : 박요셉\n토끼 : 김진홍");

	DrawText(getMemDC(), talk, strlen(talk), &credit, DT_LEFT | DT_TOP);
	//TextOut(getMemDC(), 20, 130, talk, strlen(talk));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	SetBkMode(getMemDC(), OPAQUE);
}

void FountainScene::SceneStart()
{
	if (_sceneStart)
	{
		FadeOut(&_alpha);
		if (_alpha == 0) _sceneStart = false;
	}
}

void FountainScene::CreditEnd()
{
	if (_endingCreditY < -300 && !_sceneChange)
	{
		_sceneChange = true;
	}

	if (_sceneChange)
		FadeIn(&_alpha);
}

void FountainScene::GoEndScene()
{
	if (!_sceneStart && _alpha == 255)
	{
		SCENEMANAGER->changeScene("ClearScene", "LoadingScene");
	}
}