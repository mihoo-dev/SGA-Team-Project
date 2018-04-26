#pragma once
#include "gameNode.h"
class Player :
    public gameNode
{
private:
    enum DIRECTION {
        LEFT, RIGHT
    };

    RECT _rc;
    float _x, _y;
    DIRECTION _direction;
public:
    Player();
    ~Player();

    HRESULT init();
    void release();
    void update();
    void render();
};

