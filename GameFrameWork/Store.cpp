#include "stdafx.h"
#include "Store.h"


Store::Store()
{
}


Store::~Store()
{
}

HRESULT Store::init()
{
	_armor = new ArmorItem;
	_armor->init(CAMERA->GetCenterX() - 280, CAMERA->GetCenterY() - 100);


	_potion = new PotionItem;
	_potion->init(CAMERA->GetCenterX() + 220, CAMERA->GetCenterY() - 100);

	_starPoint = new StarPoint;
	_starPoint->init(CAMERA->GetCenterX() + 70, CAMERA->GetCenterY() - 100);

	_sword = new Sword;
	_sword->init(CAMERA->GetCenterX() - 110, CAMERA->GetCenterY() - 100);

	_NPC = new StoreNPC;
	_NPC->init(CAMERA->GetCenterX() + 200, CAMERA->GetCenterY());
	

	return S_OK;
}

void Store::update()
{
	_NPC->update();
}

void Store::release()
{
}

void Store::render()
{
	_armor->render();
	FontFunction(255, 0, 0, "armor", CAMERA->GetCenterX() - 470, CAMERA->GetCenterY() - 160);
	_potion->render();
	FontFunction(255, 0, 0, "potion", CAMERA->GetCenterX() + 20, CAMERA->GetCenterY() - 160);
	_starPoint->render();
	FontFunction(255, 0, 0, "star", CAMERA->GetCenterX() - 135, CAMERA->GetCenterY() - 160);
	_sword->render();
	FontFunction(255, 0, 0, "sword", CAMERA->GetCenterX() - 300, CAMERA->GetCenterY() - 160);

	_NPC->render();
}

void Store::FontFunction(int r, int g, int b, const char* txt, float rcX, float rcY)
{
	HFONT font, oldFont;
	RECT rcText = RectMake(rcX, rcY, 500, 300);

	font = CreateFont(20, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("±Ã¼­Ã¼"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextAlign(getMemDC(), TA_CENTER);
	DrawText(getMemDC(), TEXT(txt), strlen(txt), &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	SetTextColor(getMemDC(), RGB(r, g, b));

	SetTextAlign(getMemDC(), TA_TOP);
	SetBkMode(getMemDC(), OPAQUE);

}
