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

    return S_OK;
}

void PlayerManager::release()
{
    _player->release();
}

void PlayerManager::update()
{
    _player->update();
}

void PlayerManager::render()
{
    _player->render();
}
