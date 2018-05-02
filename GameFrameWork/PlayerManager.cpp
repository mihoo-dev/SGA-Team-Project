#include "stdafx.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

HRESULT PlayerManager::init()
{
    _player = new Player;
    _player->init();

    _pu = new PlayerUI;
    _pu->init();

    return S_OK;
}

void PlayerManager::release()
{
    _player->release();
    _pu->release();
}

void PlayerManager::update()
{
    _player->update();
    
    _pu->SetPlayerInfo(_player);
    _pu->update();
}

void PlayerManager::render()
{
    _player->render();
    _pu->render();
}
