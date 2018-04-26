#pragma once
#include "gameNode.h"
class Player :
    public gameNode
{
private:
    enum STATE {
        RIGHT_IDLE, LEFT_IDLE
    };
    enum DIRECTION {
        LEFT, RIGHT
    };

    image * _img;
    animation * _anim;

    RECT _rc;
    float _x, _y;
    DIRECTION _direction;
    STATE _state;
public:
    Player();
    ~Player();

    HRESULT init();
    void release();
    void update();
    void render();
};

