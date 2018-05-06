#pragma once
#include "Object.h"
class Door :
    public Object
{
private:
    enum STATE {
        CLOSE, OPEN
    };

    STATE _state;
public:
    Door();
    ~Door();

    HRESULT init(float x, float y);
    void release();
    void update();
    void render();

    void Collision(Player * player);
};

