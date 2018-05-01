#pragma once
#include "gameNode.h"
#include "Player.h"

class PlayerManager :
    public gameNode
{
private:
    Player * _player;
public:
    PlayerManager();
    ~PlayerManager();

    HRESULT init();
    void release();
    void update();
    void render();

    inline RECT GetRC() { return _player->GetRC(); }
};

