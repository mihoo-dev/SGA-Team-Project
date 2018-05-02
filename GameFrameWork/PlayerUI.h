#pragma once
#include "gameNode.h"

class Player;

class PlayerUI :
    public gameNode
{
private:
    int _playerHP;
    bool _weapon;
public:
    PlayerUI();
    ~PlayerUI();

    HRESULT init();
    void release();
    void update();
    void render();

    void SetPlayerInfo(Player * player);
};

