#pragma once
#include "gameNode.h"
#include "PlayerManager.h"

class TutorialScene : public gameNode
{
private:
    PlayerManager * _pm;
public:
    TutorialScene();
    ~TutorialScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

