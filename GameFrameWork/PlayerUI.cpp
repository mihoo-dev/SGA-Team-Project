#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"


PlayerUI::PlayerUI()
{
}


PlayerUI::~PlayerUI()
{
}

HRESULT PlayerUI::init()
{
    IMAGEMANAGER->addImage("HPBack", "PlayerHPUIBack.bmp", 144, 46, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("HPFront", "PlayerHPUIFront.bmp", 40, 46, false, RGB(0, 0, 0));
    IMAGEMANAGER->addImage("SwordUI", "PlayerSwordUI.bmp", 70, 18, true, RGB(255, 0, 255));
    return S_OK;
}

void PlayerUI::release()
{
}

void PlayerUI::update()
{

}

void PlayerUI::render()
{
    IMAGEMANAGER->findImage("HPBack")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY());
    for (int i = 0; i < _playerHP; i++)
        IMAGEMANAGER->findImage("HPFront")->render(getMemDC(), CAMERA->GetX() + (i * 40), CAMERA->GetY());
    if (_weapon)
        IMAGEMANAGER->findImage("SwordUI")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY() + 50);
}

void PlayerUI::SetPlayerInfo(Player * player)
{
    _playerHP = player->GetInfo().hp;
    _weapon = player->GetInfo().weapon;
}
