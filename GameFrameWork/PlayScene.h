#pragma once
#include "gameNode.h"
#include "PlayerManager.h"

class PlayScene : public gameNode
{
private:
    PlayerManager * _pm;
public:
    PlayScene();
    ~PlayScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

