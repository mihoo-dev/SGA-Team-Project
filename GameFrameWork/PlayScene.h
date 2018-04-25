#pragma once
#include "gameNode.h"
class PlayScene : public gameNode
{
private:
    RECT _rc;
    float _x, _y;
public:
    PlayScene();
    ~PlayScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

